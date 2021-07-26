#ifndef DATAGRAM_H
#define DATAGRAM_H

#include <QObject>
#include <QDataStream>

class Datagram : public QObject
{
    Q_OBJECT

public:
    Datagram(const QByteArray &_datagram, QObject *parent = nullptr);
    Datagram(const QString &_msg,
             const short &_recvId,
             const short &_sendId,
             const short &_msgId,
             const qint8 &_type,
             const qint16 &_packageNumber,
             const quint16 &_checkSum,
             QObject *parent = 0);
    ~Datagram();

    Datagram &operator=(Datagram &other);

    void datagarmAssemble();
    void datagramParse();

    QByteArray getData();
    unsigned short getReceiverId();
    unsigned short getSenderId();
    unsigned short getMessageId();
    qint8 getType();
    unsigned short getPackageNumber();
    bool getEndFlag();
    QString getMessage();
    quint16 getCheckSum();

    void setEndFlag();

private:
    QString msg;
    short sendId;
    short recvId;
    short msgId;

    qint8 type;
    // 0 - OK
    // 1 - Meassage
    // 2 - File
    // 3 - Request

    qint16 packageNumber;
    bool isEnd;
    quint16 checkSum;
    QByteArray data;
};
#endif // DATAGRAM_H
