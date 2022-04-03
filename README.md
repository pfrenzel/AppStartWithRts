# Start an application and automatically set the RTS line of a USB-Seriel converter.

This program has the purpose to start another program and at the same time to set the RTS line of a USB-Seriel converter. When the program is terminated, the RTS line is automatically reset. This allows an external hardware to be triggered automatically.

The program has three parameters:

```
  -?, -h, --help      Displays this help.
  -p <usb_port_name>  Set USB-Port (required). Note Ports above 9 musst be
                      specified like this: "\\\\.\\COM10"
  -c <command>        Start command (optional)
  -i                  Invert RTS (optional)
```

## Using Windows-Shortcut
A shortcut can be created, eliminating the need to use the command line.
The parameters must be adjusted in the link for this. Simply add the necessary parameters under Target.

## Compile
The program can be used on both Linux and Windows. Qt5 must be installed.