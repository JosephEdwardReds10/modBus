#ifndef SOCKET_H
#define SOCKET_H
#include <QObject> // Para quitar este include, hay que hacer la
                   // la sustitucion por string.h
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h> /* Ver NOTAS manual Linux*/
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace tcp {

// Class Socket is interface of BSD (Berkeley Software Distribution)

class Socket
{
    struct sockaddr_in m_socketLocalAddress;
    struct sockaddr_in m_socketRemoteAddress;
    int m_socket;
    bool m_isCreatedSocket;
    bool m_isConnecting;
    bool m_isSetLocalSocket;
    bool m_isSetRemoteSocket;
    bool m_isBoundSocket;
    bool m_isListend;

public:

    enum Domain
    {
        UNIX,
        INET
    };

    explicit Socket(Domain domain = Domain::INET);

    const QString &ip() const;
    uint16_t port() const;

    bool isConnecting() const;
    bool isCreatedSocket() const;
    bool isSetLocalSocket() const;
    bool isSetRemoteSocket() const;
    bool isBoundSocket() const;
    bool isListend() const;

    void setLocalSocket(const QString &address,  uint16_t port);
    void setRemoteSocket(const QString &address, uint16_t port);

    void createSocket(); //ok
    void bindSocket(); // ok
    void connectSocket(); //ok
    void listenn();
    void listenn2();
    void sendFrame();
    void recFrame();
    void disconnect(); // ok

private:
    Socket::Domain m_domain;
    bool setSocket(struct sockaddr_in& socketAddress, const QString &address, uint16_t port);
};

//Communication break between two operational end points:

//- If no packet is currently sent on the connection:
//  The communication break will not be seen if it lasts less than the Keep Alive timer
//  value. If the communication break lasts more than the Keep Alive timer value, an
//  error is returned to the TCP Management layer that can reset the connection.
//- If Some packets are sent before and after the disconnection:
//  The TCP retransmission algorithms (Jacobson's, Karn's algorithms and exponential
//  backoff. See section 4.3.2) are activated. This may lead to a stack TCP layer Reset
//  of the Connection before the Keep Alive timer is over.

}
#endif // SOCKET_H
