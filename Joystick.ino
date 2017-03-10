/*
 Reads a T000030 Joystick Module Analog Sensor connected to I0 and I1,
 then set the brightness of two T010111 LED Module connected on O0 and O1
 with the values. Also prints the results to the serial monitor.
 http://www.tinkerkit.com/joystick/
 http://www.tinkerkit.com/led-green-10mm/

 created  7 dec 2010
 by Davide Gomba 
 modified on Dec 2011
 by Federico Vanzati
 modified on Jun 2013
 by Matteo Loglio<http://matlo.me>

 This example code is in the public domain.
 */

// include the TinkerKit library
#include <TinkerKit.h>
#include <Servo.h>


TKJoystick joystick(I0, I1);  // creating the object 'joystick' that belongs to the 'TKJoystick' class 
                       	      // and giving the values to the desired input pins

TKLed led(O1);

TKMosFet mos(O5);         //create the mos object

Servo myservo1;  
Servo myservo2;  


int x = 0;      // a variable for the Joystick's x value
int y = 0;      // a variable for the Joystick's y value
const int debug_on = 1;


int get_pos()
{
  delay(500);
  Serial.println("\n\n WAITING FOR JStick\n\n"); 
  while (1==1)
  {
    led.on();
    x = joystick.readX();  
    y = joystick.readY(); 
    /*
     * Serial.print("x, y =" );                       
     * Serial.print(x);   
     * Serial.print(", " );                       
     * Serial.println(y); 
    */   
    if (x <= 100){
      led.off();
      debug("1");
      return 1;
    }
    else if (y <= 100){
      led.off();
      debug("2");
      return 2;
    }
    else if (x >= 800){
      led.off();
      debug("3");
      return 3;
    }
    else if (y >= 800){
      led.off();
      debug("4");
      return 4;
    }
  }
}

void debug(char* tp)
{
  if (debug_on == 1){
    Serial.println(tp);
    }
}

void setup() 
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);  
  myservo1.attach(O3);  
  myservo2.attach(O4); 

}

void loop()
{
  debug("FAIL !");
  
  led.off();
  mos.write(128);       //assign the values to the mosfet
  myservo1.write(0);                  // sets the 1st servo position according to the scaled value
  myservo2.write(0);                  // sets the 2nd servo position according to the scaled value
  
  if (get_pos() == 4){
    debug("CA 1");
    if (get_pos() == 4){
      debug("CA 2");
      if (get_pos() == 2){
        debug("CA 3");
        if (get_pos() == 2){
          debug("CA 4");
          if (get_pos() == 3){
            debug("CA 5");
            if (get_pos() == 1){
              debug("CA 6");
              if (get_pos() == 3){
                debug("CA 7");
                if (get_pos() == 1){
                  debug("CA 8");
                  Serial.println("Code accepté");
                  mos.write(0);       //assign the values to the mosfet

                  // BOUM :)
                  
                  myservo1.write(180);                  // sets the 1st servo position 
                  delay(400);
                  myservo2.write(180);                  // sets the 2nd servo position

                  delay(10000);
                  
                }
              }
            }
          }
        }
      }
    }
  }

  // wait 10 milliseconds before the next loop
  delay(100);    
}

