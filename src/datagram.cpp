#include "datagram.h"
#include <iostream>
Datagram::Datagram(const QString &_msg,
                   const short &_recvId,
                   const short &_sendId,
                   const short &_msgId,
                   const qint8 &_type,
                   const qint16 &_packageNumber,
                   const quint16 &_checkSum,
                   QObject *parent):
    QObject(parent)
{
    msg = _msg;
    recvId = _recvId;
    sendId = _sendId;
    msgId = _msgId;
    type = _type;
    packageNumber = _packageNumber;
    isEnd = false;
    checkSum = _checkSum;
}

Datagram::Datagram(const QByteArray &_datagram, QObject *parent):
    QObject(parent)
{
    data=_datagram;
}

Datagram& Datagram::operator=(Datagram &other){
    msg = other.msg;
    sendId = other.sendId;
    recvId = other.recvId;
    msgId = other.msgId;
    type = other.type;
    packageNumber = other.packageNumber;
    isEnd = other.isEnd;
    checkSum = other.checkSum;
    data = other.data;
    return *this;
}

Datagram::~Datagram(){}

void Datagram::datagramParse(){
    QDataStream in(&data, QIODevice::ReadOnly);
    in >> recvId >> sendId >> msgId >> type >> packageNumber >> isEnd >> msg >> checkSum;
}

void Datagram::datagarmAssemble(){
    QByteArray res;
    QDataStream out(&res, QIODevice::WriteOnly);
    out << quint16(recvId);
    out << quint16(sendId);
    out << quint16(msgId);
    out << quint8(type);
    out << quint16(packageNumber);
    out << bool(isEnd);
    out << msg;
    out << quint16(checkSum);
    data = res;
}

QByteArray Datagram::getData(){
    return data;
}

quint16 Datagram::getCheckSum(){
    return checkSum;
}

bool Datagram::getEndFlag(){
    return isEnd;
}

QString Datagram::getMessage(){
    return msg;
}

unsigned short Datagram::getReceiverId(){
    return recvId;
}

unsigned short Datagram::getSenderId(){
    return sendId;
}

unsigned short Datagram::getMessageId(){
    return msgId;
}

qint8 Datagram::getType(){
    return type;
}

unsigned short Datagram::getPackageNumber(){
    return packageNumber;
}

void Datagram::setEndFlag(){
    isEnd = true;
}




