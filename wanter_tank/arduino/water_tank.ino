#include <SoftwareSerial.h>
SoftwareSerial espSerial(5, 6);

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
  pinMode(13, OUTPUT);
  
  // Setup for ultra sonic sensor
  Serial.begin(9600);
  espSerial.begin(9600);
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
    
    // Print the flow rate for this second in litres / minute
//    Serial.print("Flow rate: ");
//    Serial.print(int(flowRate));  // Print the integer part of the variable
//    Serial.print("L/min");
//    Serial.print("\t");       // Print tab space
//    Serial.println();

    

    // Reset the pulse counter so we can start incrementing again
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
      espSerial.println('1');
 
      delay(5000);
    }
    
  }
  if ((obj.filled == 1) && (obj.empty==0))
  {
    if (motor_state==1)
    {
    digitalWrite(13, LOW);
    espSerial.println('0');
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
      espSerial.println('0');
      delay(10000);
    }
    
  }
  
  /*
  
   if (flow)
   {
    //Serial.println(flow);
    digitalWrite(13, HIGH);
   }
   else
   {
    digitalWrite(13, LOW);
   }
   */
   
}
