#include <QCoreApplication>
#include <QThread>
#include <QCommandLineParser>
#include <QProcess>

#include "mainApplication.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption usbPort("p", "Set USB-Port (required). Note Ports above 9 musst be specified like this: \"\\\\\\\\.\\\\COM10\"", "usb_port_name");
    parser.addOption(usbPort);

    QCommandLineOption startProgram("c", "Start command (optional)", "command", "C:\\Program Files\\SDR-Radio.com (V3-26)\\SDR Console.exe");
    parser.addOption(startProgram);

    QCommandLineOption invertRts("i", "Invert RTS (optional)");
    parser.addOption(invertRts);

    parser.process(a);

    if(!parser.isSet("p"))
    {
        qWarning() << "You need to set the port!";
        return 0;
    }

    QString program = "C:\\Program Files\\Notepad++\\notepad++.exe";
//    QString program = "C:\\Program Files\\SDR-Radio.com (V3-26)\\SDR Console.exe";
    if(parser.isSet("c"))
        program = parser.value(startProgram);

    bool invert = false;
    if(parser.isSet("i"))
        invert = true;

    mainApplication app(program, parser.value(usbPort), invert);
    if(!app.isInit())
    {
        return -1;
    }

    return a.exec();
}
