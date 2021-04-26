#ifndef FW_UTIL_H
#define FW_UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/fwlib32.h"
typedef struct odbdy2_t
{
  int16_t dummy;
  int16_t axis;
  int32_t alarm;
  int32_t prgnum;
  int32_t prgmnum;
  int32_t seqnum;
  int32_t actf;
  int32_t acts;
  union
  {
    struct
    {
      int32_t absolute[MAX_AXIS];
      int32_t machine[MAX_AXIS];
      int32_t relative[MAX_AXIS];
      int32_t distance[MAX_AXIS];
    } faxis;
    struct
    {
      int32_t absolute;
      int32_t machine;
      int32_t relative;
      int32_t distance;
    } oaxis;
  } pos;
} ODBDY2_T;
#endif
