#include "protocol.h"
#include "uartinterface.h" // UART 인터페이스 헤더 파일 포함
#include <stdio.h>
#include <string.h>
#include <unistd.h>


 ProtocolFlag flaginfo;
 ProtocolData dataInfo;

void initialize_protocol(void) {
    memset(&flaginfo, 0, sizeof(flaginfo));
    memset(&dataInfo, 0, sizeof(dataInfo));
}

// 이전에 정의된 Check_Protocol 함수와 플래그/데이터 구조체 정의 이후


//프로토콜을 준수하는 패킷 저장하는 함수
void Check_Protocol(const char* frame)
{
    if (strncmp(frame, "<RAH", 4) == 0 && frame[7] == '>') 
	{
        flaginfo.Air_Dir_Flag = 1;
        dataInfo.Air_Dir_Data = ((frame[4] - '0') * 100) + ((frame[5] - '0') * 10) + (frame[6] - '0');
        printf("Log: Air Direction Data updated to %d\n", dataInfo.Air_Dir_Data);

    }
	else if (strncmp(frame, "<RAL", 4) == 0 && frame[7] == '>') 
	{
        flaginfo.Air_Speed_Flag = 1;
        dataInfo.Air_Speed_Data = ((frame[4] - '0') * 100) + ((frame[5] - '0') * 10) + (frame[6] - '0');
        printf("Log: Air Speed Data updated to %d\n", dataInfo.Air_Speed_Data);    
    }
	else if (strncmp(frame, "<RCH", 4) == 0 && frame[7] == '>') 
	{
        flaginfo.Seat_UpDown_Flag = 1;
        dataInfo.Seat_UpDown_Data = ((frame[4] - '0') * 100) + ((frame[5] - '0') * 10) + (frame[6] - '0');
        printf("Log: Seat Up/Down Data updated to %d\n", dataInfo.Seat_UpDown_Data);
    }
	else if (strncmp(frame, "<RCL", 4) == 0 && frame[7] == '>') 
	{
        flaginfo.Seat_RightLeft_Flag = 1;
        dataInfo.Seat_RightLeft_Data = ((frame[4] - '0') * 100) + ((frame[5] - '0') * 10) + (frame[6] - '0');
        printf("Log: Seat Right/Left Data updated to %d\n", dataInfo.Seat_RightLeft_Data);
    } 
	else if (strncmp(frame, "<RSH", 4) == 0 && frame[7] == '>') 
	{
        flaginfo.Side_UpDown_Flag = 1;
        dataInfo.Side_UpDown_Data = ((frame[4] - '0') * 100) + ((frame[5] - '0') * 10) + (frame[6] - '0');
        printf("Log: Side Up/Down Data updated to %d\n", dataInfo.Side_UpDown_Data);
    }
	else if (strncmp(frame, "<RSL", 4) == 0 && frame[7] == '>') 
	{
        flaginfo.Side_RightLeft_Flag = 1;
        dataInfo.Side_RightLeft_Data = ((frame[4] - '0') * 100) + ((frame[5] - '0') * 10) + (frame[6] - '0');
        printf("Log: Side Right/Left Data updated to %d\n", dataInfo.Side_RightLeft_Data);
    }
	else if (strncmp(frame, "<WK0001>", 8) == 0) 
	{
        flaginfo.Key_Close_Flag = 1;
        flaginfo.Key_Far_Flag=0;
        printf("Log: Key Close Flag set\n");
    }
	else if (strncmp(frame, "<WK0000>", 8) == 0) 
	{
        flaginfo.Key_Far_Flag = 1;
        flaginfo.Key_Close_Flag=0;
        printf("Log: Key Far Flag set\n");
    }
	else if (strncmp(frame, "<WK0010>", 8) == 0) 
	{
        flaginfo.Key_Off_Flag = 1;
        printf("Log: Key Off Flag set\n");

    } 
	else if (strncmp(frame, "<WK0011>", 8) == 0) 
	{
        flaginfo.Key_On_Flag = 1;
        printf("Log: Key On Flag set\n");
    }
}


//받은 데이터를 처리하는 함수
void process_recieved_data(int fd, PortInfo* portInfo) {
    char data;
    int bytes_read = read_from_serial_port(fd, &data, 1);

    if (bytes_read > 0) {
        portInfo->buffer[portInfo->buffer_index++] = data;

        if (data == '>') {
            char* frame_start = strchr(portInfo->buffer, '<');
            if (frame_start) {
                char* frame_end = strchr(frame_start, '>');
                if (frame_end) {
                    *frame_end = '\0'; // 프레임의 끝을 널 문자로 대체
                    printf("Received frame: %s\n", frame_start); //
                    Check_Protocol(frame_start);
                    memmove(portInfo->buffer, frame_end + 1, BUFFER_SIZE - (frame_end - portInfo->buffer) - 1);
                    portInfo->buffer_index -= (frame_end - frame_start) + 1;
                }
            }
        }

        if (portInfo->buffer_index >= BUFFER_SIZE - 1) {
            memset(portInfo->buffer, 0, BUFFER_SIZE);
            portInfo->buffer_index = 0;
        }
    }
}



