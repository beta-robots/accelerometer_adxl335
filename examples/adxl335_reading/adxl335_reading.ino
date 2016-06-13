//testing ADXL335

//standard library
#include "Arduino.h"

//ADXL335 library
#include "accelerometer_adxl335.h"

//pin assignement & constants
int PIN_LED = 13; // Pin 13 has a LED connected on most Arduino boards.
int PIN_ADXL335_X = 0; //x analog input
int PIN_ADXL335_Y = 1; //y analog input
int PIN_ADXL335_Z = 2; //z analog input
int ADC_REFERENCE = DEFAULT; //set to default (5V with Mega or UNO)
int SERIAL_BAUD_RATE = 9600;

//ADXL335 object, with pins and ADC voltage reference 
AccelerometerADXL335 adxl335(PIN_ADXL335_X, PIN_ADXL335_Y, PIN_ADXL335_Z, ADC_REFERENCE);

//global variables
float x_volts;
float y_volts;
float z_volts; //voltage levels for x,y,z [V]
float x_accel;
float y_accel;
float z_accel; //accel for x,y,z axis [N]
float angle_roll; //angle of rotation around x axis

//setup
void setup() 
{
    //sets pin_led as a digital output
    pinMode(PIN_LED, OUTPUT);
    
    //sets ADC reference
    analogReference(ADC_REFERENCE);
    
    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);     
}
 
//main loop
void loop() 
{    
    
    // turn the LED on 
    digitalWrite(PIN_LED, HIGH);   
    
    //get raw data separately per axis
    x_volts = adxl335.getVoltageX();
    y_volts = adxl335.getVoltageY(); 
    z_volts = adxl335.getVoltageZ(); 
    
    //get accelerations separately per axis
    x_accel = adxl335.getAccelerationX();
    y_accel = adxl335.getAccelerationY();
    z_accel = adxl335.getAccelerationZ(10); //10 readings, instead of the default set by N_READINGS_DEFAULT at accelerometer_adxl335.h    
    
    //get roll angle, tilt around X axis
    angle_roll = adxl335.getAngleX(); 
    
    //print results if verbose mode
    Serial.print("x_volts: ");
    Serial.println(x_volts, DEC);
    Serial.print("y_volts: ");
    Serial.println(y_volts, DEC);
    Serial.print("z_volts: ");
    Serial.println(z_volts, DEC);
    Serial.print("x_accel: ");
    Serial.println(x_accel, DEC);
    Serial.print("y_accel: ");
    Serial.println(y_accel, DEC);
    Serial.print("z_accel: ");
    Serial.println(z_accel, DEC);
    Serial.print("roll (about x): ");
    Serial.println(angle_roll, DEC);
    Serial.print("----------------------------\n\n");
    
    //relax
    delay(500); 
    
 
}
