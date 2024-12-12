# RS232 to Websocket

This programm connects to Serial Port of a Linux/Windows machine
and provides a websocket to receive and provide unaltered signals.

The system will pipe all incoming signals from the client to the wheel and vice versa and is compatible to RS232 signals.

このプログラムはLinux/Windowsマシンのシリアルポートに接続し
に接続し、変更されていない信号を受信して提供するウェブソケットを提供します。

このシステムは、クライアントからホイールへ、またはその逆へ、すべての受信信号をパイプし、RS232信号と互換性があります。


# Build
- Make Makefile `cmake .`
- Build with `make`

# Dependencies
This project makes use of c++ boost 1.86
- beast:: for websocket
- asio:: for serial communication


# Arguments


Example
```
-log /var/log/rs232soc.log  
-sp /dev/ttyS0
-a 127.0.0.1
-p 8989
-t 3
```

- *-log* Destination of logfile (remove if no log is needed)
- *-sp* the COM/Serial port that will used
- *-a* remmote address
- *-p* server port for websocket
- *-t* threaths for listener (default: 1)


Usage:
```
./rs232soc -log /var/log/rs232.log -sp /dev/ttyS0 -a 127.0.0.1 -p 8989
```

