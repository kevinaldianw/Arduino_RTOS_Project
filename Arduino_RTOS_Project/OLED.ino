
void OLEDInit()
{
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(System5x7);
  oled.setCursor(0, 0);            // Start at top-left corner
  oled.println(F("BAGASKARA P P"));
  oled.println("44215");
  oled.println(F("KEVIN ALDIAN W"));
  oled.println("44239");
  oled.println(F("M HARITSAH M"));
  oled.println("44246");
  delay(4000);
  oled.clear();
}

void OLEDDisplay()
{
  key = keypad.getKey();
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
      stepperJoyActive = true;
      menuActive = false;

    }
    if (key == 'C' && select == 3) //Masuk Menu 3 (Stepper + Keypad)
    {
      oled.clear();
      stepperKeyActive = true;
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
    oled.setCursor(0, 0);
    char text[20];
    sprintf(text,"Suhu: %d C",(int) temperature);
    oled.println(text);
    sprintf(text1,"Kelembapan: %d %", (int) humidity);
    if (key == 'D') //Kembali ke menu
    {
      oled.clear();
      menuActive = true;
      dhtActive = false;
    }
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

  if (stepperJoyActive)
  {
    oled.setCursor(0, 0);
    oled.println(F("STEPPER + JOYSTICK"));
    oled.println("Kecepatan :");
    stepperSpeed = map(joystickYVal, 0, 1023, 0, 100);
    char text[20];
    sprintf(text, "  %d  ", stepperSpeed);
    oled.println(text);
    if (key == 'D') //Kembali ke menu
    {
      oled.clear();
      menuActive = true;
      stepperJoyActive = false;
    }
  }

  if (stepperKeyActive)
  {
    oled.setCursor(0, 0);
    oled.println("Masukkan kecepatan");
    oled.println("(0-100)");
    char text[20];
    int a = temporarySpeed;
    sprintf(text, "%d", a);
    oled.println(text);
    oled.println("___ ");

    if (key == '0') {
      temporarySpeed *= 10;
      vTaskDelay(10);
    }
    else if (key == '1') {
      temporarySpeed *= 10;
      temporarySpeed += 1;
      vTaskDelay(10);
    }
    else if (key == '2') {
      temporarySpeed *= 10;
      temporarySpeed += 2;
      vTaskDelay(10);
    }
    else if (key == '3') {
      temporarySpeed *= 10;
      temporarySpeed += 3;
      vTaskDelay(10);
    }
    else if (key == '4') {
      temporarySpeed *= 10;
      temporarySpeed += 4;
      vTaskDelay(10);
    }
    else if (key == '5') {
      temporarySpeed *= 10;
      temporarySpeed += 5;
      vTaskDelay(10);
    }
    else if (key == '6') {
      temporarySpeed *= 10;
      temporarySpeed += 6;
      vTaskDelay(10);
    }
    else if (key == '7') {
      temporarySpeed *= 10;
      temporarySpeed += 7;
      vTaskDelay(10);
    }
    else if (key == '8') {
      temporarySpeed *= 10;
      temporarySpeed += 8;
      vTaskDelay(10);
    }
    else if (key == '9') {
      temporarySpeed *= 10;
      temporarySpeed += 9;
      vTaskDelay(10);
    }
    else if (key == 'C')
    {
      oled.clear();
      stepperSpeed = temporarySpeed;
      temporarySpeed = 0;
      vTaskDelay(10);
    }

    if (key == 'D') //Kembali ke menu
    {
      oled.clear();
      menuActive = true;
      stepperSpeed = 0;
      stepperKeyActive = false;
    }
  }
}

