#include<NewPing.h>                // For Ultrasonic Sensor         
#include<AFMotor.h>                //AdaFruit Motor library for Motor

#define RIR A3                    // IR sensor on the right - pin A3
#define LIR A4                    // IR sensor on the left - pin A4
#define TRIG A1                   // Trigger pin - pin A1 
#define ECHO A0                   // Echo pin - pin A0 
#define MAX_DISTANCE 200          // Maximum ping distance

unsigned int distance = 0;        //Distance measured by ultrasonic sensor 
unsigned int RIR_value = 0;       //Value returned by IR sensor on the right
unsigned int LIR_value = 0;       //Value returned by IR sensor on the left
  

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);  //Setup of pins and maximum distance for ultrasonic sensor using NewPing

//Creating motor objects
AF_DCMotor Motor1(1,MOTOR12_1KHZ);        // Motor 1 and 2 belong to the same side
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);        // Motor 3 and 4 belong to the same side
AF_DCMotor Motor4(4,MOTOR34_1KHZ);


void setup() 
{ 
   pinMode(RIR, INPUT);     //Set pin as input from IR Sensor on the right
   pinMode(LIR, INPUT);     //Set pin as input from IR Sensor on the left
}

void loop() 
{                             
  
  delay(50);                                        
  distance = sonar.ping_cm();                       //Get Distance from human
  RIR_value = digitalRead(RIR);                     //Read from IR sensor on the right
  LIR_value = digitalRead(LIR);                     //Read from IR sensor on the left
  

  if((RIR_value == 1) && (LIR_value == 1))          //Check if there is no object right next to the robot
  {
    
    if((distance > 9) && (distance < 50))          //Check if there is an object(human) at a distance between 9 to 50
    {               
        //Move Forward
        Motor1.setSpeed(130);  
        Motor1.run(FORWARD);                  
        Motor2.setSpeed(130);  
        Motor2.run(FORWARD);   
        Motor3.setSpeed(130);  
        Motor3.run(FORWARD);   
        Motor4.setSpeed(130);  
        Motor4.run(FORWARD);   
    }

    else if((distance > 1) && (distance <= 9))     //Stop at a safe distance
    {
        //Stop
        Motor1.setSpeed(0);    
        Motor1.run(RELEASE);   
        Motor2.setSpeed(0);    
        Motor2.run(RELEASE);   
        Motor3.setSpeed(0);    
        Motor3.run(RELEASE);   
        Motor4.setSpeed(0);    
        Motor4.run(RELEASE); 
    }

    else if(distance >= 50)
    {
        //Turn left to search for object at distance between 9 and 50 - Motor run direction may change according to the user's configuration
        Motor1.setSpeed(150);  
        Motor1.run(BACKWARD);  
        Motor2.setSpeed(150);  
        Motor2.run(BACKWARD);  
        Motor3.setSpeed(150);  
        Motor3.run(FORWARD);   
        Motor4.setSpeed(150);  
        Motor4.run(FORWARD);   
        delay(150);
    }

  }

  else if((RIR_value == 0) && (LIR_value == 1))     //If there is an object on the right close to the robot
  {  
      //Turn right - Motor run direction may change according to the user's configuration                                            
      Motor1.setSpeed(100);  
      Motor1.run(FORWARD);   
      Motor2.setSpeed(100);  
      Motor2.run(FORWARD);   
      Motor3.setSpeed(100);  
      Motor3.run(BACKWARD);  
      Motor4.setSpeed(100);  
      Motor4.run(BACKWARD);  
      delay(150);
  }

  else if((RIR_value == 1) && (LIR_value == 0))     //If there is an object on the left close to the robot
  {    
      //Turn left - Motor run direction may change according to the user's configuration
      Motor1.setSpeed(100);  
      Motor1.run(BACKWARD);  
      Motor2.setSpeed(100);  
      Motor2.run(BACKWARD);  
      Motor3.setSpeed(100);  
      Motor3.run(FORWARD);   
      Motor4.setSpeed(100);  
      Motor4.run(FORWARD);   
      delay(150);
  }

  else if((RIR_value == 0) && (LIR_value == 0))     //If there is an object right in front of the robot
  {                          
      //Go back to a safe distance                                              
      Motor1.setSpeed(100);  
      Motor1.run(BACKWARD);   
      Motor2.setSpeed(100);  
      Motor2.run(BACKWARD);   
      Motor3.setSpeed(100);  
      Motor3.run(BACKWARD);  
      Motor4.setSpeed(100);  
      Motor4.run(BACKWARD);  
      delay(150);
  }
  
}
