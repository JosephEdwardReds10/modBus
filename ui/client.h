#ifndef CLIENT_H
#define CLIENT_H

#include "idevice.h"
#include "socket.h"

namespace modBus{

class Client : public QObject, public IDevice
{
    Q_OBJECT
    Q_INTERFACES(IDevice)

    tcp::Socket m_socket;
    QString m_Address;
    uint16_t m_localPort;

public:
    explicit Client(QObject *parent = nullptr);

public slots:
    void setPort(int newPort) override;
    void setAddress(const QString &newAddress) override;
    bool openConnection() override;
    int  send(const char buffer, int size) override;
    int  receive(const char buffer, int size) override;
    bool closeConnection() override;

signals:
};

}
#endif // CLIENT_H
