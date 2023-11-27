#include "sounds/sounds.h"

void IRAM_ATTR fixedPlaybackTimer()
{

    //   // coreId = xPortGetCoreID(); // Running on core 1

    static uint32_t curHornSample = 0; // Index of currently loaded horn sample

    //   static uint32_t curSirenSample = 0;                           // Index of currently loaded siren sample
    //   static uint32_t curSound1Sample = 0;                          // Index of currently loaded sound1 sample
    //   static uint32_t curReversingSample = 0;                       // Index of currently loaded reversing beep sample
    //   static uint32_t curIndicatorSample = 0;                       // Index of currently loaded indicator tick sample
    //   static uint32_t curWastegateSample = 0;                       // Index of currently loaded wastegate sample
    //   static uint32_t curBrakeSample = 0;                           // Index of currently loaded brake sound sample
    //   static uint32_t curParkingBrakeSample = 0;                    // Index of currently loaded brake sound sample
    //   static uint32_t curShiftingSample = 0;                        // Index of currently loaded shifting sample
    //   static uint32_t curDieselKnockSample = 0;                     // Index of currently loaded Diesel knock sample
    //   static uint32_t curCouplingSample = 0;                        // Index of currently loaded trailer coupling sample
    //   static uint32_t curUncouplingSample = 0;                      // Index of currently loaded trailer uncoupling sample
    //   static uint32_t curHydraulicFlowSample = 0;                   // Index of currently loaded hydraulic flow sample
    //   static uint32_t curTrackRattleSample = 0;                     // Index of currently loaded track rattle sample
    //   static uint32_t curBucketRattleSample = 0;                    // Index of currently loaded bucket rattle sample
    //   static uint32_t curTireSquealSample = 0;                      // Index of currently loaded tire squeal sample
    //   static uint32_t curOutOfFuelSample = 0;                       // Index of currently loaded out of fuel sample
    static int32_t a, a1, a2 = 0; // Input signals "a" for mixer
      static int32_t b, b0, b1, b2, b3, b4, b5, b6, b7, b8, b9 = 0; // Input signals "b" for mixer
      static int32_t c, c1, c2, c3 = 0;                             // Input signals "c" for mixer
      static int32_t d, d1, d2 = 0;                                 // Input signals "d" for mixer
    //   static boolean knockSilent = 0;                               // This knock will be more silent
    //   static boolean knockMedium = 0;                               // This knock will be medium
    //   static uint8_t curKnockCylinder = 0;                          // Index of currently ignited zylinder

    //   // portENTER_CRITICAL_ISR(&fixedTimerMux);

    //   // Group "a" (horn & siren) ******************************************************************

    if (hornTrigger || hornLatch)
    {
        fixedTimerTicks = 4000000 / hornSampleRate;         // our fixed sampling rate
        timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

        if (curHornSample < hornSampleCount - 1)
        {
            a1 = (hornSamples[curHornSample] * hornVolumePercentage / 100);
            curHornSample++;
#ifdef HORN_LOOP // Optional "endless loop" (points to be defined manually in horn file)
            if (hornTrigger && curHornSample == hornLoopEnd)
                curHornSample = hornLoopBegin; // Loop, if trigger still present
#endif
        }
        else
        { // End of sample
            curHornSample = 0;
            a1 = 0;
            hornLatch = false;
        }
    }

    //   if (sirenTrigger || sirenLatch)
    //   {
    //     fixedTimerTicks = 4000000 / sirenSampleRate;        // our fixed sampling rate
    //     timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

    // #if defined SIREN_STOP
    //     if (!sirenTrigger)
    //     {
    //       sirenLatch = false;
    //       curSirenSample = 0;
    //       a2 = 0;
    //     }
    // #endif

    //     if (curSirenSample < sirenSampleCount - 1)
    //     {
    //       a2 = (sirenSamples[curSirenSample] * sirenVolumePercentage / 100);
    //       curSirenSample++;
    // #ifdef SIREN_LOOP // Optional "endless loop" (points to be defined manually in siren file)
    //       if (sirenTrigger && curSirenSample == sirenLoopEnd)
    //         curSirenSample = sirenLoopBegin; // Loop, if trigger still present
    // #endif
    //     }
    //     else
    //     { // End of sample
    //       curSirenSample = 0;
    //       a2 = 0;
    //       sirenLatch = false;
    //     }
    //   }
    //   if (curSirenSample > 10 && curSirenSample < 500)
    //     cannonFlash = true; // Tank cannon flash triggering in TRACKED_MODE
    //   else
    //     cannonFlash = false;

    //   // Group "b" (other sounds) **********************************************************************

    //   // Sound 1 "b0" ----
    //   if (sound1trigger)
    //   {
    //     fixedTimerTicks = 4000000 / sound1SampleRate;       // our fixed sampling rate
    //     timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

    //     if (curSound1Sample < sound1SampleCount - 1)
    //     {
    //       b0 = (sound1Samples[curSound1Sample] * sound1VolumePercentage / 100);
    //       curSound1Sample++;
    //     }
    //     else
    //     {
    //       sound1trigger = false;
    //     }
    //   }
    //   else
    //   {
    //     curSound1Sample = 0; // ensure, next sound will start @ first sample
    //     b0 = 0;
    //   }

    //   // Reversing beep sound "b1" ----
    //   if (engineRunning && escInReverse)
    //   {
    //     fixedTimerTicks = 4000000 / reversingSampleRate;    // our fixed sampling rate
    //     timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

    //     if (curReversingSample < reversingSampleCount - 1)
    //     {
    //       b1 = (reversingSamples[curReversingSample] * reversingVolumePercentage / 100);
    //       curReversingSample++;
    //     }
    //     else
    //     {
    //       curReversingSample = 0;
    //     }
    //   }
    //   else
    //   {
    //     curReversingSample = 0; // ensure, next sound will start @ first sample
    //     b1 = 0;
    //   }

    //   // Indicator tick sound "b2" ----------------------------------------------------------------------
    // #if not defined NO_INDICATOR_SOUND
    //   if (indicatorSoundOn)
    //   {
    //     fixedTimerTicks = 4000000 / indicatorSampleRate;    // our fixed sampling rate
    //     timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

    //     if (curIndicatorSample < indicatorSampleCount - 1)
    //     {
    //       b2 = (indicatorSamples[curIndicatorSample] * indicatorVolumePercentage / 100);
    //       curIndicatorSample++;
    //     }
    //     else
    //     {
    //       indicatorSoundOn = false;
    //     }
    //   }
    //   else
    //   {
    //     curIndicatorSample = 0; // ensure, next sound will start @ first sample
    //     b2 = 0;
    //   }
    // #endif

    //   // Wastegate (blowoff) sound, triggered after rapid throttle drop -----------------------------------
    //   if (wastegateTrigger)
    //   {
    //     if (curWastegateSample < wastegateSampleCount - 1)
    //     {
    //       b3 = (wastegateSamples[curWastegateSample] * rpmDependentWastegateVolume / 100 * wastegateVolumePercentage / 100);
    //       curWastegateSample++;
    //     }
    //     else
    //     {
    //       wastegateTrigger = false;
    //     }
    //   }
    //   else
    //   {
    //     b3 = 0;
    //     curWastegateSample = 0; // ensure, next sound will start @ first sample
    //   }

    //   // Air brake release sound, triggered after stop -----------------------------------------------
    //   if (airBrakeTrigger)
    //   {
    //     if (curBrakeSample < brakeSampleCount - 1)
    //     {
    //       b4 = (brakeSamples[curBrakeSample] * brakeVolumePercentage / 100);
    //       curBrakeSample++;
    //     }
    //     else
    //     {
    //       airBrakeTrigger = false;
    //     }
    //   }
    //   else
    //   {
    //     b4 = 0;
    //     curBrakeSample = 0; // ensure, next sound will start @ first sample
    //   }

    //   // Air parking brake attaching sound, triggered after engine off --------------------------------
    //   if (parkingBrakeTrigger)
    //   {
    //     if (curParkingBrakeSample < parkingBrakeSampleCount - 1)
    //     {
    //       b5 = (parkingBrakeSamples[curParkingBrakeSample] * parkingBrakeVolumePercentage / 100);
    //       curParkingBrakeSample++;
    //     }
    //     else
    //     {
    //       parkingBrakeTrigger = false;
    //     }
    //   }
    //   else
    //   {
    //     b5 = 0;
    //     curParkingBrakeSample = 0; // ensure, next sound will start @ first sample
    //   }

    //   // Pneumatic gear shifting sound, triggered while shifting the TAMIYA 3 speed transmission ------
    //   if (shiftingTrigger && engineRunning && !automatic && !doubleClutch)
    //   {
    //     if (curShiftingSample < shiftingSampleCount - 1)
    //     {
    //       b6 = (shiftingSamples[curShiftingSample] * shiftingVolumePercentage / 100);
    //       curShiftingSample++;
    //     }
    //     else
    //     {
    //       shiftingTrigger = false;
    //     }
    //   }
    //   else
    //   {
    //     b6 = 0;
    //     curShiftingSample = 0; // ensure, next sound will start @ first sample
    //   }

    //   // Diesel ignition "knock" is played in fixed sample rate section, because we don't want changing pitch! ------
    //   if (dieselKnockTriggerFirst)
    //   {
    //     dieselKnockTriggerFirst = false;
    //     curKnockCylinder = 0;
    //   }

    //   if (dieselKnockTrigger)
    //   {
    //     dieselKnockTrigger = false;
    //     curKnockCylinder++; // Count ignition sequence
    //     curDieselKnockSample = 0;
    //   }

    // #ifdef V8 // (former ADAPTIVE_KNOCK_VOLUME, rename it in your config file!)
    //   // Ford or Scania V8 ignition sequence: 1 - 5 - 4 - 2* - 6 - 3 - 7 - 8* (* = louder knock pulses, because 2nd exhaust in same manifold after 90°)
    //   if (curKnockCylinder == 4 || curKnockCylinder == 8)
    //     knockSilent = false;
    //   else
    //     knockSilent = true;
    // #endif

    // #ifdef V8_MEDIUM // (former ADAPTIVE_KNOCK_VOLUME, rename it in your config file!)
    //   // This is EXPERIMENTAL!! TODO
    //   if (curKnockCylinder == 5 || curKnockCylinder == 1)
    //     knockMedium = false;
    //   else
    //     knockMedium = true;
    // #endif

    // #ifdef V8_468 // (Chevy 468, containing 16 ignition pulses)
    //   // 1th, 5th, 9th and 13th are the loudest
    //   // Ignition sequence: 1 - 8 - 4* - 3 - 6 - 5 - 7* - 2
    //   if (curKnockCylinder == 1 || curKnockCylinder == 5 || curKnockCylinder == 9 || curKnockCylinder == 13)
    //     knockSilent = false;
    //   else
    //     knockSilent = true;
    // #endif

    // #ifdef V2
    //   // V2 engine: 1st and 2nd knock pulses (of 4) will be louder
    //   if (curKnockCylinder == 1 || curKnockCylinder == 2)
    //     knockSilent = false;
    //   else
    //     knockSilent = true;
    // #endif

    // #ifdef R6
    //   // R6 inline 6 engine: 6th knock pulse (of 6) will be louder
    //   if (curKnockCylinder == 6)
    //     knockSilent = false;
    //   else
    //     knockSilent = true;
    // #endif

    // #ifdef R6_2
    //   // R6 inline 6 engine: 6th and 3rd knock pulse (of 6) will be louder
    //   if (curKnockCylinder == 6 || curKnockCylinder == 3)
    //     knockSilent = false;
    //   else
    //     knockSilent = true;
    // #endif

    //   if (curDieselKnockSample < knockSampleCount)
    //   {
    // #if defined RPM_DEPENDENT_KNOCK // knock volume also depending on engine rpm
    //     b7 = (knockSamples[curDieselKnockSample] * dieselKnockVolumePercentage / 100 * throttleDependentKnockVolume / 100 * rpmDependentKnockVolume / 100);
    // #elif defined EXCAVATOR_MODE // knock volume also depending on hydraulic load
    //     b7 = (knockSamples[curDieselKnockSample] * dieselKnockVolumePercentage / 100 * throttleDependentKnockVolume / 100 * hydraulicDependentKnockVolume / 100);
    // #else                        // Just depending on throttle
    //     b7 = (knockSamples[curDieselKnockSample] * dieselKnockVolumePercentage / 100 * throttleDependentKnockVolume / 100);
    // #endif
    //     curDieselKnockSample++;
    //     if (knockSilent && !knockMedium)
    //       b7 = b7 * dieselKnockAdaptiveVolumePercentage / 100; // changing knock volume according to engine type and cylinder!
    //     if (knockMedium)
    //       b7 = b7 * dieselKnockAdaptiveVolumePercentage / 75;
    //   }

    // #if not defined EXCAVATOR_MODE
    //   // Trailer coupling sound, triggered by switch -----------------------------------------------
    // #ifdef COUPLING_SOUND
    //   if (couplingTrigger)
    //   {
    //     if (curCouplingSample < couplingSampleCount - 1)
    //     {
    //       b8 = (couplingSamples[curCouplingSample] * couplingVolumePercentage / 100);
    //       curCouplingSample++;
    //     }
    //     else
    //     {
    //       couplingTrigger = false;
    //     }
    //   }
    //   else
    //   {
    //     b8 = 0;
    //     curCouplingSample = 0; // ensure, next sound will start @ first sample
    //   }

    //   // Trailer uncoupling sound, triggered by switch -----------------------------------------------
    //   if (uncouplingTrigger)
    //   {
    //     if (curUncouplingSample < uncouplingSampleCount - 1)
    //     {
    //       b9 = (uncouplingSamples[curUncouplingSample] * couplingVolumePercentage / 100);
    //       curUncouplingSample++;
    //     }
    //     else
    //     {
    //       uncouplingTrigger = false;
    //     }
    //   }
    //   else
    //   {
    //     b9 = 0;
    //     curUncouplingSample = 0; // ensure, next sound will start @ first sample
    //   }
    // #endif
    // #endif

    //   // Group "c" (excavator sounds) **********************************************************************

    // #if defined EXCAVATOR_MODE

    //   // Hydraulic fluid flow sound -----------------------
    //   if (curHydraulicFlowSample < hydraulicFlowSampleCount - 1)
    //   {
    //     c1 = (hydraulicFlowSamples[curHydraulicFlowSample] * hydraulicFlowVolumePercentage / 100 * hydraulicFlowVolume / 100);
    //     curHydraulicFlowSample++;
    //   }
    //   else
    //   {
    //     curHydraulicFlowSample = 0;
    //   }

    //   // Track rattle sound -----------------------
    //   if (curTrackRattleSample < trackRattleSampleCount - 1)
    //   {
    //     c2 = (trackRattleSamples[curTrackRattleSample] * trackRattleVolumePercentage / 100 * trackRattleVolume / 100);
    //     curTrackRattleSample++;
    //   }
    //   else
    //   {
    //     curTrackRattleSample = 0;
    //   }

    //   // Bucket rattle sound -----------------------
    //   if (bucketRattleTrigger)
    //   {
    //     if (curBucketRattleSample < bucketRattleSampleCount - 1)
    //     {
    //       c3 = (bucketRattleSamples[curBucketRattleSample] * bucketRattleVolumePercentage / 100);
    //       curBucketRattleSample++;
    //     }
    //     else
    //     {
    //       bucketRattleTrigger = false;
    //     }
    //   }
    //   else
    //   {
    //     c3 = 0;
    //     curBucketRattleSample = 0; // ensure, next sound will start @ first sample
    //   }
    // #endif

    //   // Group "d" (additional sounds) **********************************************************************

    // #if defined TIRE_SQUEAL
    //   // Tire squeal sound -----------------------
    //   if (curTireSquealSample < tireSquealSampleCount - 1)
    //   {
    //     d1 = (tireSquealSamples[curTireSquealSample] * tireSquealVolumePercentage / 100 * tireSquealVolume / 100);
    //     curTireSquealSample++;
    //   }
    //   else
    //   {
    //     d1 = 0;
    //     curTireSquealSample = 0;
    //   }
    // #endif

    // #if defined BATTERY_PROTECTION
    //   // Out of fuel sound, triggered by battery voltage -----------------------------------------------
    //   if (outOfFuelMessageTrigger)
    //   {
    //     if (curOutOfFuelSample < outOfFuelSampleCount - 1)
    //     {
    //       d2 = (outOfFuelSamples[curOutOfFuelSample] * outOfFuelVolumePercentage / 100);
    //       curOutOfFuelSample++;
    //     }
    //     else
    //     {
    //       outOfFuelMessageTrigger = false;
    //     }
    //   }
    //   else
    //   {
    //     d2 = 0;
    //     curOutOfFuelSample = 0; // ensure, next sound will start @ first sample
    //   }
    // #endif

      // Mixing sounds together **********************************************************************
      a = a1 + a2; // Horn & siren
      // if (a < 2 && a > -2) a = 0; // Remove noise floor TODO, experimental
      b = b0 * 5 + b1 + b2 / 2 + b3 + b4 + b5 + b6 + b7 + b8 + b9; // Other sounds
      c = c1 + c2 + c3;                                            // Excavator sounds
      d = d1 + d2;                                                 // Additional sounds

      // DAC output (groups mixed together) ****************************************************************************

      // dacDebug = constrain(((a * 8 / 10) + (b * 2 / 10) + c + d) * masterVolume / 100 + dacOffset, 0, 255); // Mix signals, add 128 offset, write result to DAC
      dacWrite(DAC2, constrain(((a * 8 / 10) + (b * 2 / 10) + c + d) * masterVolume / 100 + dacOffset, 0, 255)); // Mix signals, add 128 offset, write result to DAC
      // dacWrite(DAC2, constrain( a2 * masterVolume / 100 + dacOffset, 0, 255)); // Mix signals, add 128 offset, write result to DAC
      // dacWrite(DAC2, 0);

      // portEXIT_CRITICAL_ISR(&fixedTimerMux);
}
