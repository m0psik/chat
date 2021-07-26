#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);

    int getUdpSize();
    void setUdpSize(int &_udpSize);

private:
    int udpSize;
};

#endif // SETTINGS_H
