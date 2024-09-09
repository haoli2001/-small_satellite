#include "ccyclebuffer.h"
#include <assert.h>
#include <memory.h>
#include <QDebug>

CCycleBuffer::CCycleBuffer(int size, QObject *parent) : QObject(parent)
{
    m_nBufSize = size;
    m_nReadPos = 0;
    m_nWritePos = 0;
    m_pBuf = (unsigned char*)malloc(m_nBufSize * sizeof(unsigned char));
    //m_pBuf = new unsigned char[m_nBufSize];
    m_bEmpty = true;
    m_bFull = false;
    test = 0;
}

CCycleBuffer::~CCycleBuffer()
{
    free(m_pBuf);
}

/************************************************************************/
/* 向缓冲区写入数据，返回实际写入的字节数 */
/************************************************************************/
long long  CCycleBuffer::write(unsigned char *buf, long long  count)
{
    if(count <= 0)
    {
        return 0;
    }

    m_bEmpty = false;
    // 缓冲区已满，不能继续写入
    if(m_bFull)
    {
        return 0;
    }
    else if(m_nReadPos == m_nWritePos) // 缓冲区为空时
    {
        /* == 内存模型 ==
(empty) m_nReadPos (empty)
|----------------------------------|-----------------------------------------|
m_nWritePos m_nBufSize
*/
        long long  leftcount = m_nBufSize - m_nWritePos;
        if(leftcount > count)
        {
            memcpy(m_pBuf + m_nWritePos, buf, count);
            m_nWritePos += count;
            m_bFull = (m_nWritePos == m_nReadPos);
            return count;
        }
        else
        {
            memcpy(m_pBuf + m_nWritePos, buf, leftcount);
            m_nWritePos = (m_nReadPos > count - leftcount) ? count - leftcount : m_nWritePos;
            memcpy(m_pBuf, buf + leftcount, m_nWritePos);
            m_bFull = (m_nWritePos == m_nReadPos);

            return leftcount + m_nWritePos;
        }
    }
    else if(m_nReadPos < m_nWritePos) // 有剩余空间可写入
    {
        /* == 内存模型 ==
        (empty)                 (data)                       (empty)
|-------------------|----------------------------|---------------------------|
               m_nReadPos                  m_nWritePos    (leftcount)
*/
        // 剩余缓冲区大小(从写入位置到缓冲区尾)
        long long  leftcount = m_nBufSize - m_nWritePos;
        long long  test = m_nWritePos;
        if(leftcount > count) // 有足够的剩余空间存放   //最右侧可放下此次数据
        {
            memcpy(m_pBuf + m_nWritePos, buf, count);
            m_nWritePos += count;
            m_bFull = (m_nReadPos == m_nWritePos);
            assert(m_nReadPos <= m_nBufSize);      //m_nReadPos > m_nBufSize 则中断
            assert(m_nWritePos <= m_nBufSize);

            return count;
        }
        else // 剩余空间不足
        {
            // 先填充满剩余(右侧)空间，再从头放置
            memcpy(m_pBuf + test, buf, leftcount);

            m_nWritePos = (m_nReadPos >= count - leftcount) ? count - leftcount : m_nReadPos;
            memcpy(m_pBuf, buf + leftcount, m_nWritePos);
            m_bFull = (m_nReadPos == m_nWritePos);
            assert(m_nReadPos <= m_nBufSize);
            assert(m_nWritePos <= m_nBufSize);

            return leftcount + m_nWritePos;
        }
    }
    else        //中间剩余
    {
        /* == 内存模型 ==
       (unread)                (read)                       (unread)
|-------------------|----------------------------|---------------------------|
              m_nWritePos   (leftcount)     m_nReadPos
*/
        long long  leftcount = m_nReadPos - m_nWritePos;
        if(leftcount > count)
        {
            // 有足够的剩余空间存放
            memcpy(m_pBuf + m_nWritePos, buf, count);
            m_nWritePos += count;
            m_bFull = (m_nReadPos == m_nWritePos);
            assert(m_nReadPos <= m_nBufSize);
            assert(m_nWritePos <= m_nBufSize);

            return count;
        }
        else
        {
            // 剩余空间不足时要丢弃后面的数据
            memcpy(m_pBuf + m_nWritePos, buf, leftcount);
            m_nWritePos += leftcount;
            m_bFull = (m_nReadPos == m_nWritePos);
            assert(m_bFull);
            assert(m_nReadPos <= m_nBufSize);
            assert(m_nWritePos <= m_nBufSize);

            return leftcount;
        }
    }
}
/************************************************************************/
/* 从缓冲区读数据，返回实际读取的字节数 */
/************************************************************************/
long long  CCycleBuffer::read(unsigned char *buf, long long  count)
{

    if(count <= 0)
    {

        return 0;
    }
    m_bFull = false;
    if(m_bEmpty) // 缓冲区空，不能继续读取数据
    {

        return 0;
    }
    else if(m_nReadPos == m_nWritePos) // 缓冲区满时
    {
        /* == 内存模型 ==
             (data)         m_nReadPos                (data)
|--------------------------------|--------------------------------------------|
                           m_nWritePos                                   m_nBufSize
*/
        long long  leftcount = m_nBufSize - m_nReadPos;
        if(leftcount > count)
        {
            memcpy(buf, m_pBuf + m_nReadPos, count);
            m_nReadPos += count;
            m_bEmpty = (m_nReadPos == m_nWritePos);

            return count;
        }
        else
        {
            memcpy(buf, m_pBuf + m_nReadPos, leftcount);
            m_nReadPos = (m_nWritePos > count - leftcount) ? count - leftcount : m_nWritePos;
            memcpy(buf + leftcount, m_pBuf, m_nReadPos);
            m_bEmpty = (m_nReadPos == m_nWritePos);

            return leftcount + m_nReadPos;
        }
    }
    else if(m_nReadPos < m_nWritePos) // 写指针在前(未读数据是连接的)
    {
        /* == 内存模型 ==
        (read)                (unread)                       (read)
|-------------------|----------------------------|---------------------------|
               m_nReadPos                   m_nWritePos                 m_nBufSize
*/
        long long  leftcount = m_nWritePos - m_nReadPos;
        long long  c = (leftcount > count) ? count : leftcount;
        memcpy(buf, m_pBuf + m_nReadPos, c);
        m_nReadPos += c;
        m_bEmpty = (m_nReadPos == m_nWritePos);

        assert(m_nReadPos <= m_nBufSize);
        assert(m_nWritePos <= m_nBufSize);
        return c;
    }
    else // 读指针在前(未读数据可能是不连接的)
    {
        /* == 内存模型 ==
       (unread)               (read)                        (unread)
|-------------------|----------------------------|---------------------------|
                m_nWritePos                 m_nReadPos                  m_nBufSize

*/
        long long  leftcount = m_nBufSize - m_nReadPos;
        if(leftcount > count) // 未读缓冲区够大，直接读取数据
        {
            memcpy(buf, m_pBuf + m_nReadPos, count);
            m_nReadPos += count;
            m_bEmpty = (m_nReadPos == m_nWritePos);

            assert(m_nReadPos <= m_nBufSize);
            assert(m_nWritePos <= m_nBufSize);
            return count;
        }
        else // 未读缓冲区不足，需回到缓冲区头开始读
        {
            memcpy(buf, m_pBuf + m_nReadPos, leftcount);
            m_nReadPos = (m_nWritePos >= count - leftcount) ? count - leftcount : m_nWritePos;
            memcpy(buf + leftcount, m_pBuf, m_nReadPos);
            m_bEmpty = (m_nReadPos == m_nWritePos);

            assert(m_nReadPos <= m_nBufSize);
            assert(m_nWritePos <= m_nBufSize);
            return leftcount + m_nReadPos;
        }
    }
}
/************************************************************************/
/* 获取缓冲区有效数据长度 */
/************************************************************************/
long long  CCycleBuffer::getLength()
{
    if(m_bEmpty)
    {
        return 0;
    }
    else if(m_bFull)
    {
        return m_nBufSize;
    }
    else if(m_nReadPos < m_nWritePos)
    {
        return m_nWritePos - m_nReadPos;
    }
    else
    {
        return m_nBufSize - m_nReadPos + m_nWritePos;
    }
}

void CCycleBuffer::empty()
{
    m_nReadPos = 0;
    m_nWritePos = 0;
    m_bEmpty = true;
    m_bFull = false;
    test = 0;
    memset(m_pBuf, 0, m_nBufSize * sizeof(unsigned char));
}
bool CCycleBuffer::isEmpty()
{
    return m_bEmpty;
}
bool CCycleBuffer::isFull()
{
    return m_bFull;
}
