#include <CmdExecutor.h>
#include <pin_config.h>
#include <EEPROM.h>
#include <string.h>

SoftSerial *serialw;
void CmdExecutor::execute_command(char key[], char value[], SoftSerial *serial)
{
    serialw = serial;

    if (per_strcmp(key, (char *)CMD_SET_APPLIANCE_OUTPUT_VOLTAGE) == 0)
    {
        DEBUG_PRINT(F("Command Matched, setting output voltage"));
        analogWrite(SET_APPLIANCE_OUTPUT_PIN, atoi(value));
    }
    else if (per_strcmp(key, (char *)CMD_GET_DEVICE_ID) == 0)
    {
        DEBUG_PRINT(F("Command Matched, getting device ID"));
        // serial->println((String)this->get_device_id());
        this->get_device_id();
    }
    else if (per_strcmp(key, (char *)CMD_SET_DEVICE_ID) == 0)
    {
        DEBUG_PRINT(F("Command Matched, setting device ID"));
        this->set_device_id(value);
    }
    else if (per_strcmp(key, (char *)CMD_GET_DEVICE_TYPE) == 0)
    {
        DEBUG_PRINT(F("Command Matched, getting device TYPE"));
        serial->println((String)DEVICE_TYPE);
    }
    else if (per_strcmp(key, (char *)CMD_GET_DEVICE_STATUS) == 0)
    {
        DEBUG_PRINT(F("Command Matched, getting device STATUS"));
        serial->println((String)digitalRead(GET_APPLIANCE_ON_OFF_STATUS));
    }
    else if (per_strcmp(key, (char *)CMD_RAISE_TRIGGER) == 0)
    {
        String str = "{\"RTR\":\"";
        //str += this->get_device_id();
        str += "\"}";
        serial->println(str);
    }
    /* else
    {
        serial->println(F("Command does not exists"));
    }*/
}

void CmdExecutor::set_device_id(char id[])
{
    EEPROM.begin();

    uint8_t i = 0;
    uint8_t len = strlen(id);
    for (i = 0; i < len; i++)
        EEPROM.write(i, id[i]);

    //EEPROM.commit();
    EEPROM.end();
}

void CmdExecutor::get_device_id()
{
    EEPROM.begin();
    // String op = "Notihng 1";
    // dev_id = (char *)malloc(sizeof(char) * DEVICE_ID_LEN);
    //memset(this->dev_id, 255, sizeof(char) * DEVICE_ID_LEN);

    uint8_t i = 0;
    //   uint8_t ch;
    do
    {
        // ch = EEPROM.read(i);
        // this->dev_id[i] = (char)ch;
        //op+=(String)EEPROM.read(i);
        serialw->print((char)EEPROM.read(i));
        i++;
    } while (i < DEVICE_ID_LEN);

    //  this->dev_id[i] = '\0';

    //EEPROM.commit();
    EEPROM.end();

    // if (i == 1)
    //   return (String)NO_ID;

    // return op;
}

int CmdExecutor::per_strcmp(char input_key[], char target_key[])
{
    uint8_t len1;
    uint8_t len2;

    for (len1 = 0; input_key[len1] != '\0'; len1++)
        ;
    for (len2 = 0; target_key[len2] != '\0'; len2++)
        ;
    if (len1 != len2)
        return 1;

    for (uint8_t i = 0; i < len1; i++)
        if (input_key[i] != target_key[i])
            return 1;

    return 0;
}