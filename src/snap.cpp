#include "snap.h"
#include "config.h"
#include <Arduino.h>
int snap_frames = 0;
int snap_current = 0;
int snap_delay = 0;
int snap_exposure = 0;
int snap_during = 0;
void snap_init()
{
    pinMode(SNAP_PIN, OUTPUT);
    pinMode(FOCUS_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}
void snap_run()
{
    if(snap_frames>0)
    {
        if(snap_current==0)
        {
            digitalWrite(LED_PIN, LOW);
            for(int i=0;i<snap_delay;i++)
            {
                delay(1000);
            }
        }
        if(snap_exposure>0)
        {
            digitalWrite(LED_PIN, HIGH);
            for(int i=0;i<snap_exposure;i++)
            {
                delay(1000);
            }
        }
        if(snap_during>0)
        {
            digitalWrite(LED_PIN, LOW);
            for(int i=0;i<snap_during;i++)
            {
                delay(1000);
            }
        }
        snap_current++;
        if(snap_current==snap_frames)
        {
            snap_frames = 0;
            snap_current = 0;
        }
    }
}

void snap_add_task(int frames, int delay, int exposure, int during)
{
    if(snap_frames==0)
    {
        snap_frames = frames;
        snap_delay = delay;
        snap_exposure = exposure;
        snap_during = during;
        snap_current = 0;
    }
}
int snap_get_frames()
{
    return snap_frames;
}
int snap_get_current()
{
    return snap_current;
}
void snap_cancel_task()
{
    snap_frames = 0;
    snap_current = 0;
}