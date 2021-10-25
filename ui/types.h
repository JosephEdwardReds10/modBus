#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <iostream>
#include <QObject>
#include <QDebug>

struct MemoryAddress
{
    MemoryAddress()
        : m_type('N'), m_module(0), m_number(0)
    {

    }
    MemoryAddress(char type, uint8_t module, uint8_t number)
        : m_type(type), m_module(module), m_number(number)
    {

    }

    ~MemoryAddress() = default;

    char type() const { return m_type; }
    uint8_t module() const { return m_module; }
    uint8_t number() const { return m_number; }
    std::string address() const { return type() + std::to_string(m_module) + "." + std::to_string(m_number); }

    bool operator==(const MemoryAddress &m) const
    {
        return type() == m.type() && module() == m.module() && number() == m.number();
    };

    void setAddress(char type, uint8_t module, uint8_t number)
    {
        m_type = type;
        m_module = module;
        m_number = number;
    }

private:
    char m_type;
    uint8_t m_module;
    uint8_t m_number;
};

/*inline*/ std::ostream& operator<<(std::ostream& os, const MemoryAddress &a)
{
    os << a.address().c_str();
    return os;
};

struct digital
{
    std::string tag;
    MemoryAddress address;
    bool status;
};

template <typename T>
struct Register
{
    std::string tag;
    uint32_t memoryAddress;
    T value;
    Register() {}
};

struct DiscretesInput // Read-Only
{ // This type of data can be provided by an I/O system.
    std::vector<digital> inputs;
    DiscretesInput(int inputs) : inputs(inputs) {}

    void set(const MemoryAddress &address, const bool status)
    {
        for(auto item = inputs.begin(); item != inputs.end(); item++)
        {
            if(address == item->address)
                item->status = status;
        }
    }
};

struct Coils // Read-Write
{ // This type of data can be alterable by an application program.
    std::vector<digital> coils;
    Coils(int coils) : coils(coils) {}

    void set(const MemoryAddress &address, const bool status)
    {
        for(auto item = coils.begin(); item != coils.end(); item++)
        {
            if(address == item->address)
                item->status = status;
        }
    }
};

struct InputRegisters
{ // This type of data can be provided by an I/O system [Read-Only]
    std::vector<Register<uint32_t>> inputs;
    InputRegisters() {}
};

struct HoldingRegisters // Read-Write
{ // This type of data can be alterable by an application program.
    std::vector<Register<uint32_t>> holding;
    HoldingRegisters() {}
};

struct MBAPHeader
{
    uint16_t transactionIdentifier;
    uint16_t protocolIdentifier;
    uint16_t length;
    uint8_t  unitIdentifier;

    MBAPHeader()
        : transactionIdentifier(0), protocolIdentifier(0), length(0), unitIdentifier(0)
//        : transactionIdentifier(513), protocolIdentifier(0), length(775), unitIdentifier(0)
    {

    }

    QByteArray toBuffer() const
    {
        QByteArray data;
        data.reserve(7);

        for(auto byte = constBegin; byte != constEnd; byte++)
            data.append(*byte);

        return data;
    }

    void FromBuffer(const char *buffer)
    {
        if(buffer == nullptr)
            return;

        for(auto byte = begin; byte != end; byte++, buffer++)
            *byte = *buffer;
    }

    bool FromBuffer(const char *buffer, const char * const end)
    {
        if(buffer == nullptr || end == nullptr)
            return false;

        for(auto byte = begin; byte != this->end; byte++, buffer++)
            *byte = *buffer;

        return buffer == (end + 1);
    }

private:
    char *begin { reinterpret_cast<char*>(&transactionIdentifier) };
    char *end   { reinterpret_cast<char*>(&unitIdentifier + 1) };

    //Falta probar este cambio.
    const char *constBegin { reinterpret_cast<const char*>(begin) };
    const char *constEnd   { reinterpret_cast<const char*>(end) };

//    const char *constBegin { reinterpret_cast<const char*>(&transactionIdentifier) };
//    const char *constEnd   { reinterpret_cast<const char*>(&unitIdentifier + 1) };

};

inline QDebug operator<<(QDebug debug, const MBAPHeader &h)
{
    debug << "{ transactionIdentifier:" << h.transactionIdentifier
          << " protocolIdentifier:" << h.protocolIdentifier
          << " length:" << h.length
          << " unitIdentifier:" << h.unitIdentifier << " }";
    return debug;
};

#endif // TYPES_H
