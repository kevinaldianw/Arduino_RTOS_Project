int32_t lastDigit = 0, temporarySpeed = 0;
bool newDigit = false;

bool menuActive = true, cekKeypadActive = false, stepperActive = false, dhtActive = false, useJoystick = false;



void OLEDInit()
{
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(System5x7);
  oled.setCursor(0,0);             // Start at top-left corner
  oled.println(F("BAGASKARA P P"));
  oled.println(F("KEVIN ALDIAN W"));
  oled.println(F("M HARITSAH M"));
  delay(2000);
  oled.clear();
}

void displayOLED()
{
  if (menuActive)
  {
    if (key == 'A') //Atas
    {
      select--;
      vTaskDelay(20);
    }
    if (key == 'B') //Bawah
    {
      select++;
      vTaskDelay(20);
    }

    if (select == 1)
    {
      oled.setCursor(0, 0);            // Start at top-left corner
      oled.println(F("MENU"));
      oled.println(F("~ Cek Keypad"));
      oled.println(F("  Stepper + Joystick"));
      oled.println(F("  Stepper + Keypad"));
      oled.println(F("  DHT-11"));
    }
    else if (select == 2)
    {
      oled.setCursor(0, 0);            // Start at top-left corner
      oled.println(F("MENU"));
      oled.println(F("  Cek Keypad"));
      oled.println(F("~ Stepper + Joystick"));
      oled.println(F("  Stepper + Keypad"));
      oled.println(F("  DHT-11"));
    }
    else if (select == 3)
    {
      oled.setCursor(0, 0);            // Start at top-left corner
      oled.println(F("MENU"));
      oled.println(F("  Cek Keypad"));
      oled.println(F("  Stepper + Joystick"));
      oled.println(F("~ Stepper + Keypad"));
      oled.println(F("  DHT-11"));
    }
    else if (select == 4)
    {
      oled.setCursor(0, 0);
      oled.println(F("MENU"));
      oled.println(F("  Cek Keypad"));
      oled.println(F("  Stepper + Joystick"));
      oled.println(F("  Stepper + Keypad"));
      oled.println(F("~ DHT-11"));
    }
    else if (select == 0) select = 4;
    else if (select == 5) select = 1;

    if (key == 'C' && select == 1) //Masuk Menu 1 (Cek Keypad)
    {
      oled.clear();
      cekKeypadActive = true;
      menuActive = false;
    }
    if (key == 'C' && select == 2) //Masuk Menu 2 (Stepper + Joystick)
    {
      oled.clear();
      useJoystick = true;
      stepperActive = true;
      menuActive = false;

    }
    if (key == 'C' && select == 3) //Masuk Menu 3 (Stepper + Keypad)
    {
      oled.clear();
      useJoystick = false;
      stepperActive = true;
      menuActive = false;

    }
    if (key == 'C' && select == 4) //Masuk Menu 4 (DHT)
    {
      oled.clear();
      dhtActive = true;
      menuActive = false;
    }
  }
  if (dhtActive)
  {
    if (key == 'D') //Kembali ke menu
    {
      oled.clear();
      menuActive = true;
      dhtActive = false;
    }
    oled.setCursor(0, 0);
    oled.println(F("SENSOR DHT-11"));
    oled.println("Suhu:");
    oled.println(temperature,1);
    oled.println("Kelembapan:");
    oled.println(humidity,1);
  }
  if (cekKeypadActive)
  {
    oled.setCursor(0, 0);
    oled.println(F("CEK KEYPAD"));
    if (key)oled.println(key);
    if (key == 'D') //Kembali ke menu
    {
      oled.clear();
      menuActive = true;
      cekKeypadActive = false;
    }
  }

  if (stepperActive)
  {
    if (useJoystick)
    {
      oled.setCursor(0, 0);
      oled.println(F("STEPPER + JOYSTICK"));
      oled.println("Kecepatan :");
      //      stepperSpeed = map(joystickYVal, 0, 1023, 0, 100);
      //      char text[20];
      //      sprintf(text,"%d",stepperSpeed);
      //      oled.println(text);
      if (key == 'D') //Kembali ke menu
      {
        oled.clear();
        menuActive = true;
        stepperActive = false;
      }
    }
    else
    {
      oled.setCursor(0, 0);
      oled.println(F("STEPPER + KEYPAD"));
      oled.println("Masukkan kecepatan");
      oled.println("(0-100)");

      if (key == '0') {
        lastDigit = 0;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '1') {
        lastDigit = 1;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '2') {
        lastDigit = 2;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '3') {
        lastDigit = 3;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '4') {
        lastDigit = 4;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '5') {
        lastDigit = 5;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '6') {
        lastDigit = 6;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '7') {
        lastDigit = 7;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '8') {
        lastDigit = 8;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == '9') {
        lastDigit = 9;
        newDigit = true;
        vTaskDelay(10);
      }
      else if (key == 'C')
      {
        oled.clear();
        stepperSpeed = temporarySpeed;
        temporarySpeed = 0;
      }

      else if (key == 'D') //Kembali ke menu
      {
        oled.clear();
        menuActive = true;
        stepperSpeed = 0;
        stepperActive = false;
      }

      if (newDigit)
      {
        temporarySpeed = temporarySpeed * 10 + lastDigit;
        newDigit = false;
        vTaskDelay(1);
      }
      Serial.println(temporarySpeed);
      if (temporarySpeed > 0)oled.println(temporarySpeed);
    }
  }
}

