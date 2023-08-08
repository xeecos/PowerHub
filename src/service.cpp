#include "service.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include "config.h"
#include "snap.h"

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void service_init()
{
    WiFi.softAP("EZ-SNAP", "");
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        char * result = (char*)malloc(64);
        memset(result,0,64);
        sprintf(result,"{\"frames\":%d,\"current\":%d}",snap_get_frames(),snap_get_current());
        request->send(200, "text/json", result);
        free(result); });

    server.on("/snap", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("action")) {
            if(request->getParam("value")->value().equals("add"))
            {
                int frames = request->getParam("frames")->value().toInt();
                int delay = request->getParam("delay")->value().toInt();
                int exposure = request->getParam("exposure")->value().toInt();
                int during = request->getParam("during")->value().toInt();
                snap_add_task(frames,delay,exposure,during);
            }
            else if(request->getParam("value")->value().equals("cancel"))
            {
                snap_cancel_task();
            }
        }
        request->send(200, "text/json", "{\"res\":\"ok\"}"); });

    SPIFFS.begin(true);
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");
    server.begin();
}
