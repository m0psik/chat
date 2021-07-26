#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    udpSize = 256;
}

int Settings::getUdpSize(){
    return udpSize;
}

void Settings::setUdpSize(int &_udpSize){
    udpSize = _udpSize;
}
