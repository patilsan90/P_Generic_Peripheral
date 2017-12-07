#ifndef __CMD_EXECUTOR__
#define __CMD_EXECUTOR__
//#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <pin_config.h>
#include <SoftSerial.h>
#include <config.h>

#define CMD_GET_DEVICE_ID ("GDI")                 //("GET_DEV_ID")
#define CMD_SET_DEVICE_ID ("SDI")                 //("SET_DEV_ID")
#define CMD_GET_DEVICE_TYPE ("GDT")               //("GET_DEV_TYPE")
#define CMD_SET_APPLIANCE_OUTPUT_VOLTAGE ("pval") //("Peripheral_value")
#define CMD_RAISE_TRIGGER ("RTR")                 //("RAISE_TRIGGER")
#define CMD_GET_DEVICE_STATUS ("GDS")             //("GET_DEV_STATUS")

#define DEVICE_TYPE ("DG1") //("DEV_GEN_1")
#define NO_ID ("NO_ID")

class CmdExecutor
{
public:
  void execute_command(char key[], char value[], SoftSerial *serial);

private:
  int per_strcmp(char input_key[], char target_key[]);
  void set_device_id(char id[]);
  void get_device_id();
};

#endif
