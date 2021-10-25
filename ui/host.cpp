#include <QDebug>
#include "host.h"
#include "client.h"
#include "server.h"

Host::Host(QObject *parent) : QObject(parent)
{
//    m_device = new modBus::Client(this);
    m_device = new modBus::Server(this);
}

bool Host::openConnection()
{
    return m_device->openConnection();
}

bool Host::closeConnection()
{
    return m_device->closeConnection();
}

void Host::setAddress(const QString &newAddress)
{
    m_device->setAddress(newAddress);
    emit addressChanged();
}

void Host::setPort(int newPort)
{
    m_device->setPort(newPort);
    emit portChanged();
}
