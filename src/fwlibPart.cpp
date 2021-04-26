#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./util.c"
#include "../lib/fwlib32.h"

int getMachine(const char *host, int port)
{
  char cncID[36];

  if (retrieve_id(host, port, cncID))
  {
    return EXIT_FAILURE;
  }

  printf("machine id: %s\n", cncID);

  return EXIT_SUCCESS;
}
