#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "shmlib.h"

#include "uartinterface.h"
#include "protocol.h"

char buffer[BUFFER_SIZE];
int buffer_length = 0;



int main() {
    uint8_t close_flag=0;
    uint8_t far_flag=0;
    uint8_t off_flag=0;
    
    int shmkey = 0x33333333;
    shm_t* shm = shm_initialize(shmkey);
    usleep(1000000);
    update_data(shm,0);

    // Initialize UART ports
    int uart4 = open_serial_port(UART4, B115200); //bt
    int uart2 = open_serial_port(UART2, B115200); //sheet
    int uart3 = open_serial_port(UART3, B115200); //headlight

    if (uart4 < 0 || uart2 < 0 || uart3 < 0) {
        printf("Error opening serial ports\n");
        return 1;
    }
    // flaginfo.Key_On_Flag=1;
    char read_buf[256]; // Buffer for storing received data
    int read_size;

    while (1) {
        // Read and check protocol for each UART port
        if (read_from_serial_port(uart4, read_buf, sizeof(read_buf)) > 0) {
            printf("Received from UART4: %s\n", read_buf);
            Check_Protocol(read_buf);
        }

        if (read_from_serial_port(uart2, read_buf, sizeof(read_buf)) > 0) {
            printf("Received from UART2: %s\n", read_buf);
            Check_Protocol(read_buf);
        }

        if (read_from_serial_port(uart3, read_buf, sizeof(read_buf)) > 0) {
            printf("Received from UART3: %s\n", read_buf);
            Check_Protocol(read_buf);
        }

          if(flaginfo.Key_Close_Flag==1 && close_flag==0){
        
            usleep(100);
            Comm_UartWrite(uart3,'W','K',0001,'\0');            
            printf("close\n");
            close_flag=1;
        }
          if (flaginfo.Key_Close_Flag == 0) {
            close_flag=0;  
        }
        if(flaginfo.Key_Far_Flag==1 && far_flag==0){
        
            usleep(100);
            Comm_UartWrite(uart3,'W','K',0000,'\0');            
            printf("far\n");
            far_flag=1;
        }
          if (flaginfo.Key_Far_Flag == 0) {
            far_flag=0;  
        }
        if(flaginfo.Key_On_Flag==1 && data_flag_check()==1){
                update_data(shm,1);
            
            
            usleep(100);

            send_all_data(uart2,'W');
            send_all_data(uart3,'W');
            Comm_UartWrite(uart3,'W','K',0000,'\0');            


            printf("key on\n");

            clear_data_flag();
        }

        //
         if(flaginfo.Key_Off_Flag==1 && off_flag==0)
         {
            Comm_UartWrite(uart2,'W','K',10,'\0');
            Comm_UartWrite(uart3,'W','K',10,'\0');
            off_flag=1;
            //for ECU2 only test
            // flaginfo.Side_UpDown_Flag =1; //for test
            // flaginfo.Side_RightLeft_Flag =1;    //for test

            //for ECU3 only test
            // flaginfo.Seat_UpDown_Flag =1; //for test
            // flaginfo.Seat_RightLeft_Flag =1;    //for test
            // flaginfo.Air_Dir_Flag =1; //for test
            // flaginfo.Air_Speed_Flag =1;    //for test
         }
         else if(flaginfo.Key_Off_Flag==1 && data_flag_check()==1)
         {
            update_data(shm,0);
            
            usleep(100);
            send_all_data_delay(uart4,'R');

            printf("key off\n");

            clear_data_flag();
            off_flag=0;  
        }

        // Add a y to ease the CPU usage
        usleep(100); // 100 milliseconds
    }

    // Close UART ports
    close_serial_port(uart4);
    close_serial_port(uart2);
    close_serial_port(uart3);

    return 0;
}