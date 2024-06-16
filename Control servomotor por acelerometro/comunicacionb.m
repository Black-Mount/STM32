clear puerto_serial
puerto_serial = serialport("COM2",9600,"DataBits",8,"Timeout",100)

pause(0.1);

write(puerto_serial,180,"uint8")
pause(0.1);

clear puerto_serial