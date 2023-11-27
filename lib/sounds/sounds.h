#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include "Arduino.h"
// #include "sounds/CarHorn.h" // A boring car horn
#include "sounds/VwBeetle.h"

// Sound
volatile boolean hornTrigger = false; // Trigger for horn on / off

// Sound latches
volatile boolean hornLatch = false; // Horn latch bit

// Sampling intervals for interrupt timer (adjusted according to your sound file sampling rate)
uint32_t maxSampleInterval = 4000000 / sampleRate;
uint32_t minSampleInterval = 4000000 / sampleRate * 100 / MAX_RPM_PERCENTAGE;

// Interrupt timer for fixed sample rate playback (horn etc., playing in parallel with engine sound)
hw_timer_t *fixedTimer = NULL;
portMUX_TYPE fixedTimerMux = portMUX_INITIALIZER_UNLOCKED;
volatile uint32_t fixedTimerTicks = maxSampleInterval;

//
void IRAM_ATTR fixedPlaybackTimer();

#endif // __SOUNDS_H__