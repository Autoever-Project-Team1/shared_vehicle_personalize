//uartinterface.h

#ifndef UARTINTERFACE_H
#define UARTINTERFACE_H

#include <stddef.h>
#include <termios.h>

//uart serial port
#define     UART1   "/dev/ttyS0"   //uart1
#define     UART2   "/dev/ttyAMA1" //uart2
#define     UART3   "/dev/ttyAMA2" //uart3 
#define     UART4   "/dev/ttyAMA3" //uart4 

//baud rate
#define BAUDRATE B115200

//uart method

//uart 포트 여는 함수
int open_serial_port(const char *device, int rate);

//uart 포트 닫는 함수
void close_serial_port(int fd);

//uart 포트(fd)에서 데이터를 읽어오는 함수
int read_from_serial_port(int fd, char *buffer, size_t size);

//uart 포트(fd)에 데이터를 쓰는 함수
int send_to_serial_port(int fd, const char *data, size_t length);

#endif