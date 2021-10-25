#ifndef APPLICATIONDATAUNIT_H
#define APPLICATIONDATAUNIT_H

#include <QObject>
#include "protocolDataUnit.h"
namespace modBus {

class ApplicationDataUnit: public QObject
{
    Q_OBJECT


    ProtocolDataUnit m_protocolDataUnit;
    qint16 m_frameLength;
public:
    virtual ~ApplicationDataUnit() = default;

    quint16 frameLength() const { return m_frameLength; }
};

struct MBAPHeader // MODBUS Application Protocol header
{
    quint16 transactionIdentifier;
    const quint16 protocolIdentifier {0};
    quint16 length;
    quint8 unitIdentifier;
};

class ApplicationDataUnitTCP : public ApplicationDataUnit
{
    Q_OBJECT
    MBAPHeader m_MBAPHeader;
    const quint16 lengthADU {0}; // Maximmun length Application Data Unit by TCP

public:
    explicit ApplicationDataUnitTCP(QObject *parent = nullptr);

signals:

};

struct AdditionalAddress
{

};

class ApplicationDataUnitGeneral : public ApplicationDataUnit // Modbus RTU [serial line]
{
    Q_OBJECT
    AdditionalAddress m_additionalAddress;
    int m_errorcheck;
public:
};

}
#endif // APPLICATIONDATAUNIT_H
