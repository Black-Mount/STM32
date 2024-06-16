clc
delete(instrfind({'Port'},{'COM2'}));
puerto_serial=serial('COM2')
puerto_serial.BaudRate=9600;

fopen(puerto_serial)


