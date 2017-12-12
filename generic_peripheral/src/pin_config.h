//===================Start=============================
/* Below pin configuration is compolsory to all the peripherals based on Attiny85. */
#define GET_APPLIANCE_ON_OFF_STATUS 4  // To check whether Appliance is ON/OFF

#define RX 0 // *** PB, Pin 0
#define TX 3 // *** PB, Pin 3
//===================End===============================



//===================Start=============================
/* Below pin configuration is for Device Type DG1. */

#define SET_APPLIANCE_OUTPUT_PIN 1  // Dimmer Circuit will be connected to this pin //1 is also on board LED

#define SET_APPLIANCE_INDICATION_IS_ACTIVE (2) //is_connected
//===================End===============================


//===================Start=============================
/* Below pin configuration is for bell */

#define GET_APPLIANCE_TRIGGER 2  // Interrupt driven pin, In case of bell 
//===================End===============================


//===================Start=============================
/* Below pin configuration is for Water level indicator peripheral. */

#define WATER_LEVEL_HIGH_STATUS 1  // Dimmer Circuit will be connected to this pin //1 is also on board LED
#define WATER_LEVEL_MEDIUM_STATUS 2  // Interrupt driven pin, In case of bell 
#define WATER_LEVEL_LOW_STATUS 4  // To check whether Applicance is ON/OFF
//===================End===============================


