
#include "swinterrupt3.h"
#include "ambient.h"
#include "shmlib.h" //ipc shared memory mutex
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

    
    //posix shm using mutex init
    int shmkey = 0x33333333;
    shm_t* shm = shm_initialize(shmkey);

    int r, data=0;
    ws2811_return_t ret;

    //led_handler init
    matrix_initialize();
    setup_handlers();

    //setup switch
    setupSwitches();

    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) 
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        exit(1); 
    }
   
    while (running) 
    {
        //sharedmemory read
        // 0 : key_off, 1 : key_on
        data = read_data(shm, &r);
        
        //key_on
        if(data==1)
        {
            // brigthness conversion switch
            AmbientLight_Update_Brightness();
            // motion conversion switch
            update_motion();
            //render
            matrix_render();

            // 30frames/sec

            if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS)
            {
                fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
                break;
            }
        }

        //key off
        else
        {
            matrix_clear();
            matrix_render();
            if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS) 
            {
                fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
                break;
            }
        }

        // 30frames/sec        
        usleep(1000000/30 );
    }
     ws2811_fini(&ledstring);

    return 0;

    
    }