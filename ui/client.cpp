#include "client.h"

namespace modBus{

Client::Client(QObject *parent) : QObject(parent), m_socket()
{

}

void Client::setPort(int newPort)
{
    if (m_localPort == newPort)
        return;
    m_localPort = newPort;
}

void Client::setAddress(const QString &newAddress)
{
    if (m_Address == newAddress)
        return;
    m_Address = newAddress;
}

bool Client::openConnection()
{
    m_socket.createSocket();
    m_socket.setRemoteSocket(m_Address, m_localPort);
    m_socket.connectSocket();
    return m_socket.isConnecting();
}

int Client::send(const char buffer, int size)
{
    Q_UNUSED(buffer)
    Q_UNUSED(size)
    return 0;
}

int Client::receive(const char buffer, int size)
{
    Q_UNUSED(buffer)
    Q_UNUSED(size)
    return 0;
}

bool Client::closeConnection()
{
    m_socket.disconnect();
    return m_socket.isConnecting();
}

}
