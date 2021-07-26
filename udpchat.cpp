#include "udpchat.h"

bool UdpChat::compare(std::pair<int, QString> &first, std::pair<int,QString> &second){
    return first.first > second.first;
}

UdpChat::UdpChat(const short &_id, const int &_port, QObject *parent):
    QObject(parent)
{
    userId = _id;
    port = _port;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, port);
    connect(socket,
            SIGNAL(readyRead()),
            this,
            SLOT(read()));
}

UdpChat::~UdpChat(){
    delete socket;
}

quint16 UdpChat::caclulateChecksum(const QString &msg){
    QByteArray src = msg.toUtf8();
    return qChecksum(src.data(), src.length());
}

// SEND MESSAGE
void UdpChat::calculateDataSize(int &currentSizeSetting){
    dataSize = (currentSizeSetting - 42) / 2;
}

void UdpChat:: sendDatagram(Datagram &_datagram){
    _datagram.datagarmAssemble();
    socket->writeDatagram(_datagram.getData(), QHostAddress::LocalHost, port);
}

void UdpChat::sendMessage(const QString &msg, const short &recvId){
    quint16 checkSum = caclulateChecksum(msg);
    std::list<QString> packs = separateMessage(msg);
    quint16 iterator = 0;
    increaseMsgId();
    while (!packs.empty()){
        iterator += 1;
        Datagram datagram (packs.front(), recvId, userId, msgId, '1', iterator, checkSum);
        packageBufferOutcomming[recvId][msgId].append(std::make_pair(iterator,packs.front()));
        if (packs.size()==1){
            datagram.setEndFlag();
        }
        sendDatagram(datagram);
        packs.pop_front();
    }
}

std::list<QString> UdpChat::separateMessage(const QString &msg){
    std::list<QString> res;
    for (int i=0; i<msg.size(); i+=dataSize){
        res.push_back(msg.mid(i,dataSize));
    }
    return res;
}

// RECEIVE MESSAGE
QString UdpChat::unionPackages(QVector<std::pair<int, QString>> &packs){
    std::sort(packs.begin(), packs.end(), compare);
    QString res;
    while (!packs.empty()){
        res += packs.back().second;
        packs.pop_back();
    }
    return res;
}

bool UdpChat::isEqualChecksum(QString &msg, quint16 &incomingChecksum){
    return caclulateChecksum(msg) == incomingChecksum;
}

void UdpChat::read(){
    QByteArray data;
    data.resize(socket->pendingDatagramSize());
    QHostAddress *addr = new QHostAddress();
    socket->readDatagram(data.data(), data.size(), addr);
    Datagram datagram(data);
    datagram.datagramParse();
    if (datagram.getReceiverId() != userId){
        return;
    }
    QString incomingMessage = datagram.getMessage();
    unsigned short senderId = datagram.getSenderId();
    unsigned short incomingMessageId = datagram.getMessageId();
    unsigned short packageNumber = datagram.getPackageNumber();
    if (datagram.getType() == '0'){
        getReceipt(senderId,incomingMessageId);
    }
    packageBufferIncomming[senderId][incomingMessageId].append(std::make_pair(packageNumber,incomingMessage));
    if (!datagram.getEndFlag()){
        return;
    }
    QString msg = unionPackages(packageBufferIncomming[senderId][incomingMessageId]);
    quint16 incomingChecksum = datagram.getCheckSum();
    if (isEqualChecksum(msg,incomingChecksum)){
        sendReceipt(senderId,incomingMessageId);
        emit sendDataToIncoming(msg);
    }
}

void UdpChat::increaseMsgId(){
    msgId == 60000 ? msgId = 0 : msgId += 1;
}

void UdpChat::sendReceipt(unsigned short &recvId, unsigned short &_msgId){
    Datagram datagram("", recvId, userId, _msgId, '0', 1, caclulateChecksum(""));
    sendDatagram(datagram);
}

void UdpChat::getReceipt(unsigned short &recvId, unsigned short &_msgId){
    QString msg = unionPackages(packageBufferOutcomming[recvId][_msgId]);
    packageBufferOutcomming[recvId].remove(_msgId);
    emit sendDataToOutcoming(msg);
}

void UdpChat::packageRequest(unsigned short &recvId, unsigned short &_msgId){
 // запрос пакетов
}
