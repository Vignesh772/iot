//Written By Nikodem Bartnik - nikodembartnik.pl
#define STEPPER_PIN_1 D5
#define STEPPER_PIN_2 D6
#define STEPPER_PIN_3 D7
#define STEPPER_PIN_4 D8
int step_number = 0;
void setup() {

  Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}

  
pinMode(STEPPER_PIN_1, OUTPUT);
pinMode(STEPPER_PIN_2, OUTPUT);
pinMode(STEPPER_PIN_3, OUTPUT);
pinMode(STEPPER_PIN_4, OUTPUT);

}

void loop() {
  //int data=0;
  int turn;
  if (Serial.available()) {
    char data=Serial.read();
    Serial.write(data);
  if (data=='1')
  {
    turn =0;
    while(turn<1)
    {
   for(int i=0;i<512;i++)
   {
    OneStep(false);
    delay(2);
  
    
   }
   turn++;
    }

    turn =0;
    while(turn<1)
    {
   for(int i=0;i<512;i++)
   {
    OneStep(true);
    delay(2);
  
    
   }
   turn++;
    }
  }
if(data=='0')
{
  turn =0;
  while(turn<1)
  {
  for(int i=0;i<512;i++)
 {
  OneStep(true);
  delay(2);
  
 }
 turn++;
  }

  turn =0;
  while(turn<1)
  {
  for(int i=0;i<512;i++)
 {
  OneStep(false);
  delay(2);
  
 }
 turn++;
  }
  
  }
  }

}


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
