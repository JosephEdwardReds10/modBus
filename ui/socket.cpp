#include "socket.h"
#include "QDebug"

namespace tcp {

const int OPERATION_FAILED {-1};

void resetFlags()
{
    qDebug() << Q_FUNC_INFO;
}

Socket::Socket(Domain domain)
    : m_socket(-1), m_isCreatedSocket(false), m_isConnecting(false), m_isSetLocalSocket(false),
      m_isSetRemoteSocket(false), m_isBoundSocket(false), m_isListend(false), m_domain(domain)
{
//     setsockopt();
//    tcp_keepalive_time();
}

const QString &Socket::ip() const { return QString("m_ip"); }

uint16_t Socket::port() const { return htons(m_socketLocalAddress.sin_port);/*m_port*/; }

bool Socket::isCreatedSocket() const { return m_isCreatedSocket/*m_socket >= 0*/; }

bool Socket::isSetLocalSocket() const { return m_isSetLocalSocket; }

bool Socket::isSetRemoteSocket() const { return m_isSetRemoteSocket; }

bool Socket::isBoundSocket() const { return m_isBoundSocket; }

bool Socket::isListend() const { return m_isListend; }

bool Socket::isConnecting() const { return m_isConnecting; }

void Socket::createSocket()
{
    if (isCreatedSocket())
        return;

    try {
        m_socket = socket( (m_domain == Domain::INET ? AF_INET : AF_UNIX), SOCK_STREAM, 0 );

        m_isCreatedSocket = !(m_socket == OPERATION_FAILED);

        if(isCreatedSocket())
            qDebug() << "[System]: Socket creation succefull:" << m_socket;
        else
            qDebug() << "[CLIENT]: Socket creation failed:" << m_socket << strerror( errno );

    } catch (...) {
        qDebug() << "socket() thorw exception";
    }
}

void Socket::setLocalSocket(const QString &address, uint16_t port)
{
    if(isConnecting() || isBoundSocket())
        return;
    m_isSetLocalSocket = setSocket(m_socketLocalAddress, address, port);
}

void Socket::setRemoteSocket(const QString &address, uint16_t port)
{
    if(isConnecting())
        return;
    m_isSetRemoteSocket = setSocket(m_socketRemoteAddress, address, port);
}

void Socket::connectSocket()
{
    if(isConnecting() || !isSetRemoteSocket())
        return;

    int connection = connect(m_socket, (struct sockaddr*)&m_socketRemoteAddress, sizeof(m_socketRemoteAddress));

    m_isConnecting = (connection >/*!=*/ OPERATION_FAILED);

    if(!isConnecting())
        qDebug() << "When trying to establish the connection with the server, an error occurred." << strerror( errno );
}

void Socket::sendFrame()
{
    const char frame[] = "Hola, Que tal! Perro.";
    if (write(m_socket, frame, sizeof (frame)) < 0)
        qDebug() << "write; failed";
}

void Socket::recFrame()
{
    char buffer[] = "Hola! perro";
    fputs("Received: ", stdout);
    int numBytes = recv(m_socket, buffer, sizeof(buffer) - 1, 0);
    if (numBytes < 0)
        qDebug() <<"recv() failed";
    else if (numBytes == 0)
    {
        qDebug() << "recv() connection closed prematurely";
        //Debemos de cerrar el socket es este lado.
    }
    fputs(buffer, stdout);
}

void Socket::bindSocket()
{
    if(m_isBoundSocket || !m_isCreatedSocket)
        return;

    int binded = bind(m_socket, (struct sockaddr *)&m_socketLocalAddress, sizeof(m_socketLocalAddress));

    m_isBoundSocket = !(binded == OPERATION_FAILED);

    if (m_isBoundSocket)
        qDebug() << "[System]: socket bind succesfull" << binded;
    else
        qDebug() << "[System]: socket bind failed" << binded << strerror( errno );
}

void Socket::listenn()
{
    unsigned int len;     /* length of client address */
    struct sockaddr_in client;
    int connfd;
    int  len_rx = 0;                     /* received and sent length, in bytes */
    char buff_rx[260];   /* buffers for reception  */
    char buff_tx[260];   /* buffers for reception  */

    if ((listen(m_socket, /*BACKLOG*/5)) == OPERATION_FAILED)
    {
        qDebug() << "[SERVER-error]: socket listen failed " << strerror( errno );
        return /*false*/;
    }
    else
    {
        qDebug() << "[SERVER]: Listening on SERV_PORT";
    }

    //**********************************
    len = sizeof(client);

    /* Accept the data from incoming sockets in a iterative way */
    while(1)
    {
        connfd = accept(m_socket, (struct sockaddr *)&client, &len);
        if (connfd < 0)
        {
            qDebug() << "[SERVER-error]: connection not accepted." << strerror( errno );
        }
        else
        {
            while(1) /* read data from a client socket till it is closed */
            {
                /* read client message, copy it into buffer */
                len_rx = read(connfd, buff_rx, sizeof(buff_rx));

                if(len_rx == -1)
                {
                    qDebug() << "[SERVER-error]: connfd cannot be read." << strerror( errno );
                }
                else if(len_rx == 0) /* if length is 0 client socket closed, then exit */
                {
                    qDebug() << "[SERVER]: client socket closed";
                    close(connfd);
                    break;
                }
                else
                {
                    write(connfd, buff_tx, strlen(buff_tx));
                    qDebug() << "[SERVER]: %s \n" << buff_rx;
                }
            }
        }
    }
    //**********************************
}

void Socket::listenn2()
{
    if(!isBoundSocket())
        return;

    int listenning = listen(m_socket, /*BACKLOG*/5);

    m_isListend = !(listenning == OPERATION_FAILED);

    if (isListend())
        qDebug() << "[System]: server is listening" << listenning;
    else
        qDebug() << "[System]: socket listen failed " << strerror( errno );
}

void Socket::disconnect()
{
    if(isConnecting())
        return;

    int connection = close(m_socket);

    m_isConnecting  = (connection == OPERATION_FAILED);

    if(isConnecting())
        qDebug() << "[System]: Disconnect failed " << connection << strerror( errno );
    else
    {
        qDebug() << "[System]: Disconnect succesfull " << connection;
        resetFlags();
        m_isCreatedSocket=false;
        m_isConnecting=false;
        m_isSetLocalSocket=false;
        m_isSetRemoteSocket=false;
        m_isBoundSocket=false;
        m_isListend=false;
        m_socket=-1;
    }
}

bool Socket::setSocket(sockaddr_in &socketAddress, const QString &address, uint16_t port)
{
    memset(&socketAddress, 0, sizeof (socketAddress));
    socketAddress.sin_family = m_domain == Domain::INET ? AF_INET : AF_UNIX;
    socketAddress.sin_port   = htons(port);

    try {
        socketAddress.sin_addr.s_addr = inet_addr(address.toStdString().c_str());
    } catch (...) {
        qDebug() << "La conversion de la direccion causo una excepcion";
    }

    if(socketAddress.sin_addr.s_addr != INADDR_NONE)
        return true;
    else
        return false;
}

}
