#ifndef HOST_H
#define HOST_H

#include <QObject>

class IDevice;

class Host : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(int port WRITE setPort NOTIFY portChanged)

    IDevice* m_device;

public:
    explicit Host(QObject *parent = nullptr);

public slots:
    void setPort(int newPort);
    void setAddress(const QString &newAddress);
    Q_INVOKABLE bool openConnection();
    Q_INVOKABLE bool closeConnection();

signals:    
    void addressChanged();
    void portChanged();
};

#endif // HOST_H

/*El tamaño de la PDU MODBUS está limitado
 *-La restricción de tamaño heredada de la primera implementación MODBUS en la red de línea serie (máx. RS485 ADU = 256 bytes).
 *Por lo tanto: TCP MODBUS ADU = 253 bytes + MBAP (7 bytes) = 260 bytes.
*/

/*Reglas de implementación
 *-Se recomienda mantener abierta la conexión TCP con un dispositivo
 * remoto y no abrirla y cerrarla para cada transacción MODBUS / TCP.
 * Observación: Sin embargo, el cliente MODBUS debe ser capaz de aceptar
 *              una solicitud de cierre del servidor y cerrar la conexión.
 *              La conexión se puede volver a abrir cuando sea necesario.
 *
 *-Se recomienda que un cliente MODBUS abra un mínimo de conexiones TCP
 * con un servidor MODBUS remoto (con la misma dirección IP). Una conexión
 * por aplicación podría ser una buena opción.
 *
 *-Se pueden activar varias transacciones MODBUS simultáneamente en la misma
 * conexión TCP.
 * Observación: Si se hace esto, se debe utilizar el identificador de transacción
 * MODBUS para identificar de manera única las solicitudes y respuestas coincidentes.
 *
 *-En caso de una comunicación bidireccional entre dos entidades MODBUS remotas
 * (cada una de ellas es cliente y servidor), es necesario abrir conexiones
 * separadas para el flujo de datos del cliente y para el flujo de datos del servidor.
*/
