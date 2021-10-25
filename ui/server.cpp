#include "server.h"
#include <QDebug>

namespace modBus{

void Server::setPort(int newPort)
{
    if (m_localPort == newPort)
        return;
    m_localPort = newPort;
}

void Server::setAddress(const QString &newAddress)
{
    if (m_Address == newAddress)
        return;
    m_Address = newAddress;
}

bool Server::openConnection()
{
    m_socket.createSocket();
    m_socket.bindSocket();
    m_socket.listenn2();
    return m_socket.isListend();
}

int Server::send(const char buffer, int size)
{
    Q_UNUSED(buffer)
    Q_UNUSED(size)
    return 0;
}

int Server::receive(const char buffer, int size)
{
    Q_UNUSED(buffer)
    Q_UNUSED(size)
    return 0;
}

bool Server::closeConnection()
{
    m_socket.disconnect();
    return m_socket.isConnecting();
}

}
