#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <WiFiClient.h>
#include <WiFiManager.h>

#include "laser_hardware.h"

LaserHardware hardware;

ESP8266WebServer server(80);

void setup(void)
{
  // Setup hardware
  Serial.begin(9600);
  hardware.begin();

  // Setup network
  char hostname[64];
  snprintf(hostname, 64, "pewpew-%06x", ESP.getChipId());
  wifi_station_set_hostname(hostname);
  WiFi.hostname(hostname);
  ArduinoOTA.begin();
  WiFiManager wifiManager;
  wifiManager.autoConnect(hostname);
  MDNS.begin(hostname);
  MDNS.addService("pewpew", "tcp", 80);

  // Setup web server
  server.on("/set", [](){
    int r, i;
    String arg;
    if ((arg = server.arg("r")) && arg.length() > 0)
    {
      r = arg.toFloat()*100;
      if ((arg = server.arg("i")) && arg.length() > 0)
      {
        i = arg.toFloat()*100;
        hardware.setPosition(r, i);
      }
    }
    if ((arg = server.arg("p")) && arg.length() > 0) {
      hardware.setPower(arg.toFloat()*255);
    }

    server.send(200, "application/javascript", "{\"result\":\"ok\"}");
  });

  SPIFFS.begin();
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    server.serveStatic(dir.fileName().c_str(), SPIFFS, dir.fileName().c_str());
  }
  server.serveStatic("/", SPIFFS, "/index.html");
  server.begin();
}

long last = 0;
int toggle = 0;

void loop(void)
{
  ArduinoOTA.handle();
  hardware.update();
  server.handleClient();
}
