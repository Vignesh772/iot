//variabled for servo motor
#include <Servo.h> 
int servoPin = 5;
Servo Servo1; 


// Variables for flow sensor
byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;
const int pingPin = 4; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 3; // Echo Pin of Ultrasonic Sensor

int motor_state = 0;

 


struct level {
    int filled;
    int empty;
};

void turn_on()
{
  Servo1.write(130); 
  delay(500);

  Servo1.write(75); 
  delay(500);
  
  
}
void turn_off()
{
  Servo1.write(10); 
  delay(500);

  Servo1.write(75); 
  delay(500);

  
  
}
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}


int ultra_sonic()
{
   long duration, inches, cm;
   
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
  
   duration = pulseIn(echoPin, HIGH);
   inches = duration / 74 / 2;
   
   return inches;
}
struct level check_level()
{
  int c=0;
  
  struct level obj;
  obj.filled = 1;
  obj.empty = 1;
  
  while(c!=5)
  {
    int inches = ultra_sonic();
    c+=1;
    if (inches>=5)
    {
     obj.filled=0; 
      
    }
    if(inches<=30)
    {
      obj.empty=0;
    }
    delay(100);
  }
  return obj;
  
  
}
void setup()
{
  // Setup for ultra serrvo sensor
  Servo1.attach(servoPin); 
  Servo1.write(75);


  pinMode(13, OUTPUT);
  
  // Setup for ultra sonic sensor
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);

 
 // Setup for flow sensor
  pinMode(sensorPin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

bool is_water_flowing()
{
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    
    oldTime = millis();
    
  
    
      
    unsigned int frac;

    pulseCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    return flowRate;
    
    
    
  }
  
}
void loop()
{
  //int flow=is_water_flowing();
  struct level obj = check_level();
  Serial.print(obj.filled);
  Serial.println(obj.empty);
  if ((obj.filled == 0) && (obj.empty==1))
  {
    if (motor_state==0)
    {
      motor_state=1;
      digitalWrite(13, HIGH);
      turn_on();
 
      delay(5000);
    }
    
  }
  if ((obj.filled == 1) && (obj.empty==0))
  {
    if (motor_state==1)
    {
    digitalWrite(13, LOW);
    turn_off();
     delay(1000);
    }
  }

  if(motor_state==1)
  {
    int count=0;
    int is_flowing=1;
    while(count<10)
    {
      int flow=is_water_flowing();
      if (flow==0)
      {
        is_flowing=0;
      }
      delay(1000); 
      count++;
    }
    if (is_flowing==0)
    {
      digitalWrite(13, LOW);
      motor_state=0;
      turn_off();
      delay(600000);
    }
    
  }
  
 
   
}