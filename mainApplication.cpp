#include "mainApplication.h"

#include <QDebug>
#include <QCoreApplication>

mainApplication::mainApplication(const QString &program, const QString usbPort, bool invert, QObject *parent) :
    QObject(parent)
{
    m_InvertRts = invert;

    // start subprocess
    m_StartProgramm.start(program, QStringList() << "");

    // check state
    if(m_StartProgramm.state() == QProcess::Running)
    {
        m_IsInit = true;
        qInfo() << "The program was successfully launched:" << program;
    }
    else    // something went wrong -> exit
    {
        qWarning() << "Could not start programm, please check path." << program;
        QCoreApplication::quit();
        return;
    }

    // create timer, to check the application state
    m_Timer.setInterval(100);
    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(sl_CheckApp()));
    m_Timer.start();

    // create serial
    m_Port = new Serial_Port(usbPort);

    // open serial port
    m_Port->openPort();

    // set RTS
    m_Port->setRTS(!m_InvertRts);

    qInfo() << "RTS is set" << m_InvertRts;
}

mainApplication::~mainApplication()
{
    qInfo() << "Finish application";
    if(m_Port != nullptr)
    {
        m_Port->setRTS(m_InvertRts);
        m_Port->closePort();
        delete m_Port;
        m_Port = nullptr;
    }
    m_StartProgramm.close();
}

bool mainApplication::isInit() const
{
    return m_IsInit;
}

void mainApplication::sl_CheckApp()
{
    if(m_StartProgramm.state() != QProcess::Running)
    {
        qInfo() << "Main Application closed, exit Program";

        m_Port->setRTS(m_InvertRts);
        qInfo() << "RTS is set" << !m_InvertRts;

        QCoreApplication::quit();
    }
}
