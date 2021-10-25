#ifndef SERVER_H
#define SERVER_H

#include "idevice.h"
#include "socket.h"

namespace modBus{

class Server : public QObject, public IDevice
{
    Q_OBJECT
    Q_INTERFACES(IDevice)

    tcp::Socket m_socket;
    QString m_Address;
    uint16_t m_localPort;

public:
    explicit Server(QObject * parent = nullptr) : QObject(parent), m_socket() {}

public slots:
    void setPort(int newPort) override;
    void setAddress(const QString &newAddress) override;

    bool openConnection() override;
    int send(const char buffer, int size) override;
    int receive(const char buffer, int size) override;
    bool closeConnection() override;
};

}

#endif // SERVER_H
