/*---------------------------------------------------------------------------*/
/**
 * \
 * @{
 *
 * \file
 * Board-specific SPI driver
 */
/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "ti-lib.h"
#include "board-spi-tcc.h"
#include "board.h"
#include <stdbool.h>

/*---------------------------------------------------------------------------*/
uint8_t spi_read2_tcc(uint8_t sck, uint8_t so){
    int i; //// nao usar essa funcao. usar temperature_read
    uint8_t d = 0;

  // Laço FOR para apanhar 8 bits de cada vez
    for (i = 7; i >= 0; i--){
        GPIO_writeDio(sck, 0);  // Borda de descida do clock - Falling Edge
        clock_delay_usec(1000);             // Aguarda 1ms
        if (GPIO_readDio(so)) {    // Faz a leitura do pino de dados de saída do MAX
            d |= (1 << i);          // Armazena os bits lidos, 0 ou 1, na variável e desloca de acordo com o indice para
        }                         // preencher todo o byte de dados
        GPIO_writeDio(sck, 1);// Borda de subida do clock - Rising Edge
        clock_delay_usec(1000);            // Aguarda 1ms
    }

    return d;                   // Retirna o byte de leitura dos dados lidos do MAX
}

/*---------------------------------------------------------------------------*/
uint16_t temperature_read(uint8_t sck, uint8_t cs, uint8_t so){
    // sck - clock / cs - chip select / so - serial data output
    uint16_t v;
 //   GPIO_setOutputEnableDio(29, GPIO_OUTPUT_ENABLE);  // escrita de pino
 //  GPIO_setOutputEnableDio(27, GPIO_OUTPUT_ENABLE);  // escrita de pino
 //   GPIO_setOutputEnableDio(26, GPIO_OUTPUT_DISABLE);  // leitura de pino

   // GPIO_writeDio(sck, 1);
   // GPIO_toggleDio(sck);
    //clock_wait(time_wait*CLOCK_SECOND);

    GPIO_writeDio(cs, 0);  // chip select
    v = spi_read2_tcc(sck, so);       // Leitura da parte alta - Primeiros 8 bits de dados
    v <<= 8;             // Desloca 8 posições para a esquerda
    v |= spi_read2_tcc(sck, so);
    GPIO_writeDio(cs, 1);  // chip select
    //spi_read_tcc(uint8_t *buf, size_t len, uint32_t SO_dioNumber, uint32_t SCLK_dioNumber, uint32_t CS_dioNumber){    // lembrar de habilitar os pinos
    v >>= 3;
  //  float resultado = v*25;
  //  int resultado_int = resultado/100;
  //  float resultado_intm = ((resultado/100)-resultado_int);
  //  uint16_t resultado_fc = (resultado_intm)*100;
  //  printf("\n temperatura: %i.%u °C\n", resultado_int, resultado_fc);
  //  GPIO_writeDio(sck, 0);
    return v;
}

/*---------------------------------------------------------------------------*/

void enable_spi_pin(uint8_t sck, uint8_t cs, uint8_t so){
    GPIO_setOutputEnableDio(sck, GPIO_OUTPUT_ENABLE);  // escrita de pino
    GPIO_setOutputEnableDio(cs, GPIO_OUTPUT_ENABLE);  // escrita de pino
    GPIO_setOutputEnableDio(so, GPIO_OUTPUT_DISABLE);  // leitura de pino
}
/** @} */
