// header : protocol.h
// note : Collection of communication protocol related functions
#ifndef PROTOCOL_H
#define PROTOCOL_H

/* HEADER BEGIN */
#include "stm32f0xx_hal.h"
#include "string.h"
#include "stdlib.h"
/* HEADER END */

/* MACRO BEGIN */
#define DATALENGTH	8

// Check State
// IDLE 	->  NOTHING
// Far   	-> 	HeadLight OFF
// Close 	-> 	HeadLight BLINK
// KEYOFF 	->  User's information Send
// KEYON	->  User's information Receive
#define IDLE			100
#define FAR				  0	//0000
#define CLOSE			  1 //0000
#define KEYOFF		      2 //0010
#define KEYON		      3 //0011

/* MACRO END */

/* STRUCT & TYPE BEGIN */
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

typedef struct{
	uint8_t Air_Dir_Data;
	uint8_t Air_Speed_Data;
	uint8_t Seat_UpDown_Data;
	uint8_t Seat_RightLeft_Data;
	uint8_t Side_UpDown_Data;
	uint8_t Side_RightLeft_Data;
}ProtocolData;
/* STRUCT & TYPE END */

/* VARIABLES BEGIN */
extern uint8_t RX_Data[DATALENGTH];
extern UART_HandleTypeDef huart3;
extern ProtocolFlag FlagInfo;
extern ProtocolData DataInfo;
extern uint32_t Rx_flag;
extern uint32_t Rx_it_source;
extern uint8_t data;
extern uint8_t index_rx;
/* VARIABLES END */

/* FUNCTION BEGIN */
void Uart_Init();
void Uart_Handler();
void Check_Protocol();
void Comm_UartWrite(uint8_t function1, uint8_t function2, uint32_t data);
void TestProtocol();

void Send_sideMirror(uint8_t pwm1, uint8_t pwm2);
uint8_t Check_CloseState();
uint8_t Check_KeyState();
uint8_t Check_newman();
uint8_t Receieve_UDsideMirror();
uint8_t Receieve_RLsideMirror();

/* FUNCTION END */

#endif
