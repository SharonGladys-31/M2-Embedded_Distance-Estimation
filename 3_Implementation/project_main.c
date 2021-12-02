
#define echoPin 2
#define trigPin 3

//340m/s = 0.034 (centimeter/microseconds)
#define SPEED_OF_SOUND_WAVE 0.034

#define MEASURE_TIME_GAP  500
String timeLimit;

long duration;
int distance;

void printMessage()
{
  Serial.println("\nPress r to check distance");
  Serial.println("Press i to check distance continously for 10 sec");
  Serial.println("Press t and mention time to check distance continously for specific time duration in sec"); 
}

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  Serial.println("Vehicle Parking Assistant");
  printMessage();
  delay(2000);
}

void loop() {
  
  if (Serial.available() > 0) {
    char input = Serial.read();
    if(input == 'r')
    {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      
      duration = pulseIn(echoPin, HIGH);
      distance = duration * SPEED_OF_SOUND_WAVE / 2;
      Serial.print("Vehicle Gap Distance is: ");
      Serial.print(distance);
      Serial.println(" cm");
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
        delayMicroseconds(2);
        
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        
        duration = pulseIn(echoPin, HIGH);
        distance = duration * SPEED_OF_SOUND_WAVE / 2;
        Serial.print("Vehicle Gap Distance is: ");
        Serial.print(distance);
        Serial.println(" cm");
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
        delayMicroseconds(2);
        
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        
        duration = pulseIn(echoPin, HIGH);
        distance = duration * SPEED_OF_SOUND_WAVE / 2;
        Serial.print("Vehicle Gap Distance is: ");
        Serial.print(distance);
        Serial.println(" cm");
        delay(MEASURE_TIME_GAP);
      }
      printMessage();
    }
    else
    {
      Serial.println("Invalid Input");
    }
  }
  delay(1000);
}

