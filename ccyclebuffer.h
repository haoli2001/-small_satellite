#ifndef CCYCLEBUFFER_H
#define CCYCLEBUFFER_H

#include <QObject>
#include <QMutex>

class CCycleBuffer : public QObject
{
    Q_OBJECT
public:
    explicit CCycleBuffer(int size, QObject *parent = nullptr);
    ~CCycleBuffer();

public:
    bool isFull();
    bool isEmpty();
    void empty();
    long long   getLength();
    long long   write(unsigned char* buf, long long count);
    long long   read(unsigned char* buf, long long  count);
    long long   getStart() { return m_nReadPos;  }
    long long   getEnd()   { return m_nWritePos; }

private:
    bool m_bEmpty, m_bFull;
    unsigned char * m_pBuf;
    long long m_nBufSize;
    long long  m_nReadPos;
    long long  m_nWritePos;
    long long  test;

    QMutex m_mutex;
signals:

};

#endif // CCYCLEBUFFER_H
