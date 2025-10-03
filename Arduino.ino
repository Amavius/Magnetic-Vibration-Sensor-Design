#include <Arduino.h>
#include <TimerOne.h>
#include <string.h>

// -----------------------------------------------------------------------------
// Sampling configuration
// -----------------------------------------------------------------------------
constexpr uint8_t ADC_CHANNEL = A0;
constexpr uint16_t SAMPLING_FREQ_HZ = 40;          // Samples per second
constexpr float TOTAL_SAMPLE_TIME_S = 5.0f;        // Capture window in seconds
constexpr uint16_t NUMBER_OF_SAMPLES =
    static_cast<uint16_t>(TOTAL_SAMPLE_TIME_S * SAMPLING_FREQ_HZ);

// Shared state between the interrupt service routine and the main loop.
volatile uint16_t samples[NUMBER_OF_SAMPLES];
volatile uint16_t samplingCounter = 0;
volatile bool samplingFinished = false;

// -----------------------------------------------------------------------------
// Utility helpers
// -----------------------------------------------------------------------------
void resetSamplingState() {
  samplingCounter = 0;
  samplingFinished = false;
}

void sampleISR();

// -----------------------------------------------------------------------------
// Arduino entry points
// -----------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);  // Faster upload of captured samples

  resetSamplingState();

  Timer1.initialize(1'000'000UL / SAMPLING_FREQ_HZ);
  Timer1.attachInterrupt(sampleISR);
}

void loop() {
  if (!samplingFinished) {
    return;
  }

  // Copy the captured data while interrupts are disabled to prevent race
  // conditions when the ISR restarts writing new samples.
  uint16_t capturedSamples[NUMBER_OF_SAMPLES];
  uint16_t capturedCount = 0;

  noInterrupts();
  capturedCount = samplingCounter;
  memcpy(capturedSamples, (const void*)samples, sizeof(capturedSamples));
  resetSamplingState();
  interrupts();

  for (uint16_t i = 0; i < capturedCount; ++i) {
    Serial.println(capturedSamples[i]);
  }
}

// -----------------------------------------------------------------------------
// Interrupt service routine
// -----------------------------------------------------------------------------
void sampleISR() {
  if (samplingCounter < NUMBER_OF_SAMPLES) {
    samples[samplingCounter++] = analogRead(ADC_CHANNEL);
    if (samplingCounter >= NUMBER_OF_SAMPLES) {
      samplingFinished = true;
    }
  }
}
