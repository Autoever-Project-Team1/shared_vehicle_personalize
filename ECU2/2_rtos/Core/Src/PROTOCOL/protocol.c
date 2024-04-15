// header : protocol.c
// note : Collection of communication protocol related functions

#include "PROTOCOL/protocol.h"
#include "usart.h"

/* VARIABLES BEGIN */
ProtocolFlag FlagInfo;
ProtocolData DataInfo;
uint8_t RX_Data[DATALENGTH];
uint32_t Rx_flag = 0;
uint32_t Rx_it_source = 0;
uint8_t data = 0;
uint8_t index_rx = 0;

// Receieve User's data
uint8_t rx_side_updown = 0;
uint8_t rx_side_rightleft = 0;
uint8_t state = IDLE;
/* VARIABLES END */

void Uart_Init()
{
	MX_USART3_UART_Init();
   HAL_UART_Receive_IT(&huart3, (uint8_t*)RX_Data, DATALENGTH);
}

void Comm_UartWrite(uint8_t function1, uint8_t function2, uint32_t data)
{
   uint8_t TX_Data[8] = {0,};
   TX_Data[0] = '<';
   TX_Data[1] = 'R';
   TX_Data[2] = function1;
   TX_Data[3] = function2;
   TX_Data[4] = (data / 100) + '0';
   TX_Data[5] = ((data % 100) / 10) + '0';
   TX_Data[6] = (data % 10) + '0';
   TX_Data[7] = '>';
   HAL_UART_Transmit(&huart3,(uint8_t*)TX_Data, DATALENGTH, 10);
}

void Uart_Handler()
{
	Rx_flag = __HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE);
	Rx_it_source = __HAL_UART_GET_IT_SOURCE(&huart3, UART_IT_RXNE);

	if ((Rx_flag != RESET) && (Rx_it_source != RESET)) {
		 /* 1Byte copy */
		 data = (uint8_t)(huart3.Instance->RDR & (uint8_t)0x00FF);
		 RX_Data[index_rx] = data;
		 index_rx++;
	}
	else;

	if(index_rx >= 8)
	{
		Check_Protocol();

		index_rx = 0;
	}
}

void Check_Protocol()
{
	if(strncmp(RX_Data, "<WAH--->", 4) == 0 && RX_Data[7] == '>')
	{
		FlagInfo.Air_Dir_Flag = 1;
		DataInfo.Air_Dir_Data = ((RX_Data[4] -'0') * 100) + ((RX_Data[5] -'0') * 10) + (RX_Data[6] -'0');
	}
	else if(strncmp(RX_Data, "<WAL--->", 4) == 0 && RX_Data[7] == '>')
	{
		FlagInfo.Air_Speed_Flag = 1;
		DataInfo.Air_Speed_Data = ((RX_Data[4] -'0') * 100) + ((RX_Data[5] -'0') * 10) + (RX_Data[6] -'0');
	}
	else if(strncmp(RX_Data, "<WCH--->", 4) == 0 && RX_Data[7] == '>')
	{
		FlagInfo.Seat_UpDown_Flag = 1;
		DataInfo.Seat_UpDown_Data = ((RX_Data[4] -'0') * 100) + ((RX_Data[5] -'0') * 10) + (RX_Data[6] -'0');
	}
	else if(strncmp(RX_Data, "<WCL--->", 4) == 0 && RX_Data[7] == '>')
	{
		FlagInfo.Seat_RightLeft_Flag = 1;
		DataInfo.Seat_RightLeft_Data = ((RX_Data[4] -'0') * 100) + ((RX_Data[5] -'0') * 10) + (RX_Data[6] -'0');
	}
	else if(strncmp(RX_Data, "<WSH--->", 4) == 0 && RX_Data[7] == '>')
	{
		FlagInfo.Side_UpDown_Flag = 1;
		DataInfo.Side_UpDown_Data = ((RX_Data[4] -'0') * 100) + ((RX_Data[5] -'0') * 10) + (RX_Data[6] -'0');
		rx_side_updown = DataInfo.Side_UpDown_Data;
	}
	else if(strncmp(RX_Data, "<WSL--->", 4) == 0 && RX_Data[7] == '>')
	{
		FlagInfo.Side_RightLeft_Flag = 1;
		DataInfo.Side_RightLeft_Data = ((RX_Data[4] -'0') * 100) + ((RX_Data[5] -'0') * 10) + (RX_Data[6] -'0');
		rx_side_rightleft = DataInfo.Side_RightLeft_Data;
	}
	else if(strncmp(RX_Data, "<WK0001>", 8) == 0)
	{
		FlagInfo.Key_Close_Flag = 1;
	}
	else if(strncmp(RX_Data, "<WK0000>", 8) == 0)
	{
		FlagInfo.Key_Far_Flag = 1;
	}
	else if(strncmp(RX_Data, "<WK0010>", 8) == 0)
	{
		FlagInfo.Key_Off_Flag = 1;
	}
	else if(strncmp(RX_Data, "<WK0011>", 8) == 0)
	{
		FlagInfo.Key_On_Flag = 1;
	}
	else;
}

