
const int bucket_power = 7;
const int bucket_read = A0;

const int ir_read = 11;

const int relay = 12;
const int buttonPin_bucket = 2;  
const int buttonPin_ir = 3;  
const int buttonPin_man = 4;  

const int ledPin_bucket = 8; 
const int ledPin_ir = 9; 
const int ledPin_man = 10; 

int ledState_bucket = LOW;      
int buttonState_bucket;          
int lastbuttonState_bucket = LOW;  
unsigned long lastDebounceTime_bucket = 0;
unsigned long debounceDelay_bucket = 50;

int ledState_ir = LOW;      
int buttonState_ir;          
int lastbuttonState_ir = LOW;  
unsigned long lastDebounceTime_ir = 0;
unsigned long debounceDelay_ir = 50;

int ledState_man = LOW;      
int buttonState_man;          
int lastbuttonState_man = LOW;  
unsigned long lastDebounceTime_man = 0;
unsigned long debounceDelay_man = 50;



void setup() {
  Serial.begin(9600);

  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  
  pinMode(bucket_power, OUTPUT);
  pinMode(bucket_read, INPUT);
  digitalWrite(bucket_power, HIGH);

  
  pinMode(buttonPin_bucket, INPUT);
  pinMode(ledPin_bucket, OUTPUT);
  digitalWrite(ledPin_bucket, ledState_bucket);

  pinMode(buttonPin_man, INPUT);
  pinMode(ledPin_man, OUTPUT);
  digitalWrite(ledPin_man, ledState_man);

  pinMode(buttonPin_ir, INPUT);
  pinMode(ledPin_ir, OUTPUT);
  digitalWrite(ledPin_ir, ledState_ir);
  
}

int is_filled()
{
  if(ledState_man)
  {
    digitalWrite(relay, HIGH);
    ledState_man = !ledState_man;
    digitalWrite(ledPin_man, ledState_man);
  }
  
  digitalWrite(relay, LOW);
  int filled = 0;
  int count = 0;
  
  while (count<100)
  {
    int a = analogRead(bucket_read);
    if(a>1000)
    {
      count ++;
    }
    else
    {
      count =0;
    }
    
    int reading_bucket = digitalRead(buttonPin_bucket);


    if (reading_bucket != lastbuttonState_bucket) {
      
      lastDebounceTime_bucket = millis();
    }
  
    if ((millis() - lastDebounceTime_bucket) > debounceDelay_bucket) {
    
      if (reading_bucket != buttonState_bucket) {
        buttonState_bucket = reading_bucket;
  
        
        if (buttonState_bucket == HIGH) {
          ledState_bucket = !ledState_bucket;
        }
      }
    }
    if (!ledState_bucket)
    {
      digitalWrite(relay, HIGH);
      digitalWrite(ledPin_bucket, ledState_bucket);
      return filled;
    }

    lastbuttonState_bucket = reading_bucket;
    
    
    
    
    
  }

  if (count >= 100)
  {
    filled = 1;
    digitalWrite(relay, HIGH);
  }
  return filled;
}

void ir_mode()
{
  if(ledState_man)
  {
    digitalWrite(relay, HIGH);
    ledState_man = !ledState_man;
    digitalWrite(ledPin_man, ledState_man);
  }
  int ir_value;
  while(true)
  {
    ir_value=digitalRead(ir_read);
    
    if(ir_value==0)
    {
      Serial.println(ir_value);
      digitalWrite(relay, LOW);
      delay(5000);
    }
    else
    {
    digitalWrite(relay, HIGH);
    }

      int reading_ir = digitalRead(buttonPin_ir);


      if (reading_ir != lastbuttonState_ir) {
        
        lastDebounceTime_ir = millis();
      }
    
      if ((millis() - lastDebounceTime_ir) > debounceDelay_ir) {
      
        if (reading_ir != buttonState_ir) {
          buttonState_ir = reading_ir;
    
          
          if (buttonState_ir == HIGH) {
            ledState_ir = !ledState_ir;
          }
        }
      }
    
        if (!ledState_ir)
        {
          digitalWrite(relay, HIGH);
        
          digitalWrite(ledPin_ir, ledState_ir);
          return;
        }
      
         
    
      lastbuttonState_ir = reading_ir;

    
  }
  
}
void loop() {
  
  int reading_bucket = digitalRead(buttonPin_bucket);


  if (reading_bucket != lastbuttonState_bucket) {
    
    lastDebounceTime_bucket = millis();
  }

  if ((millis() - lastDebounceTime_bucket) > debounceDelay_bucket) {
  
    if (reading_bucket != buttonState_bucket) {
      buttonState_bucket = reading_bucket;

      
      if (buttonState_bucket == HIGH) {
        ledState_bucket = !ledState_bucket;
      }
    }
  }

  if (ledState_bucket)
  {
    digitalWrite(ledPin_bucket, ledState_bucket);
    int filled = is_filled();
    if (filled)
    {
      ledState_bucket = !ledState_bucket;
      digitalWrite(ledPin_bucket, ledState_bucket);
      
    }
    
  }
  

  lastbuttonState_bucket = reading_bucket;


  ////////////////////////////////////////////////////////////////////

  
  int reading_man = digitalRead(buttonPin_man);


  if (reading_man != lastbuttonState_man) {
    
    lastDebounceTime_man = millis();
  }

  if ((millis() - lastDebounceTime_man) > debounceDelay_man) {
  
    if (reading_man != buttonState_man) {
      buttonState_man = reading_man;

      
      if (buttonState_man == HIGH) {
        ledState_man = !ledState_man;
      }
    }
  }
  digitalWrite(ledPin_man, ledState_man);
   if(ledState_man)
   {
      
      digitalWrite(relay, LOW);
      
   }
   else
   {
      digitalWrite(relay, HIGH);
    
   }
   
     

  lastbuttonState_man = reading_man;

  ////////////////////////////////////////////////////////////////////////////////////////

  
  int reading_ir = digitalRead(buttonPin_ir);


  if (reading_ir != lastbuttonState_ir) {
    
    lastDebounceTime_ir = millis();
  }

  if ((millis() - lastDebounceTime_ir) > debounceDelay_ir) {
  
    if (reading_ir != buttonState_ir) {
      buttonState_ir = reading_ir;

      
      if (buttonState_ir == HIGH) {
        ledState_ir = !ledState_ir;
      }
    }
  }


    digitalWrite(ledPin_ir, ledState_ir);
    if (ledState_ir)
    {
      ir_mode();
    }
     

  lastbuttonState_ir = reading_ir;
  
}
