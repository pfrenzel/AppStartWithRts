#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QProcess>
#include <QTimer>

#include "serial_port.h"

class mainApplication : public QObject
{
    Q_OBJECT
public:
    mainApplication(const QString &program, const QString usbPort, bool invert, QObject *parent = 0);
    ~mainApplication();
    bool isInit() const;

private slots:
    void sl_CheckApp();

private:
    Serial_Port *m_Port = nullptr;
    QProcess m_StartProgramm;
    bool m_IsInit = false;
    bool m_InvertRts = false;
    QTimer m_Timer;
};

#endif // MAINAPPLICATION_H
