#include <Arduino.h>
#include "snap.h"
#include "service.h"
void setup()
{
    snap_init();
    service_init();
}
void loop()
{
    snap_run();
}