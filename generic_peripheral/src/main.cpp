//#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <pin_config.h>
#include <SoftSerial.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <JSONParser.h>
#include <CmdExecutor.h>
#include <config.h>

static SoftSerial *serial = new SoftSerial(RX, TX);
static char command_buffer[30];
static CmdExecutor *executor = new CmdExecutor();
static JSONParser *parser = new JSONParser();

void setup()
{
  //cli();

  serial->begin(19200);
  DEBUG_PRINT(F("Setting up peripheral..."));

  pinMode(SET_APPLIANCE_OUTPUT_PIN, OUTPUT);
  pinMode(GET_APPLIANCE_ON_OFF_STATUS, INPUT);
  pinMode(GET_APPLIANCE_TRIGGER, INPUT);

  // GIMSK |= (1 << PCIE);   // pin change interrupt enable
  // PCMSK |= (1 << PCINT4);  // pin change interrupt enabled for PCINT4

  //MCUCR &= ~(_BV(ISC00));// | _BV(ISC00));      //INT0 on low level
  //MCUCR |= 1;      //INT0 on low level
  //GIMSK = 1 << INT0; //Enable INT0

  //  sei();                  // enable interrupts
}

void loop()
{

  if (serial->available())
  {
    char ch;
    uint8_t len = 0;
    memset(command_buffer, '\0', sizeof(command_buffer));
    while (serial->available())
    {
      ch = serial->read();
      delay(10);
      command_buffer[len] = ch;
      len++;
    }
    command_buffer[len] = '\0';

    DEBUG_PRINT(F("Received String "));
    DEBUG_PRINT(i);
    DEBUG_PRINT(command_buffer);

    parser->parse(command_buffer);
    for (int i = 0; i < parser->total_pairs; i++)
    {
      DEBUG_PRINT(parser->pairs[i].key);
      DEBUG_PRINT(parser->pairs[i].val);
      executor->execute_command(parser->pairs[i].key, parser->pairs[i].val, serial);
    }

    for (int i = 0; i < parser->total_pairs; i++)
    {
      free(parser->pairs[i].key);
      free(parser->pairs[i].val);
    }

    serial->flush();
  }
  else
  {
    DEBUG_PRINT(F("Checking for trigger"));
    DEBUG_PRINT(GET_APPLIANCE_TRIGGER);

    if (digitalRead(GET_APPLIANCE_TRIGGER) == 1)
    {
      executor->execute_command((char *)CMD_RAISE_TRIGGER, (char *)"", serial);
    }
    delay(1000);
  }
}

//ISR(PCINT0_vect)

/*ISR(INT0_vect)
  {
  serial.println("Bhay got the interrupt, toggling blub");

  if (toggle_bulb == 0)
  {
    toggle_bulb = 1;
    analogWrite(SET_APPLIANCE_OUTPUT_PIN, 0);
  }
  else
  {
    toggle_bulb = 0;
    analogWrite(SET_APPLIANCE_OUTPUT_PIN, 255);
  }
  }
*/
