#include "serial_port.h"


Serial_Port::Serial_Port(const QString &portName, QObject *parent) :
    QObject(parent)
{
    port=new QextSerialPort(portName, QextSerialPort::EventDriven);
}

int Serial_Port::openPort()
{
    // Make sure things are clear
    int iReturnValue = 0;
    port->close();

    if(port->open(QIODevice::ReadWrite))
    {
        // yust a placeholder
        port->setBaudRate(BAUD115200);
        emit(portOpened());
    }
    else
    {
        qWarning() << "Could not open Port";
    }

    return iReturnValue;
}


void Serial_Port::closePort()
{
    try
    {
        port->close();
    }catch(std::exception& e){;}
    //timer->stop();
    emit(portClosed());
}


QStringList Serial_Port::getAvailablePorts()
{
    int i;
    QList<QString> AvailablePorts;
    AvailablePorts.reserve(11);
    QString portToTest = "COM";
    for(i=1;i<10;i++)
    {
        portToTest.append(QString::number(i,10));
        port->setPortName(portToTest);
        if(port->open(QIODevice::ReadWrite))
        {
            AvailablePorts.append(portToTest);
            port->close();
        }
        portToTest.remove(3,1);
    }
    portToTest.insert(0,"\\\\.\\");
    for(i=10;i<20;i++)
    {
        portToTest.append(QString::number(i,10));
        port->setPortName(portToTest);
        if(port->open(QIODevice::ReadWrite))
        {
            AvailablePorts.append(portToTest);
            port->close();
        }
        portToTest.remove(7,2);
    }
    return AvailablePorts;
}


void Serial_Port::setDTR(bool set)
{
    port->setDtr(set);
}


void Serial_Port::setRTS(bool set)
{
    port->setRts(set);
}
