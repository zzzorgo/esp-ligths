#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "constants.h"
#include "rainbow.h"
#include "smartLogger.h"
#include "serverSetup.h"
#include "secrets.h"

Adafruit_NeoPixel strip(COUNT, 19, NEO_RGB + NEO_KHZ800);

// void getAddressMapping() {
//   for (int i = 0; i < COUNT; i++)
//   {
//     /* code */
//   }
// }
std::vector<OtaCommand> commands;
const int A_LETTER[14][2] = {
    {0, 1},
    {0, 2},
    {1, 0},
    {1, 3},
    {2, 0},
    {2, 3},
    {3, 0},
    {3, 1},
    {3, 2},
    {3, 3},
    {4, 0},
    {4, 3},
    {5, 0},
    {5, 3},
};

struct EffectFrame
{
  int delay;
  int data[COUNT * 3];
};

EffectFrame effect[10];

bool play = false;

void test()
{
  delay(1000);
  for (size_t i = 0; i < 255; i += 18)
  {
    for (size_t j = 0; j < COUNT; j += 1)
    {
      strip.setPixelColor(j, strip.ColorHSV(0, 255, i));
    }
    strip.show();
    delay(10);
  }

  delay(1000);

  for (size_t i = 0; i < 255; i += 18)
  {
    for (size_t j = 0; j < COUNT; j += 1)
    {
      strip.setPixelColor(j, strip.ColorHSV(20000, 255, i));
    }
    strip.show();
    delay(10);
  }

  delay(1000);

  for (size_t i = 0; i < 255; i += 18)
  {
    for (size_t j = 0; j < COUNT; j += 1)
    {
      strip.setPixelColor(j, strip.ColorHSV(40000, 255, i));
    }
    strip.show();
    delay(10);
  }

  // delay(1000);

  // for (size_t j = 0; j < COUNT; j+=1) {
  //     strip.setPixelColor(j, strip.ColorHSV(0, 255, 0));
  // }
  // strip.show();
}

void testWhite(int brightness)
{
  delay(1000);

  for (size_t j = 0; j < COUNT; j += 1)
  {
    // if (j == ADDRESSES[1][4]) {
    //   strip.setPixelColor(j, brightness - 30, brightness, brightness - 30);
    // } else {
    strip.setPixelColor(j, brightness, brightness, brightness);
    // }
  }

  strip.show();
}

void showA()
{
  for (int i = 0; i < 14; i++)
  {
    const int *pixel = A_LETTER[i];
    int address = ADDRESSES[pixel[0]][pixel[1]];

    strip.setPixelColor(address, strip.ColorHSV(0, 255, 255));
  }

  strip.show();
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(20);
  strip.clear();

  for (int i = 0; i < COUNT; i++)
  {
    strip.setPixelColor(i, strip.ColorHSV(0, 255, 255));
  }

  strip.show();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    smartLog("[Wifi] Connecting...");
  }

  smartLog("[Wifi] Connected! %s", WiFi.localIP().toString().c_str());

  commands.push_back({.key = "update",
                      .callback = [](int offset, unsigned char *data)
                      {
                        // smartLog("update\n");
                        for (int i = offset + 1; i < offset + (COUNT * 3); i += 3)
                        {
                          strip.setPixelColor((i - offset - 1) / 3, data[i], data[i + 1], data[i + 2]);
                        }

                        strip.show();
                      }});

  commands.push_back({.key = "json",
                      .callback = [](int offset, unsigned char *data)
                      {
                        JsonDocument doc;
                        deserializeJson(doc, &data[offset]);
                        JsonArray frames = doc.as<JsonArray>();

                        int i = 0;
                        for (JsonObject frame : frames)
                        {
                          EffectFrame effectFrame;

                          effectFrame.delay = frame["delay"].as<int>();
                          JsonArray frameData = frame["data"].as<JsonArray>();

                          int j = 0;
                          for (JsonVariant num : frameData)
                          {
                            effectFrame.data[j] = num.as<int>();
                            j++;
                          }

                          effect[i] = effectFrame;
                          i++;
                        }

                        play = true;
                      }});
  commands.push_back({.key = "brightness",
                      .callback = [](int offset, unsigned char *data)
                      {
                        int brightness = data[offset + 1];
                        strip.setBrightness(brightness);
                        strip.show();
                      }});

  setupServer(commands);

  for (int i = 0; i < COUNT; i++)
  {
    strip.setPixelColor(i, strip.ColorHSV(14000, 255, 255));
  }

  strip.show();
}

void off()
{
  strip.clear();
  strip.show();
  delay(1000);
}

void loop()
{
  if (play) {
    for (size_t i = 0; i < 2; i++)
    {
      for (size_t j = 0; j < COUNT * 3; j += 3)
      {
        strip.setPixelColor(j / 3, effect[i].data[j], effect[i].data[j + 1], effect[i].data[j + 2]);
      }

      strip.show();

      delay(effect[i].delay);
    }
  }
  // rainbow(&strip);
  // delay(1000);
  // off();
  // delay(1000);
  // test();
  // testWhite(255);
}