void TestProtocol()
{
	Comm_UartWrite('A', 'H', DataInfo.Air_Dir_Data);
	Comm_UartWrite('A', 'L', DataInfo.Air_Speed_Data);
	Comm_UartWrite('C', 'H', DataInfo.Seat_UpDown_Data);
	Comm_UartWrite('C', 'L', DataInfo.Seat_RightLeft_Data);
	Comm_UartWrite('S', 'H', DataInfo.Side_UpDown_Data);
	Comm_UartWrite('S', 'L', DataInfo.Side_RightLeft_Data);

	if(FlagInfo.Key_Close_Flag == 1)
	{
		Comm_UartWrite('K', '0', 001);
		FlagInfo.Key_Close_Flag  = 0;
	}
	else if(FlagInfo.Key_Far_Flag == 1)
	{
		Comm_UartWrite('K', '0', 000);
		FlagInfo.Key_Far_Flag  = 0;
	}
	else if(FlagInfo.Key_Off_Flag == 1)
	{
		Comm_UartWrite('K', '0', 010);
		FlagInfo.Key_Off_Flag = 0;
	}
	else if(FlagInfo.Key_On_Flag == 1)
	{
		Comm_UartWrite('K', '0', 011);
		FlagInfo.Key_On_Flag  = 0;
	}
}

// pwm1 : up down motor
// pwm2 : right left motor
void Send_sideMirror(uint8_t pwm1, uint8_t pwm2)
{
	DataInfo.Side_UpDown_Data = pwm1;
	DataInfo.Side_RightLeft_Data = pwm2;
	Comm_UartWrite('S', 'H', DataInfo.Side_UpDown_Data);
	HAL_Delay(100);
	Comm_UartWrite('S', 'L', DataInfo.Side_RightLeft_Data);
}

uint8_t Check_CloseState()
{
	if (FlagInfo.Key_Close_Flag == 1 && FlagInfo.Key_Far_Flag == 0)
	{
		state = CLOSE;
		FlagInfo.Key_Close_Flag = 0;
	}
	if (FlagInfo.Key_Close_Flag == 0 && FlagInfo.Key_Far_Flag == 1)
	{
		state = FAR;
		FlagInfo.Key_Far_Flag = 0;
	}
	return state;
}

uint8_t Check_KeyState()
{
	if (FlagInfo.Key_On_Flag == 1 && FlagInfo.Key_Off_Flag == 0)
	{
		state = KEYON;
		FlagInfo.Key_On_Flag = 0;
	}
	if (FlagInfo.Key_On_Flag == 0 && FlagInfo.Key_Off_Flag == 1)
	{
		state = KEYOFF;
		FlagInfo.Key_Off_Flag = 0;
	}
	return state;
}

uint8_t Receieve_UDsideMirror()
{
	if (FlagInfo.Side_UpDown_Flag == 1)
	{
		rx_side_updown = DataInfo.Side_UpDown_Data;
		if (rx_side_updown > 80 || rx_side_updown < 60 || rx_side_updown == 0) rx_side_updown = 70;
		FlagInfo.Side_UpDown_Flag = 0;
	}
	return rx_side_updown;
}

uint8_t Receieve_RLsideMirror()
{
	if (FlagInfo.Side_RightLeft_Flag == 1)
	{
		rx_side_rightleft = DataInfo.Side_RightLeft_Data;
		if (rx_side_rightleft > 80 || rx_side_rightleft < 60 || rx_side_updown == 0) rx_side_rightleft = 72;
		FlagInfo.Side_RightLeft_Flag = 0;
	}
	return rx_side_rightleft;
}
