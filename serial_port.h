#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QStringList>
#include <QByteArray>
#include <QDebug>

#include "3rdparty/qextserialport/src/qextserialport.h"

#include <QString>

class QextSerialPort;

class Serial_Port : public QObject
{
    Q_OBJECT

public:
    explicit Serial_Port(const QString &portName, QObject *parent = 0);
    QStringList getAvailablePorts();
    void setDTR(bool set = true);
    void setRTS(bool set = true);

private:
    QextSerialPort *port;

signals:
    void portOpened();
    void portClosed();

public slots:
    int openPort();
    void closePort();
};

#endif // SERIAL_PORT_H
