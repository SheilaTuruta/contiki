/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"

#include <stdio.h> /* For printf() */
#include "dev/leds.h"
#include "dev/pins.h"

//#include "platform/srf06-cc26xx/common/board-spi-tcc.h"
#include "board-spi-tcc.h"

#include <inttypes.h>

# define LED_PING_EVENT 0x2C
# define LED_PONG_EVENT 0x2D
/*---------------------------------------------------------------------------*/
static struct etimer et_hello;
static struct etimer et_blink;
static struct etimer et_proc3;
//static struct etimer et_pong;
static uint16_t count;

/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
PROCESS(blink_process, "LED blink process");
PROCESS(proc3_process, "Hello world process");
PROCESS(pong_process, "Pong process");
/*---------------------------------------------------------------------------*/
//AUTOSTART_PROCESSES(&blink_process);
AUTOSTART_PROCESSES(&hello_world_process,&blink_process,&proc3_process,&pong_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(proc3_process, ev, data)
{
  PROCESS_BEGIN();

  etimer_set(&et_proc3, 2*CLOCK_SECOND);
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);

  //process_post(&pong_process,LED_PING_EVENT,(void*)(&proc3_process));

  etimer_set(&et_proc3, CLOCK_SECOND * 1);
  count = 0;
  while(1) {
    PROCESS_WAIT_EVENT();
    if(ev == PROCESS_EVENT_TIMER){
        if (process_post(&pong_process,LED_PING_EVENT,(void*)(&proc3_process))==0){
                printf("Enviando ping do proc3_process para o pong_process");
        }
        etimer_reset(&et_proc3);
        printf("PROCESSO 3 A CADA 1s GOGOGO\n");
    }
    if(ev == LED_PONG_EVENT){
        printf("Recebido LED PONG EVENT no processo: proc3_process\n");
    }
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();

  uint32_t buf[20];
  //char* bit_info;
  uint32_t bit_info;
 // size_t ilen = 12;

  etimer_set(&et_hello, 5*CLOCK_SECOND);
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
//  process_post(&pong_process,LED_PING_EVENT,(void *)(& hello_world_process));

  GPIO_setOutputEnableDio(29, GPIO_OUTPUT_ENABLE);  // escrita de pino
  GPIO_setOutputEnableDio(27, GPIO_OUTPUT_ENABLE);  // escrita de pino
  GPIO_setOutputEnableDio(26, GPIO_OUTPUT_DISABLE);  // leitura de pino
  etimer_set(&et_hello, CLOCK_SECOND * 1);
  count = 0;
//  board_spi_open(490, BOARD_IOID_DIO29);
 // GPIO_writeDio(29, 1);

  while(1) {
    PROCESS_WAIT_EVENT();
    if(ev == PROCESS_EVENT_TIMER){
        process_post(&pong_process,LED_PING_EVENT,(void *)(& hello_world_process));
        leds_toggle(LEDS_RED);
      //  pins_toggle(BOARD_IOID_DIO25);
      //  board_spi_read(buf, ilen);

        printf("comeca clock_wait 1ms\n");
// escrita de pino
        GPIO_toggleDio(29);
      //  clock_delay_usec(1000);

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
        printf("\n antes de deslocar 8 %u\n", (unsigned int) v);
        printf("\n antes de deslocar 8 %"PRIu32" \n", v);
        v <<= 8;             // Desloca 8 posições para a esquerda
        printf("\n depois de deslocar2 8 %u\n", (unsigned int) v);
        v |= spi_read2_tcc();
        printf("\n depois do ou %u\n", (unsigned int) v);
        GPIO_writeDio(27, 1);  // chip select
//spi_read_tcc(uint8_t *buf, size_t len, uint32_t SO_dioNumber, uint32_t SCLK_dioNumber, uint32_t CS_dioNumber){    // lembrar de habilitar os pinos

      //  printf("aaaaaaaa: %X \n",(unsigned int)GPIO_readDio(26));

        v >>= 3;
        printf("\n ultima rotacao %u\n", (unsigned int) v);

        float resultado = v*25;
        int resultado_int = resultado/100;
        float resultado_intm = ((resultado/100)-resultado_int);
        uint16_t resultado_fc = (resultado_intm)*100;
        printf("\n depois das tres giradas %i.%u \n", resultado_int, resultado_fc);



        printf("\nsaida do spi buf: %u \n", *buf);
        printf("\nsaida do spi: %u \n", (unsigned int)buf/4);

        etimer_reset(&et_hello);
        printf("HELLO: Piscando o LED vermelho!\n");
    }
    if(ev == LED_PONG_EVENT){
        printf("Recebido LED PONG EVENT no processo: hello_world_process\n");
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_process, ev, data)
{
  PROCESS_BEGIN();

  leds_off(LEDS_ALL);
  etimer_set(&et_blink, 5*CLOCK_SECOND);
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
//  process_post(&pong_process,LED_PING_EVENT ,(void*)(&blink_process));

  etimer_set(&et_blink, 2*CLOCK_SECOND);
  while(1) {
    PROCESS_WAIT_EVENT();
    if(ev == PROCESS_EVENT_TIMER){
        process_post(&pong_process,LED_PING_EVENT ,(void*)(&blink_process));
        leds_toggle(LEDS_GREEN);
        etimer_reset(&et_blink);
        printf("BLINK: Piscando o LED verde!\n");
    }
    if(ev == LED_PONG_EVENT){
        printf("Recebido LED PONG EVENT no processo: blink_process\n");
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(pong_process, ev, data)
{
  PROCESS_BEGIN();

//  etimer_set(&et_pong, 5*CLOCK_SECOND);
//  PROCESS_WAIT_EVENT_UNTIL(ev == LED_PING_EVENT);
  //process_post(&pong_process,LED_PING_EVENT,(void *)(& hello_world_process ));
//  process_post((struct process*)data,LED_PONG_EVENT,NULL);
//
//  etimer_set(&et_pong, CLOCK_SECOND * 1);
//  count = 0;
  while(1) {
    PROCESS_WAIT_EVENT();
    if(ev == LED_PING_EVENT){
//        leds_toggle(LEDS_RED);
//        etimer_reset(&et_pong);
        if (process_post((struct process*)data,LED_PONG_EVENT,NULL)==0){
            printf("Recebido ping do processo: %s\n",(char *)pong_process.name); //pong_process.name
        }

//        printf("Recebido ping de algum processo\n");
    }
  }

  PROCESS_END();
}

/*---------------------------------------------------------------------------*/
