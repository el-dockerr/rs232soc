# RS232 to Websockety

This programm connects to Serial Port of a Linux/Windows machine
and provides a websocket to receive and provide unaltered signals.

The system will pipe all incoming signals from the client to the wheel and vice versa and is compatible to RS232 signals.


# Build
- Make Makefile `cmake .`
- Build with `make`

# Dependencies
This project makes use of c++ boost 1.86
- beast:: for websocket
- asio:: for serial communication


# Arguments


Example:
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

