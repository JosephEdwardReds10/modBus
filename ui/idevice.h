#ifndef IDEVICE_H
#define IDEVICE_H

#include <QObject>
#include <QQmlEngine>

#define IDevice_iid "IDevice_iid/1.0"

class IDevice //Sera una clase abstracta
{
    QML_INTERFACE
public:
    virtual ~IDevice() = default;

    virtual void setPort(int newPort) = 0;
    virtual void setAddress(const QString &newAddress) = 0;

    virtual bool openConnection() = 0;
    virtual int  send(const char buffer, int size) = 0;
    virtual int  receive(const char buffer, int size) = 0;
    virtual bool closeConnection() = 0;
};

Q_DECLARE_INTERFACE(IDevice, IDevice_iid);

#endif // IDEVICE_H
