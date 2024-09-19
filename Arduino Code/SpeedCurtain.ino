//#include <TinyGPSPlus.h>
#include <Arduino_MKRGPS.h>
#include <FastLED.h>
//#include <WiFiNINA.h>
//#include <utility/wifi_drv.h>
#include <ArduinoBLE.h>

#include <Wire.h>
#include "rgb_lcd.h"

#include "Constants.h"
#include "displayState.h"

rgb_lcd lcd;

#define BUTTON1_PIN 5
#define BUTTON2_PIN 6

String text ="Welcome to UCD!";

//String text ="THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";  //  The text to display on the LEDs

double speed=0; 
double avgSpeed;
double oldAvgSpeed;
double course;
unsigned long timer;
int length;

bool GNSSsetup = false;
bool BLEsetup = false;
int setupStage = 1;
double forward;
int dir = FORWARD;
int courseTimer;
int prevCourse=0;
bool forwardSetup = false;
double maxStillSpeed=0;
double waitTime = 100000;
bool backwardsEnabled = false;
bool ignoreGNSS = false;
bool avgMode = false;

CRGB leds[NUM_LEDS];      //  Array holding the colour of each LED on the curtain

// =========== Bluetooth Setup ==========
BLEService SpeedCurtainService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth Low Energy Service
// Characteristics
BLEStringCharacteristic textCharacteristic("9AFF", BLEWrite, 1000);
BLEByteCharacteristic colourCharacteristic("7CFF", BLEWrite);
BLEByteCharacteristic fontCharacteristic("2FFF", BLEWrite);
BLEByteCharacteristic statusCharacteristic("8BFF", BLERead);
BLEUnsignedIntCharacteristic lengthCharacteristic("5EFF", BLERead);
BLEBoolCharacteristic invertTextCharacteristic("1CFF", BLEWrite);
BLEBoolCharacteristic GOCharacteristic("6DFF", BLEWrite);
BLEBoolCharacteristic resetCharacteristic("6BFF", BLEWrite);
BLEBoolCharacteristic autoScrollCharacteristic("5CFF", BLEWrite);
BLEBoolCharacteristic ribbonCharacteristic("4CFF", BLEWrite);
BLEBoolCharacteristic avgCharacteristic("3AFF", BLEWrite);

BLEDescriptor textLabelDescriptor("2901", "Text to be displayed");
BLEDescriptor colourLabelDescriptor("2802", "Colour map to use R:0, G:1, B:2");
BLEDescriptor fontLabelDescriptor("3344","Choose font");
BLEDescriptor statusLabelDescriptor("2703", "Status");
BLEDescriptor lengthLabelDescriptor("2605", "Length of the text in centimeters");
BLEDescriptor GOLabelDescriptor("2504", "Start the curtain");

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");
  //Serial1.begin(GPSBaud);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);   //  Setup the LEDs

  lcd.begin(16, 2);
  lcd.clear();

  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);

  //  Setup GPS for 10Hz
  setupGNSSMessages();

  // Setup Bluetooth
  setupBluetooth();


  delay(2000);      // Wait for 2 seconds
  Serial.println("Start");

  timer = millis();
  courseTimer = millis();
  lcd.print("Starting");
}

void loop()
{
  DisplayState displayState = DisplayState();
  bool readyToMove = false;

  //Skip BLE
  /*displayState.setText("TEsting");
  displayState.setFont(1);
  BLEsetup = true;*/


  BLEDevice central = BLE.central();

  while (true)
  {
    BLEDevice central = BLE.central();
    
    if (!ignoreGNSS && !displayState.noNewLetters)
    {
      //  Poll the GNSS for new readings, if no new readings
      //  values remain unchanged  
      getGNSSReadings(); 
      if (setupStage!=0 && setupStage!=3)
      {
        setupGNSS();
      }
    }

    if (central) // TODO Press button to put in Bluetooth mode
    {
      //Serial.print("Connected");
      if (textCharacteristic.written())
      {
        String text = textCharacteristic.value();
        Serial.println(text);
        int length = displayState.setText(text);
        lengthCharacteristic.writeValue(length);
      }
      if (colourCharacteristic.written())
      {
        int colour = colourCharacteristic.value();
        Serial.println(colour);
        displayState.setColourMode(colour);
      }
      if (fontCharacteristic.written())
      {
        int font = fontCharacteristic.value();
        displayState.setFont(font);
      }
      if (GOCharacteristic.written())
      {
        BLEsetup = GOCharacteristic.value();
        Serial.println("BLE Setup");
        timer=millis();
      }
      if (invertTextCharacteristic.written())
      {
        displayState.setInvert(invertTextCharacteristic.value());
      }
      if(autoScrollCharacteristic.written() && autoScrollCharacteristic.value())
      {
        Serial.println(F("Autoscroll"));
        GNSSsetup=true;
        maxStillSpeed = 0;
        speed = 0.5;
        avgSpeed = speed;
        waitTime = 200;
        ignoreGNSS = true;
        setupStage=3;
      }
      if (resetCharacteristic.written() && resetCharacteristic.value())
      {
        // Create setup function
        Serial.println(F("RESET"));
        displayState = DisplayState();
        readyToMove = false;
        GNSSsetup = false;
        BLEsetup = false;
        setupStage = 1;
        dir = FORWARD;
        prevCourse=0;
        forwardSetup = false;
        maxStillSpeed=0;
        waitTime = 10000;
        backwardsEnabled = false;
        ignoreGNSS = false;
        avgMode = false;

        for (int i=0;i<400;i++)
        {
          leds[i] = CRGB::Black;
        }
      }
      if(ribbonCharacteristic.written() && ribbonCharacteristic.value()) // Add Ribbon
      {
        displayState.addRibbon(leds);
      }
      if(avgCharacteristic.written())
      {
        avgMode = avgCharacteristic.value();
      }
    }

    if(GNSSsetup && BLEsetup && !displayState.noNewLetters)
    {
      if (setupStage!=0)
      {
        //setupGNSS();
        if(setupStage==3)
        {
          lcd.clear();
          lcd.print("Ready NEW");
          statusCharacteristic.writeValue(2);
          setupStage=0;
          timer=millis();
        }
      }
      else if (speed > maxStillSpeed && avgSpeed > maxStillSpeed)  //  Filter to remove small noise
      { 
        if (!readyToMove)
        {
          readyToMove = displayState.prepareMove(dir,leds);
        }
        if (readyToMove && millis() - timer >= waitTime)                 // If the wait time has elapsed
        {
          timer = millis(); //  Reset the timer
          FastLED.show();   //  Update the lights 
          readyToMove = false;
          Serial.print("Speed:");
          Serial.println(avgSpeed);
        }
      }
    }
  }
}

