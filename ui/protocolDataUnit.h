#ifndef PROTOCOLDATAUNIT_H
#define PROTOCOLDATAUNIT_H

#include <QObject>

namespace modBus {

struct ProtocolDataUnit
{
    int functionCode;
    QByteArray data;
};

}
#endif // PROTOCOLDATAUNIT_H
