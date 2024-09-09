#ifndef SOCKETCONSTANT_H
#define SOCKETCONSTANT_H

#include <QByteArray>
#include <QList>
#include <QIODevice>
#include <QDataStream>

#define ERROR_NUMBER            -999
#define INIT_NUMBER             -1  //初始化数据
#define ERROR_INFO              "UNDEFINED"

#define LOG_FILE_PATH       QString("log/") //日志文件存储路径

#define SENTENCE_TO_DELETE  //用于提醒待删除的语句（一些临时加的调试语句） 160825
#define SENTENCE_TO_PROCESS //用于提醒哪些句子需要后续处理的，有可能临时注释掉了，或改变了参数 160825


//Socket连接参数
#define NET_TCP_PORT             3075    //TCP服务器监听“起始”端口号
#define NET_PORT_SPACE           10      //尝试监听、绑定、广播端口号间隔

#define NET_SOCKET_TIMEOUT       10*1000 //多长时间没有收到客户端信息说明已经断开
#define NET_SHAKE_HAND_ENABLED   false

//包数据结构 : [ 标准TCP-IP消息头 + 通道I/Q + 请求 + 数据块数量 + 标准TCP-IP消息尾 ]
#define TCP_START                1234567890
#define TCP_Length               128
#define TCP_StreamID             0
#define TCP_Channel_I            0
#define TCP_Channel_Q            1
#define TCP_Request              4
#define TCP_END                  -1234567890
#define BUFFERSIZE               (1024 * 1024 * 8)    //256M //l 0619修改成8M

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct Data
    {
        int list[5];//数据
    }Data;
#ifdef __cplusplus
}
#endif

#endif // SOCKETCONSTANT_H
