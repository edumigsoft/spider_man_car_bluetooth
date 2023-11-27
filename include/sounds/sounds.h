#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include "Arduino.h"
#include "CarHorn.h" // A boring car horn
#include "VwBeetleidle.h"

// Engine parameters ----------------------------------------------------------------------------------------------------
// Engine max. RPM in % of idle RPM. About 200% for big Diesels, 400% for fast running motors.
uint32_t MAX_RPM_PERCENTAGE = 320; // NOTE! Was called TOP_SPEED_MULTIPLIER (TSM) in earlier versions and was a multiplier instead of a percentage!
volatile int hornVolumePercentage = 100; // Adjust the horn volume (usually = 100%)

// Sound volumes
volatile int16_t masterVolume = 100; // Master volume percentage
volatile uint8_t dacOffset = 0;

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