//버퍼에 읽어오는 함수
int uart_read_packet(int uart_filestream, char* buffer, size_t buf_size) {
    char read_buf[256]; // 임시로 데이터를 읽어올 큰 버퍼
    memset(read_buf, 0, sizeof(read_buf));

    int bytes_read = read(uart_filestream, read_buf, sizeof(read_buf) - 1);
    if (bytes_read <= 0) {
        // 데이터 읽기 실패 또는 데이터가 없음
        return -1;
    }

    // '<' 시작 문자 찾기
    char* start = strchr(read_buf, '<');
    char* end = strchr(read_buf, '>');
    if (start == NULL || end == NULL || end <= start) {
        // 유효하지 않은 패킷
        return -1;
    }

    // 데이터 길이 계산 (시작과 끝 문자 제외)
    int data_length = end - start - 1;
    if (data_length <= 0 || data_length >= buf_size) {
        // 데이터 길이가 부적절하거나 버퍼 크기 초과
        return -1;
    }

    // 데이터 복사
    memcpy(buffer, start + 1, data_length);
    buffer[data_length] = '\0'; // NULL 문자로 종료

     printf("Received packet: %s\n", buffer);

    return data_length;
}


//
//function1:프로토콜 1번째 문자, function2 : 프로토콜 2번째 문자, function3 : '\0' -> 문자 2개 / 아니면 3번라면 문자
void Comm_UartWrite(int uart_fd, char function1, char function2, uint32_t data, char function3) {
    char TX_Data[DATALENGTH+1];
    if (function3 != '\0') {
        // 세 번째 함수 코드가 제공된 경우 (char 3개)
        snprintf(TX_Data, sizeof(TX_Data), "<%c%c%c%03d>", function1, function2, function3, data);
    } else {
        // 세 번째 함수 코드가 제공되지 않은 경우 (3번째변수 '\0')
        snprintf(TX_Data, sizeof(TX_Data), "<%c%c%04d>", function1, function2, data);
    }

    int bytes_written = send_to_serial_port(uart_fd, TX_Data, strlen(TX_Data));

    if (bytes_written > 0) {
        printf("Sent %d bytes: %s\n", bytes_written, TX_Data);
    } else {
        printf("Failed to send data.\n");
    }
}

//uart 포트로 저장된 데이터 보내는 함수
void send_all_data(int uart_fd,char sign){
    Comm_UartWrite(uart_fd,sign,'K',11,'\0'); //keyon
    Comm_UartWrite(uart_fd,sign,'A',dataInfo.Air_Dir_Data,'H'); //
    Comm_UartWrite(uart_fd,sign,'A',dataInfo.Air_Speed_Data,'L'); //
    Comm_UartWrite(uart_fd,sign,'C',dataInfo.Seat_UpDown_Data,'H'); //
    Comm_UartWrite(uart_fd,sign,'C',dataInfo.Seat_RightLeft_Data,'L'); //
    Comm_UartWrite(uart_fd,sign,'S',dataInfo.Side_UpDown_Data,'H'); //
    Comm_UartWrite(uart_fd,sign,'S',dataInfo.Side_RightLeft_Data,'L'); //
}
//
void send_all_data_delay(int uart_fd,char sign){
    Comm_UartWrite(uart_fd,sign,'K',11,'\0'); //keyon
    usleep(10000);
    Comm_UartWrite(uart_fd,sign,'A',dataInfo.Air_Dir_Data,'H'); // 
    usleep(10000);
    Comm_UartWrite(uart_fd,sign,'A',dataInfo.Air_Speed_Data,'L'); //
    usleep(10000);
    Comm_UartWrite(uart_fd,sign,'C',dataInfo.Seat_UpDown_Data,'H'); //
    usleep(10000);
    Comm_UartWrite(uart_fd,sign,'C',dataInfo.Seat_RightLeft_Data,'L'); //
    usleep(10000);
    Comm_UartWrite(uart_fd,sign,'S',dataInfo.Side_UpDown_Data,'H'); //
    usleep(10000);
    Comm_UartWrite(uart_fd,sign,'S',dataInfo.Side_RightLeft_Data,'L'); //
    usleep(10000);
}
// 모든 seat, side, air 플래그가 1인지 검사
int data_flag_check() {
    if (flaginfo.Air_Dir_Flag == 1 &&
        flaginfo.Air_Speed_Flag == 1 &&
        flaginfo.Seat_UpDown_Flag == 1 &&
        flaginfo.Seat_RightLeft_Flag == 1 &&
        flaginfo.Side_UpDown_Flag == 1 &&
        flaginfo.Side_RightLeft_Flag == 1) {
        return 1;  
    } else {
        return 0;
    }
}

//데이터 도착 플래그를 0으로 모두 초기화
void clear_data_flag(){
    flaginfo.Key_On_Flag=0;
    flaginfo.Key_Off_Flag=0;
    flaginfo.Air_Dir_Flag =0;
    flaginfo.Air_Speed_Flag =0;
    flaginfo.Seat_UpDown_Flag =0;
    flaginfo.Seat_RightLeft_Flag =0;
    flaginfo.Side_UpDown_Flag =0;
    flaginfo.Side_RightLeft_Flag =0;
}
