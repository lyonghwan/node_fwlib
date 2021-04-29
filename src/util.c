#include "./util.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/**
 * 
 * 
 * */
char *connect(char *host, int port, unsigned short cncLibHandler)
{
  short ret;
  // unsigned short cncLibHandler;
  ret = cnc_startupprocess(0, "focas.log");

  static char code[8];
  ret = cnc_allclibhndl3(host, port, 3, &cncLibHandler);
  if (ret != EW_OK)
  {
    const char *msg;
    switch (ret)
    {
    case EW_SOCKET:
      msg = "Socket communication error\n";
      break;
    case EW_NODLL:
      msg = "There is no DLL file for each CNC series\n";
      break;
    case EW_HANDLE:
      msg = "Allocation of handle number is failed.\n";
      break;
    default:
      msg = "An unknown error occurred.\n";
    }
    printf(msg);
    snprintf(code, 9, "%d.\n", ret);
  }

  return code;
}

/***
 * 
 * 
 * */
short disconnect(unsigned short cncLibHandler)
{
  short ret;
  ret = cnc_freelibhndl(cncLibHandler);
  ret = cnc_exitprocess();
  return ret;
}

/**
 * 
 * 
 * */
uint32_t *readCncId(unsigned short cncLibHandler)
{
  static uint32_t cnc_ids[4];
  if (cnc_rdcncid(cncLibHandler, (unsigned long *)cnc_ids) != EW_OK)
  {
    fprintf(stderr, "Failed to read cnc id!\n");
  }
  return cnc_ids;
}

/**
 * 
 * 
 * */

ODBSYS sysinfo(unsigned short cncLibHandler)
{

  short ret;
  ODBSYS sysinfo;
  ret = cnc_sysinfo(cncLibHandler, &sysinfo);

  if (ret != EW_OK)
  {
    char code[8] = "";
    snprintf(code, 7, "%d", ret);
  }

  return sysinfo;
}

ODBST statinfo(unsigned short cncLibHandler)
{
  short ret;
  ODBST statObject;
  ret = cnc_statinfo(cncLibHandler, &statObject);

  if (ret != EW_OK)
  {
    char code[8] = "";
    snprintf(code, 7, "%d", ret);
  }

  return statObject;
}

/**
 * 
 * 
 * */
ODBDY2_T readDynamicTow(unsigned short cncLibHandler)
{

  short ret;
  ODBDY2_T dyn = {0};
  ret = cnc_rddynamic2(cncLibHandler, ALL_AXES, sizeof(dyn), (ODBDY2 *)&dyn);

  if (ret != EW_OK)
  {
    char code[8] = "";
    snprintf(code, 7, "%d", ret);
  }
  return dyn;
}

int retrieve_id(const char *host, int port, char *cnc_id)
{
  int allocated = 0;
  int ret = 0;
  unsigned short libh;
  uint32_t cnc_ids[4];

#ifndef _WIN32
  if (cnc_startupprocess(0, "focas.log") != EW_OK)
  {
    fprintf(stderr, "Failed to create required log file!\n");
    return 1;
  }
#endif

  printf("connecting to machine at %s:%d...\n", host, port);
  if ((ret = cnc_allclibhndl3("127.0.0.1", 8193, 10, &libh)) != EW_OK)
  {
    fprintf(stderr, "Failed to connect to cnc! (%d)\n", ret);
    ret = 1;
    goto cleanup;
  }
  allocated = 1;

  if (cnc_rdcncid(libh, (unsigned long *)cnc_ids) != EW_OK)
  {
    fprintf(stderr, "Failed to read cnc id!\n");
    ret = 1;
    goto cleanup;
  }

  snprintf(cnc_id, 40, "%08x-%08x-%08x-%08x", cnc_ids[0], cnc_ids[1],
           cnc_ids[2], cnc_ids[3]);

cleanup:
  if (allocated && cnc_freelibhndl(libh) != EW_OK)
    fprintf(stderr, "Failed to free library handle!\n");
#ifndef _WIN32
  cnc_exitprocess();
#endif

  return ret;
}
