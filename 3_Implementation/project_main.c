
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>


#define echoPin PD1
#define trigPin PD2

//340m/s = 0.034 (centimeter/microseconds)
#define SPEED_OF_SOUND_WAVE 0.034

#define	delay	_delay_ms

#define MEASURE_TIME_GAP  500
char timeLimit[50];

long duration;
int distance;

void printMessage()
{
  printf("\nPress r to check distance\n");
  printf("Press i to check distance continously for 10 sec\n");
  printf("Press t and mention time to check distance continously for specific time duration in sec\n"); 
}

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  printf("Vehicle Parking Assistant");
  printMessage();
  delay(2000);
}

void loop() {
  
  if (Serial.available() > 0) {
    char input = Serial.read();
    if(input == 'r')
    {
      digitalWrite(trigPin, LOW);
      _delay_us(2);
      
      digitalWrite(trigPin, HIGH);
      _delay_us(10);
      digitalWrite(trigPin, LOW);
      
      duration = pulseIn(echoPin, HIGH);
      distance = duration * SPEED_OF_SOUND_WAVE / 2;
      printf("Vehicle Gap Distance is: %f cm\n",distance);
      printMessage();
    }
    else if(input == 'i')
    {
      int begin_flag = 0;
      double timing = 10;
      while(true)
      {
        begin_flag++;
        if(begin_flag * MEASURE_TIME_GAP / 1000 > timing)
        {
          break;
        }
        
        digitalWrite(trigPin, LOW);
        _delay_us(2);
        
        digitalWrite(trigPin, HIGH);
        _delay_us(10);
        digitalWrite(trigPin, LOW);
        
        duration = pulseIn(echoPin, HIGH);
        distance = duration * SPEED_OF_SOUND_WAVE / 2;
        printf("Vehicle Gap Distance is: %f cm\n",distance);
        delay(MEASURE_TIME_GAP);
      }
      printMessage();
    }
    else if(input == 't')
    {
      timeLimit = Serial.readString();
      Serial.println(timeLimit);
      int begin_flag = 0;
      double timing = timeLimit.toInt();
      while(true)
      {
        begin_flag++;
        if(begin_flag * MEASURE_TIME_GAP / 1000 > timing)
        {
          break;
        }
        
        digitalWrite(trigPin, LOW);
        _delay_us(2);
        
        digitalWrite(trigPin, HIGH);
        _delay_us(10);
        digitalWrite(trigPin, LOW);
        
        duration = pulseIn(echoPin, HIGH);
        distance = duration * SPEED_OF_SOUND_WAVE / 2;
        printf("Vehicle Gap Distance is: %f cm\n",distance);
        delay(MEASURE_TIME_GAP);
      }
      printMessage();
    }
    else
    {
      printf("Invalid Input\n");
    }
  }
  delay(1000);
}

