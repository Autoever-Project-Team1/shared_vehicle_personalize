#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//datalen, buf_Size,port num
#define DATALENGTH 8
#define BUFFER_SIZE 256
#define PORT_COUNT 3

//buffer
typedef struct {
    char buffer[BUFFER_SIZE];
    int buffer_index;
} PortInfo;

//data update flag 1 : update / 0 : no
typedef struct{
	uint8_t Air_Dir_Flag;
	uint8_t Air_Speed_Flag;
	uint8_t Seat_UpDown_Flag;
	uint8_t Seat_RightLeft_Flag;
	uint8_t Side_UpDown_Flag;
	uint8_t Side_RightLeft_Flag;
	uint8_t Key_Close_Flag;
	uint8_t Key_Far_Flag;
	uint8_t Key_Off_Flag;
	uint8_t Key_On_Flag;
}ProtocolFlag;

//save recieved data
typedef struct{
	uint8_t Air_Dir_Data;
	uint8_t Air_Speed_Data;
	uint8_t Seat_UpDown_Data;
	uint8_t Seat_RightLeft_Data;
	uint8_t Side_UpDown_Data;
	uint8_t Side_RightLeft_Data;
}ProtocolData;

//extern global variavbles
extern ProtocolFlag flaginfo;
extern ProtocolData datainfo;

//method
void initialize_protocol(void);
void print_flag_status();
void process_received_data(int fd, PortInfo* portInfo);
void Check_Protocol(const char* frame);
void Comm_UartWrite(int uart_fd, char function1, char function2, uint32_t data, char function3);
int uart_read_packet(int uart_filestream, char* buffer, size_t buf_size);
void send_all_data(int uart_fd,char sign);
void send_all_data_delay(int uart_fd,char sign);
int data_flag_check();
void clear_data_flag();

#endif // PROTOCOL_H

