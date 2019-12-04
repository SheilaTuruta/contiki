/*
 * temperature.c
 *
 *  Created on: Nov 18, 2019
 *      Author: mint
 */



#include "contiki.h"
#include "ti-lib.h"
#include <stdio.h> /* For printf() */
#include "dev/leds.h"
#include "dev/pins.h"

//#include "platform/srf06-cc26xx/common/board-spi-tcc.h"
#include "board-spi-tcc.h"

#include <inttypes.h>
/**************************************************************************************/
static struct etimer et_hello;

# define LED_PING_EVENT 0x2C
# define LED_PONG_EVENT 0x2D
/**************************************************************************************/
PROCESS(hello_world_process, "Hello world process");
/**************************************************************************************/
AUTOSTART_PROCESSES(&hello_world_process);

PROCESS_THREAD(hello_world_process, ev, data)
{
 PROCESS_BEGIN();

  uint32_t buf[20];
  //char* bit_info;
  uint32_t bit_info;
 // size_t ilen = 12;

//  etimer_set(&et_hello, 5*CLOCK_SECOND);
 // PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
//  process_post(&pong_process,LED_PING_EVENT,(void *)(& hello_world_process));
  GPIO_setOutputEnableDio(21, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(22, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(23, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(24, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(25, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(26, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(27, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(28, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(29, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(30, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(12, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(3, GPIO_OUTPUT_DISABLE);
  GPIO_setOutputEnableDio(4, GPIO_OUTPUT_DISABLE);

/*
  GPIO_setOutputEnableDio(21, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(22, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(23, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(24, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(25, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(26, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(27, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(28, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(29, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(30, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(12, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(11, GPIO_OUTPUT_ENABLE);
  GPIO_setOutputEnableDio(15, GPIO_OUTPUT_ENABLE);*/

  //GPIO_setOutputEnableDio(29, GPIO_OUTPUT_ENABLE);  // escrita de pino
  //GPIO_setOutputEnableDio(27, GPIO_OUTPUT_ENABLE);  // escrita de pino
  //GPIO_setOutputEnableDio(26, GPIO_OUTPUT_DISABLE);  // leitura de pino
  //etimer_set(&et_hello, CLOCK_SECOND * 1);
  //count = 0;
//  board_spi_open(490, BOARD_IOID_DIO29);
 // GPIO_writeDio(29, 1);

  while(1) {
   // PROCESS_WAIT_EVENT();
   // if(ev == PROCESS_EVENT_TIMER){
       // process_post(&pong_process,LED_PING_EVENT,(void *)(& hello_world_process));
      //  leds_toggle(LEDS_RED);
      //  pins_toggle(BOARD_IOID_DIO25);
      //  board_spi_read(buf, ilen);

        //printf("clock_wait 2s\n");
// escrita de pino
        //clock_wait(2*CLOCK_SECOND);//s?
        printf("clock_wait 2s\n");
        clock_wait(2*CLOCK_SECOND);

      //  GPIO_toggleDio(29);
      //  clock_delay_usec(1000);
       // bit_info = (unsigned int)GPIO_readDio(BOARD_IOID_DIO29);
       // bit_info = GPIO_readDio(26);
       // printf("leitura do pino: %X \n\n", bit_info);
       // printf("leitura do pino2: %lu \n", (unsigned int)GPIO_readDio(BOARD_IOID_DIO26));
      //  printf("leitura do pino3: %" PRIu32 "\n", bit_info);

        //spi_read_tcc(*buf, 16, 26, 29, 27); //(uint8_t *buf, size_t len, uint32_t SO_dioNumber, uint32_t SCLK_dioNumber, uint32_t CS_dioNumber){    // lembrar de habilitar os pinos
        //enable_spi_pin(29,27,26);
       // enable_spi_pin(29,27,15);
        uint16_t v;


        //GPIO_writeDio(27, 0);  // chip select
        //v = spi_read2_tcc();       // Leitura da parte alta - Primeiros 8 bits de dados
        //v = temperature_read(29,27,15);
        //v <<= 8;             // Desloca 8 posições para a esquerda
       // v |= spi_read2_tcc();
        //GPIO_writeDio(27, 1);  // chip select
//spi_read_tcc(uint8_t *buf, size_t len, uint32_t SO_dioNumber, uint32_t SCLK_dioNumber, uint32_t CS_dioNumber){    // lembrar de habilitar os pinos
        //v >>= 3;
        //float resultado = v*25;
        //int resultado_int = resultado/100;
        //float resultado_intm = ((resultado/100)-resultado_int);
        //uint16_t resultado_fc = (resultado_intm)*100;


      /*  GPIO_toggleDio(21);
        GPIO_toggleDio(22);
        GPIO_toggleDio(23);
        GPIO_toggleDio(24);
        GPIO_toggleDio(25);
        GPIO_toggleDio(26);
        GPIO_toggleDio(27);
        GPIO_toggleDio(28);
        GPIO_toggleDio(29);
        GPIO_toggleDio(30);
        GPIO_toggleDio(11);
        GPIO_toggleDio(12);
        GPIO_toggleDio(15);*/

        printf("\n pin21: %u °C", GPIO_readDio(21));
        printf("\n pin22: %u °C", GPIO_readDio(22));
        printf("\n pin23: %u °C", GPIO_readDio(23));
        printf("\n pin24: %u °C", GPIO_readDio(24));
        printf("\n pin25: %u °C", GPIO_readDio(25));
        printf("\n pin26: %u °C", GPIO_readDio(26));
        printf("\n pin27: %u °C", GPIO_readDio(27));
        printf("\n pin28: %u °C", GPIO_readDio(28));
        printf("\n pin29: %u °C", GPIO_readDio(29));
        printf("\n pin30: %u °C", GPIO_readDio(30));
        printf("\n pin11: %u °C", GPIO_readDio(11));
        printf("\n pin12: %u °C", GPIO_readDio(12));
        printf("\n pin4: %u °C\n", GPIO_readDio(4));
        printf("\n pin3: %u °C\n", GPIO_readDio(3));

   // }

 }

  PROCESS_END();
}
