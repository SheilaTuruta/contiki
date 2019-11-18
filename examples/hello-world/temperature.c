/*
 * temperature.c
 *
 *  Created on: Nov 18, 2019
 *      Author: mint
 */



#include "contiki.h"

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

  GPIO_setOutputEnableDio(29, GPIO_OUTPUT_ENABLE);  // escrita de pino
  GPIO_setOutputEnableDio(27, GPIO_OUTPUT_ENABLE);  // escrita de pino
  GPIO_setOutputEnableDio(26, GPIO_OUTPUT_DISABLE);  // leitura de pino
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

        printf("clock_wait 2s\n");
// escrita de pino
        GPIO_toggleDio(29);
        clock_wait(2*CLOCK_SECOND);//s?

      //  GPIO_toggleDio(29);
      //  clock_delay_usec(1000);
       // bit_info = (unsigned int)GPIO_readDio(BOARD_IOID_DIO29);
       // bit_info = GPIO_readDio(26);
       // printf("leitura do pino: %X \n\n", bit_info);
       // printf("leitura do pino2: %lu \n", (unsigned int)GPIO_readDio(BOARD_IOID_DIO26));
      //  printf("leitura do pino3: %" PRIu32 "\n", bit_info);

        spi_read_tcc(*buf, 16, 26, 29, 27); //(uint8_t *buf, size_t len, uint32_t SO_dioNumber, uint32_t SCLK_dioNumber, uint32_t CS_dioNumber){    // lembrar de habilitar os pinos

        uint16_t v;


        GPIO_writeDio(27, 0);  // chip select
        v = spi_read2_tcc();       // Leitura da parte alta - Primeiros 8 bits de dados
        v <<= 8;             // Desloca 8 posições para a esquerda
        v |= spi_read2_tcc();
        GPIO_writeDio(27, 1);  // chip select
//spi_read_tcc(uint8_t *buf, size_t len, uint32_t SO_dioNumber, uint32_t SCLK_dioNumber, uint32_t CS_dioNumber){    // lembrar de habilitar os pinos
        v >>= 3;
        float resultado = v*25;
        int resultado_int = resultado/100;
        float resultado_intm = ((resultado/100)-resultado_int);
        uint16_t resultado_fc = (resultado_intm)*100;
        printf("\n temperatura: %i.%u °C\n", resultado_int, resultado_fc);


   // }

 }

  PROCESS_END();
}