void getGNSSReadings()
{
  if (GPS.available()) {
    GNSSsetup=true;
    // read GPS values
    speed = GPS.speed();
    if (!isnan(speed))
    {
      oldAvgSpeed = avgSpeed;
      if (avgMode)
      {
        avgSpeed = (ALPHA*speed)+((1-ALPHA)*oldAvgSpeed);   // IIR Continuous Averaging Filter
      }
      else
      {
        avgSpeed = speed;
      }
      waitTime = (DISTBETWEENLIGHTS/avgSpeed)*1000;  // Time to wait before moving the pattern (ms)
      /*while (waitTime<15) // Time taken to update the curtain
      {
        waitTime += (DISTBETWEENLIGHTS/speed)*1000;
        displayState.prepareMove(dir,leds);
      }*/
    }
  }
}

void setupGNSS()
{
  //Serial.println(setupStage);
  if (setupStage==1 && GNSSsetup==true)
  {
    Serial.println("Signal Acquired");
    setupStage=2;
    timer=millis();
    statusCharacteristic.writeValue(1);
    lcd.clear();
    lcd.print("Wait 10s");
  }
  else if(setupStage==2)
  {
    maxStillSpeed=max(maxStillSpeed,speed);

    if(millis()-timer>10000)
    {
      
      setupStage=3;
      Serial.print(millis());
      Serial.print(",Max Still,");
      Serial.println(maxStillSpeed);
      lcd.clear();
      lcd.print(maxStillSpeed);
      timer=millis();
    }
  }
}

void setupGNSSMessages()
{
  if (!GPS.begin()) {
    Serial.println("Failed to initialize GPS!");
    while (1);
  }
  // Configure GNSS receiver to process new data at 10Hz, written by 'HackySchmacky'
  // https://arduino.stackexchange.com/a/68827

  Serial.println("Configuring GPS refresh rate...");

  //  UBX-CFG-RATE (0x06 0x08) Navigation/Measurement Rate Settings
  //  See UBX-13003221 section 32.10.23.1
  byte payload[6];

  memset(payload, 0x00, sizeof(payload));

  uint16_t measRate = 100;    // ms between gps data publish  (min of 100)
  uint16_t navRate  =   1;    // ratio between measurements and nav solution calculations
  uint16_t timeRef  =   1;    // The time system to which measurements are aligned (0: UTC, 1:GPS, ...)

  // write out the unsigned shorts in little-endian form
  payload[0] = measRate & 0xff;   
  payload[1] = (measRate >> 8) & 0xff;   
  payload[2] = navRate & 0xff;
  payload[3] = (navRate >> 8) & 0xff;
  payload[4] = timeRef & 0xff;
  payload[5] = (timeRef >>8) && 0xff;

  GPS.sendUbx(0x06, 0x08, payload, sizeof(payload));
}

void setupBluetooth()
{
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("SpeedCurtain");
  BLE.setDeviceName("SpeedCurtain");
  BLE.setAdvertisedService(SpeedCurtainService);


  // add the characteristic to the service
  textCharacteristic.addDescriptor(textLabelDescriptor);
  colourCharacteristic.addDescriptor(colourLabelDescriptor);
  fontCharacteristic.addDescriptor(fontLabelDescriptor);
  statusCharacteristic.addDescriptor(statusLabelDescriptor);
  lengthCharacteristic.addDescriptor(lengthLabelDescriptor);
  GOCharacteristic.addDescriptor(GOLabelDescriptor);

  SpeedCurtainService.addCharacteristic(textCharacteristic);
  SpeedCurtainService.addCharacteristic(colourCharacteristic);
  SpeedCurtainService.addCharacteristic(fontCharacteristic);
  SpeedCurtainService.addCharacteristic(statusCharacteristic);
  SpeedCurtainService.addCharacteristic(lengthCharacteristic);
  SpeedCurtainService.addCharacteristic(invertTextCharacteristic);
  SpeedCurtainService.addCharacteristic(GOCharacteristic);
  SpeedCurtainService.addCharacteristic(resetCharacteristic);
  SpeedCurtainService.addCharacteristic(autoScrollCharacteristic);
  SpeedCurtainService.addCharacteristic(ribbonCharacteristic);
  SpeedCurtainService.addCharacteristic(avgCharacteristic);

  // add service
  BLE.addService(SpeedCurtainService);
  statusCharacteristic.writeValue(0);
  BLE.advertise();
}

