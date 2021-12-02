
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define echoPin PD1
#define trigPin PD2

//340m/s = 0.034 (centimeter/microseconds)
#define SPEED_OF_SOUND_WAVE 0.034

#define	delay	_delay_ms

#define MEASURE_TIME_GAP  500
char timeLimit[50];

long duration;
int distance;

int TimingCounter = 0;

ISR(TIMER1_OVF_vect)
{
	TimingCounter++;
}

int main(void)
{
	setup();
    
	for (;;) {
		loop();
	}
        
	return 0;
}


void printMessage()
{
  printf("\nPress r to check distance\n");
  printf("Press i to check distance continously for 10 sec\n");
  printf("Press t and mention time to check distance continously for specific time duration in sec\n"); 
}

void setup() {
  DDRA = 0x01;
  PORTD = 0xFF;
	
  sei();
  TIMSK = (1 << TOIE1);
  TCCR1A = 0;
	
  printf("Vehicle Parking Assistant");
  printMessage();
  delay(2000);
}

double measure_distance()
{
      PORTA &= (~(1 << trigPin));
      _delay_us(2);
      
      PORTA |= (1 << trigPin);
      _delay_us(10);
      PORTA &= (~(1 << trigPin));
	    
      TCNT1 = 0;	
      TCCR1B = 0x41;
      TIFR = 1<<ICF1;
      TIFR = 1<<TOV1;

      while ((TIFR & (1 << ICF1)) == 0);
      TCNT1 = 0;
      TCCR1B = 0x01;
      TIFR = 1<<ICF1;
      TIFR = 1<<TOV1;
      TimerOverflow = 0;

      while ((TIFR & (1 << ICF1)) == 0);
      count = ICR1 + (65535 * TimingCounter);
      duration = (double)count;
      distance = duration * SPEED_OF_SOUND_WAVE / 2;
      return distance;
}

void loop() {

    char input = Serial.read();
    if(input == 'r')
    {
      distance = measure_distance();
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

        distance = measure_distance();
        printf("Vehicle Gap Distance is: %f cm\n",distance);
        delay(MEASURE_TIME_GAP);
      }
      printMessage();
    }
    else if(input == 't')
    {
      strcat(timeLimit, Serial.readString());
      int begin_flag = 0;
      double timing = atof(timeLimit);
      while(true)
      {
        begin_flag++;
        if(begin_flag * MEASURE_TIME_GAP / 1000 > timing)
        {
          break;
        }

        distance = measure_distance();
        printf("Vehicle Gap Distance is: %f cm\n",distance);
        delay(MEASURE_TIME_GAP);
      }
      printMessage();
    }
    else
    {
      printf("Invalid Input\n");
    }
  delay(1000);
}

