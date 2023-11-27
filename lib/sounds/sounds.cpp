#include "sounds.h"

Sounds soundsCar;

Sounds::Sounds()
{
    // fixedTimer = timerBegin(1, 20, true);                        // timer 1, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 20 -> 250 ns = 0.25 us, countUp
    // timerAttachInterrupt(fixedTimer, &fixedPlaybackTimer, true); // edge (not level) triggered
    // timerAlarmWrite(fixedTimer, fixedTimerTicks, true);          // autoreload true
    // timerAlarmEnable(fixedTimer);                                // enable
}

void IRAM_ATTR Sounds::fixedPlaybackTimer()
{
    static uint32_t curHornSample = 0; // Index of currently loaded horn sample
    static int32_t a, a1, a2 = 0;      // Input signals "a" for mixer
    static int32_t b = 0;              // Input signals "b" for mixer
    static int32_t c = 0;              // Input signals "c" for mixer
    static int32_t d = 0;              // Input signals "d" for mixer

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

    // Mixing sounds together **********************************************************************
    a = a1 + a2; // Horn & siren
    if (a < 2 && a > -2)
        a = 0; // Remove noise floor TODO, experimental
    // DAC output (groups mixed together) ****************************************************************************
    dacWrite(DAC2, constrain(((a * 8 / 10) + (b * 2 / 10) + c + d) * masterVolume / 100 + dacOffset, 0, 255)); // Mix signals, add 128 offset, write result to DAC
}
