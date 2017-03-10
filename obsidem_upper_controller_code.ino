#define fan 8
#define led 13
#define pc_out 12

void win()
{
  digitalWrite(led,LOW);
  digitalWrite(pc_out,LOW);
  digitalWrite(fan,LOW);
  delay(300000);
  startup();
}

void startup()
{

digitalWrite(11,LOW);
digitalWrite(pc_out,HIGH);
digitalWrite(led,HIGH);
digitalWrite(fan,HIGH);

digitalWrite(A0,HIGH);
digitalWrite(A1,HIGH);
digitalWrite(A2,HIGH);
digitalWrite(A3,HIGH);
digitalWrite(A4,HIGH);
digitalWrite(A5,HIGH);
}



void setup() {
  // put your setup code here, to run once:
pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(A3, OUTPUT);
pinMode(A4, OUTPUT);
pinMode(A5, OUTPUT);

pinMode(fan, OUTPUT);
pinMode(led, OUTPUT);
pinMode(pc_out, OUTPUT);

pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
pinMode(7,INPUT_PULLUP);

pinMode(11,OUTPUT);
startup()

}

void loop() {
  digitalWrite(A0,LOW);
  if (!digitalRead(4))
  {
    digitalWrite(A1,LOW);
    if (!digitalRead(7))
    {
      digitalWrite(A2,LOW);
      if (!digitalRead(2))
      {
        digitalWrite(A3,LOW);
        if(!digitalRead(3))
        {
          digitalWrite(A4,LOW);
          if(!digitalRead(5))
          {
            digitalWrite(A5,LOW);
            if(!digitalRead(6))
            {
              win();
            }
          }
        }
      }
    }
  }
  
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,HIGH);
  
  
  
  
  
  
  
  
  
  
  
  
  
}
