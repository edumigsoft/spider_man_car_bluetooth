// #include "sounds/sounds.h"

// void IRAM_ATTR fixedPlaybackTimer()
// {
//     static uint32_t curHornSample = 0; // Index of currently loaded horn sample
//     static int32_t a, a1, a2 = 0;      // Input signals "a" for mixer
//     static int32_t b = 0;              // Input signals "b" for mixer
//     static int32_t c = 0;              // Input signals "c" for mixer
//     static int32_t d = 0;              // Input signals "d" for mixer

//     if (hornTrigger || hornLatch)
//     {
//         fixedTimerTicks = 4000000 / hornSampleRate;         // our fixed sampling rate
//         timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

//         if (curHornSample < hornSampleCount - 1)
//         {
//             a1 = (hornSamples[curHornSample] * hornVolumePercentage / 100);
//             curHornSample++;
// #ifdef HORN_LOOP // Optional "endless loop" (points to be defined manually in horn file)
//             if (hornTrigger && curHornSample == hornLoopEnd)
//                 curHornSample = hornLoopBegin; // Loop, if trigger still present
// #endif
//         }
//         else
//         { // End of sample
//             curHornSample = 0;
//             a1 = 0;
//             hornLatch = false;
//         }
//     }

//     // Mixing sounds together **********************************************************************
//     a = a1 + a2; // Horn & siren
//     // if (a < 2 && a > -2) a = 0; // Remove noise floor TODO, experimental
//     // b = b0 * 5 + b1 + b2 / 2 + b3 + b4 + b5 + b6 + b7 + b8 + b9; // Other sounds
//     // c = c1 + c2 + c3;                                            // Excavator sounds
//     // d = d1 + d2;                                                 // Additional sounds

//     // DAC output (groups mixed together) ****************************************************************************

//     // dacDebug = constrain(((a * 8 / 10) + (b * 2 / 10) + c + d) * masterVolume / 100 + dacOffset, 0, 255); // Mix signals, add 128 offset, write result to DAC
//     dacWrite(DAC2, constrain(((a * 8 / 10) + (b * 2 / 10) + c + d) * masterVolume / 100 + dacOffset, 0, 255)); // Mix signals, add 128 offset, write result to DAC
// }
