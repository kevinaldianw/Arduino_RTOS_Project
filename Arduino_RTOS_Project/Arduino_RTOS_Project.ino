#include <Arduino_FreeRTOS.h>
#include "DHT.h" //https://github.com/markruys/arduino-DHT

#include "SSD1306Ascii.h" //https://github.com/greiman/SSD1306Ascii
#include "SSD1306AsciiAvrI2c.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

SSD1306AsciiAvrI2c oled;

DHT dht;

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {36, 38, 40, 42}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {44, 46, 48, 50}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;  // number of steps the motor has taken

#define JOYSTICK_X_PIN          A0
#define JOYSTICK_Y_PIN          A1

//Global Variable Declaration
int stepperSpeed;
int joystickXVal, joystickYVal;

char key;
int select = 1;

float temperature;
float humidity;

// define tasks
void TaskDisplayOLED( void *pvParameters );
void TaskReadJoystick( void *pvParameters );
void TaskStepper( void *pvParameters );
void TaskDHT( void *pvParameters );
void TaskBlink ( void *pvParameters);

int16_t temporarySpeed = 0;
bool menuActive = true, cekKeypadActive = false, stepperKeyActive = false, stepperJoyActive = false, dhtActive = false, useJoystick = false;


// the setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(9600);
 
  xTaskCreate(
    TaskDisplayOLED
    ,  (const portCHAR *)"DisplayOLED"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskStepper
    ,  (const portCHAR *) "JalankanStepper"
    ,  128  // Stack size
    ,  NULL
    ,  0  // Priority
    ,  NULL );

  xTaskCreate(
    TaskDHT
    ,  (const portCHAR *) "BacaDHT"
    ,  128  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );

  xTaskCreate(
    TaskReadJoystick
    ,  (const portCHAR *) "BacaJoystick"
    ,  128 // Stack size
    ,  NULL
    ,  0  // Priority
    ,  NULL );

  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *) "Blink"
    ,  128 // Stack size
    ,  NULL
    ,  0  // Priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskDisplayOLED(void *pvParameters)  // This is a task.
{

  //Inisialisasi OLED
  OLEDInit();
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    OLEDDisplay();
    vTaskDelay(1);
  }
}

void TaskDHT(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  dht.setup(2);
 
  for (;;)
  {
    temperature = dht.getTemperature();
    humidity = dht.getHumidity();
    vTaskDelay(1000 / portTICK_PERIOD_MS); // one tick delay (15ms) in between reads for stability
  }
}

void TaskStepper(void *pvParameters)  // This is a task.
{

  (void) pvParameters;

  for (;;)
  {
    if (stepperSpeed > 0) {
      myStepper.setSpeed(stepperSpeed);
      // step 1/100 of a revolution:
      myStepper.step(stepsPerRevolution / 100);
    }
    vTaskDelay(10);
  }
}

void TaskReadJoystick(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    joystickXVal = analogRead(JOYSTICK_X_PIN);
    joystickYVal = analogRead(JOYSTICK_Y_PIN);
    vTaskDelay(10);
  }
}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;)
  {
    digitalWrite(LED_BUILTIN, 1); vTaskDelay(50);
    digitalWrite(LED_BUILTIN, 0); vTaskDelay(50);
  }
}

