#ifndef UDPCHAT_H
#define UDPCHAT_H

#include <QtNetwork/QUdpSocket>
#include <QObject>
#include <vector>
#include <QDataStream>
#include "datagram.h"

class UdpChat : public QObject
{
    Q_OBJECT
public:
    UdpChat(const short &_id, const int &_port, QObject *parent = nullptr);
    void calculateDataSize(int &currentSizeSetting);
    void sendMessage(const QString &msg, const short &resvId);
    ~UdpChat();

private:
    QUdpSocket *socket;
    short userId;
    int port;
    unsigned short msgId = 0;
    int dataSize = (256 - 42) / 2;
    QMap<unsigned short, QMap<unsigned short, QVector<std::pair<int, QString>>>> packageBufferOutcomming;
    //    Receiver ID          Message ID           (packege Number, Message)

    QMap<unsigned short, QMap<unsigned short, QVector<std::pair<int, QString>>>> packageBufferIncomming;
    //     Sender ID           Message ID           (packege Number, Message)

    void sendDatagram(Datagram &_datagram);

    static bool compare(std::pair<int, QString> &first, std::pair<int,QString> &second);

    std::list<QString> separateMessage(const QString &msg);

    quint16 caclulateChecksum(const QString &msg);

    QString unionPackages(QVector <std::pair<int, QString>> &packs);

    bool isEqualChecksum(QString &msg, quint16 &incomingChecksum);

    void packageRequest(unsigned short &recvId, unsigned short &_msgId);

    void sendReceipt(unsigned short &recvId, unsigned short &_msgId);

    void getReceipt(unsigned short &recvId, unsigned short &_msgId);

    void increaseMsgId();

signals:
    void sendDataToIncoming(QString message);

    void sendDataToOutcoming(QString message);

public slots:
    void read();
};

#endif // UDPCHAT_H
