// Arduino Dual Axis Joystick Example


#define Xaxis_pin A0 // Arduino pin connected to the VRx Pin


#define Yaxis_pin A1 // Arduino pin connected to the VRy Pin


#define SW_pin A2 // Arduino pin connected to the SW Pin

#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
int step_number = 0;
String val = "";
void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
void setup() {
  

  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  pinMode(SW_pin, INPUT);


  digitalWrite(SW_pin, HIGH);


  Serial.begin(9600);

  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }


}

int turn =1;
void loop() {

//  delay(5000);
//  if(turn)
//  {
//  for(int i =0; i <2048*4; i++)
//  {
//    OneStep(true);
//      delay(2); 
//    
//  }
//  turn =0;
//  }
//  if (turn == 0)
//  {
//    for(int i =0; i <2048*4; i++)
//    {
//    OneStep(false);
//      delay(2); 
//    
//    }
//  turn =1;
//    
//  }
  

  
  while(analogRead(Yaxis_pin)>900)
  {
    
      OneStep(false);
      delay(2); 
    
    
  }

  while(analogRead(Yaxis_pin)<100)
  {
    OneStep(true);
      delay(2); 
    
    
  }
  String val="";
  String dir="";
  while (Serial.available()) 
  {
    char inByte  = 0;
    inByte = (char)Serial.read();  // ascii 97 received
    inByte = (char)inByte;
    // Serial.println(inByte);
    if ((inByte == 'T') || (inByte == 'F'))
    {
      dir = inByte;
    }
    else
    {
      val = val + inByte;
    }
    
    
  }
  //Serial.print(val); 
  
  //Serial.println(dir);
  
  
    if ((val.length() > 0) && (dir.length()>0))
    {
      Serial.println(val);
      Serial.println(dir);
      for(int i=0;i<val.toInt();i++)
      {
        
        if(dir=="F")
        {
         OneStep(false);
        }
         else
         {
         OneStep(true);
         }
         delay(2); 
         
      }
      //Serial.println("bye");
  
    
   }
 
      
  
  


//  Serial.print("X-axis: ");
//
//
//  Serial.print(analogRead(Xaxis_pin));
//
//
//  Serial.print(" : ");
//
//
//  Serial.print("Y-axis: ");
//
//
//  Serial.print(analogRead(Yaxis_pin));
//
//
//  Serial.print(" : ");
//
//
//  Serial.print("Switch:  ");
//
//  Serial.println(digitalRead(SW_pin));


  delay(200);


}
