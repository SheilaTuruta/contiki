#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "lib/random.h"
#include "sys/ctimer.h"
#include "sys/etimer.h"
#include "rpl.h"
#include "simple-udp.h"

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "dev/leds.h"

#include "board-spi-tcc.h"

static struct etimer et_temperature_process;

PROCESS(temperature_process, "temperature process");

AUTOSTART_PROCESSES(&temperature_process);


/*---------------------------------------------------------------------------*/
PROCESS_THREAD(temperature_process, ev, data)
{
  float temp [3] ;
  int temp_int = 0;
  int resultado_int [3] ;
  float resultado_intm [3] ;
  uint16_t resultado_fc [3];
  int i;

  enable_spi_pin(23,22, 4);
  enable_spi_pin(24,27,12);
  enable_spi_pin(28,29,15);
  GPIO_setOutputEnableDio(26, GPIO_OUTPUT_ENABLE); // pin enable 3.3V
  GPIO_writeDio(26, 1);

  PROCESS_BEGIN();

  etimer_set(&et_temperature_process, 1*CLOCK_SECOND);


   while(1){
    PROCESS_WAIT_EVENT();

         // sck - clock / cs - chip select / so - serial data output
    temp [0] = temperature_read(23,22, 4);
    temp [1] = temperature_read(24,27,12);
    temp [2] = temperature_read(28,29,15);

    for (i=0; i<3; i++){
         temp[i] = temp[i]*25;
         resultado_int[i] = temp[i]/100;
         resultado_intm[i]  = ((temp[i] /100)-resultado_int[i] );
         resultado_fc[i]  = (resultado_intm[i] )*100;
        // printf("temperatura sensor %i: %i.%u °C\n", i+1, resultado_int[i] , resultado_fc[i] );
         printf("\n temperatura sensor %i: %i.%u °C\n", i+4, resultado_int[i] , resultado_fc[i] );
    }
    printf("\n");
    etimer_reset(&et_temperature_process);
   }
   PROCESS_END();
}
