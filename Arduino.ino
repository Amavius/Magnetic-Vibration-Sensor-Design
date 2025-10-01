#include <TimerOne.h>
#include <MsTimer2.h>

/******** Constants ********/
#define ADC_CHANNEL A0


// Sampling
const int SAMPLING_FREQ = 40;
const float TOTAL_SAMPLE_TIME = 5;
const int NUMBER_OF_SAMPLES = TOTAL_SAMPLE_TIME*SAMPLING_FREQ;

int SAMPLES[NUMBER_OF_SAMPLES];
long SAMPLING_COUNTER;
bool FINISHED=false;


void setup () {
  for (int i = 0 ; i < NUMBER_OF_SAMPLES ; i++) {
    SAMPLES [i] =- 1;
  }

  Serial.begin(57600);


  Timer1.initialize(1e6/SAMPLING_FREQ);
  Timer1.attachInterrupt(SAMPLING);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (FINISHED) {
    for (int i = 0 ; i < NUMBER_OF_SAMPLES ; i++) {
      Serial.println(SAMPLES[i] ) ;
    }
    FINISHED=false;
  }
}


void SAMPLING () {
if (SAMPLING_COUNTER == NUMBER_OF_SAMPLES) {
Timer1.detachInterrupt() ;
FINISHED=true;
}else {
SAMPLES [SAMPLING_COUNTER]=analogRead(ADC_CHANNEL);
SAMPLING_COUNTER++;
}
}
