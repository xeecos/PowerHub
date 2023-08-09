#include <Arduino.h>
#include "snap.h"
#include "service.h"
void setup()
{
    USBSerial.begin();
    snap_init();
    service_init();
}
void loop()
{
    snap_run();
}