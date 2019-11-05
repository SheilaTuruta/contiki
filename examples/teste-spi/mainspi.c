
#include "contiki.h"
//#include "spi.h"

#include <stdio.h> /* For printf() */

PROCESS(test_process, "Hello world process");
AUTOSTART_PROCESSES(&test_process);

PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();

  printf("Hello, world\n");

  PROCESS_END();
}
