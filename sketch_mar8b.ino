#include <Servo.h>

//hodnota pro rychlost zvuku
#define SOUND_SPEED 0.034 

#define Rychlost 20

//pin pro integrovanou LED
#define buildLEDPin 2

#define RLEDPin 14
#define GLEDPin 27
#define BLEDPin 34

//definování servo pinů
#define SERVO1_PIN 23
#define SERVO2_PIN 22
#define SERVO3_PIN 21
#define SERVO4_PIN 19

//definování pinů pro ultrazvukový senzor
#define trigPin 13
#define echoPin 12

//aktivování servo motorů
Servo LChodidlo;   
Servo RChodidlo;
Servo RNoha;
Servo LNoha;

long duration;
float vzdalenost;
int cas = 0;
long randNumber;

void dopredu();
void doleva();
void doprava();

void setup() {
  //ultrazvukový senzor
  Serial.begin(9600); //začne sériovou komunikaci
  pinMode(trigPin, OUTPUT); // nastaví trigPin jako výstup
  pinMode(echoPin, INPUT); // nastaví echoPin jako vstup

  //nastavení pinů pro serva
  RNoha.attach(SERVO1_PIN);  
  LChodidlo.attach(SERVO2_PIN);
  RChodidlo.attach(SERVO3_PIN);
  LNoha.attach(SERVO4_PIN);

  //nastavení pinů jako výstupy
  pinMode(RLEDPin,OUTPUT);
  pinMode(GLEDPin,OUTPUT);
  pinMode(BLEDPin,OUTPUT);
  pinMode(buildLEDPin,OUTPUT);
  
  //robot do zakladni polohy
  RNoha.write(90);  
  RChodidlo.write(90);
  LChodidlo.write(90);
  LNoha.write(90);

  delay(500);

  randomSeed(analogRead(0));

}

void loop() {

  //fungování ultrazvukového senzoru
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(5);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        vzdalenost = duration / 58.31;
        Serial.print("vzdalenost (cm): ");
        Serial.println(vzdalenost);

//ze základní pozice do podprogramu dopredu
  for (int pos = 90; pos >= 60; pos -= 1)
  {
   LChodidlo.write(pos);
   RChodidlo.write(pos);             
   delay(Rychlost);  
  }

  for (int pos = 90; pos <= 120; pos += 1)
  {
   LNoha.write(pos);
   RNoha.write(pos);             
   delay(Rychlost);
  }

while (vzdalenost > 10)
{
  dopredu();
}

//z podprogramu dopredu do zakladni pozice
for (int pos = 60; pos <= 90; pos += 1) 
    {
    LChodidlo.write(pos);
    RChodidlo.write(pos);             
    delay(Rychlost);  
    }

    for (int pos = 120; pos >= 90; pos -= 1) 
    {
    LNoha.write(pos);
    RNoha.write(pos);            
    delay(Rychlost);  
    }

  delay(500);

  randNumber = random(2);
  Serial.print("nahodne cislo je: ");
  Serial.println(randNumber);

  switch(randNumber)
  {
    case 0:
      Serial.print("otocka doleva");

      //ze zakladni pozice do podprogramu doleva
      for (int pos = 90; pos >= 60; pos -= 1) 
      {
        LChodidlo.write(pos);
        RChodidlo.write(pos);             
        delay(Rychlost);  
      }

      for (int pos = 90; pos <= 110; pos += 1) 
      {
        RNoha.write(pos);            
        delay(Rychlost);  
      }

      for(int i = 0; i < 5; i += 1)
      {
        doleva();
      }

      //z podprogramu doleva do zakladni pozice
      for (int pos = 60; pos <= 90; pos += 1) 
      {
        LChodidlo.write(pos);
        RChodidlo.write(pos);          
        delay(Rychlost);  
      }

      for (int pos = 110; pos >= 90; pos -= 1) 
      {
        RNoha.write(pos);             
        delay(Rychlost);  
      }

      delay(500);

      break;

    case 1:
      Serial.print("otocka doprava");

      //ze zakladni pozice do podprogramu doprava
      for (int pos = 90; pos <= 130; pos += 1) 
      {
        LChodidlo.write(pos);
        RChodidlo.write(pos);             
        delay(Rychlost);  
      }

      for (int pos = 90; pos <= 70; pos += 1) 
      {
        LNoha.write(pos);            
        delay(Rychlost);  
      }

      for(int i = 0; i < 5; i += 1)
      {
        doprava();
      }

      //z podprogramu doprava do zakladni pozice
      for (int pos = 130; pos >= 90; pos -= 1) 
      {
        LChodidlo.write(pos);
        RChodidlo.write(pos);          
        delay(Rychlost);  
      }

      for (int pos = 70; pos <= 90; pos += 1) 
      {
        LNoha.write(pos);             
        delay(Rychlost);  
      }

      delay(500);
      
      break;
  }
}

/****************PODPROGRAMY****************/

void dopredu() {

    for (int pos = 60; pos <= 130; pos += 1) 
    {
    LChodidlo.write(pos);
    RChodidlo.write(pos);             
    delay(Rychlost);  
    }

    for (int pos = 120; pos >= 60; pos -= 1) 
    {
    LNoha.write(pos);
    RNoha.write(pos);            
    delay(Rychlost);  
    }

    for (int pos = 130; pos >= 60; pos -= 1) 
  {
   LChodidlo.write(pos);
   RChodidlo.write(pos);             
   delay(Rychlost);  
   }

  for (int pos = 60; pos <= 120; pos += 1) 
    {
    LNoha.write(pos);
    RNoha.write(pos);             
    delay(Rychlost);  

    if(pos == 90)
      {
        //fungování ultrazvukového senzoru
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(5);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        vzdalenost = duration / 58.31;
        Serial.print("vzdalenost (cm): ");
        Serial.println(vzdalenost);

      }
    }
}

void doleva() {
  for (int pos = 60; pos <= 130; pos += 1) 
    {
    LChodidlo.write(pos);
    RChodidlo.write(pos);          
    delay(Rychlost);  
    }

     for (int pos = 110; pos >= 80; pos -= 1) 
    {
    RNoha.write(pos);             
    delay(Rychlost);  
    }

     for (int pos = 130; pos >= 60; pos -= 1) 
    {
    LChodidlo.write(pos);
    RChodidlo.write(pos);          
    delay(Rychlost);  
    }

  for (int pos = 80; pos <= 110; pos += 1) 
    {
    RNoha.write(pos);            
    delay(Rychlost);  
    }
}

void doprava() {
    for (int pos = 130; pos >= 60; pos -= 1) 
    {
    LChodidlo.write(pos);
    RChodidlo.write(pos);          
    delay(Rychlost);  
    }

    for (int pos = 70; pos <= 100; pos += 1) 
    {
    LNoha.write(pos);             
    delay(Rychlost);  
    }

    for(int pos = 60; pos <= 130; pos += 1)  
    {
    LChodidlo.write(pos);
    RChodidlo.write(pos);          
    delay(Rychlost);  
    }

    for (int pos = 100; pos >= 70; pos -= 1) 
    {
    LNoha.write(pos);            
    delay(Rychlost);  
    }
}
