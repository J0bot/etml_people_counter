#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "utility/wifi_drv.h"
#include "secrets.h"

// mac address : f0:08:d1:cf:17:70


const int DETECTION_TIMEOUT = 1000;
String savedDirection = "";
String detectedDirection = "";
int startedTimeout = 0;
bool detectedRecord = false;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASSWORD;
char serverId[] = SECRET_URL;

/** Setup Pins **/
const byte PIN_ENTRY_CAPTOR = 7;
const byte PIN_EXIT_CAPTOR = 6;
const byte PIN_ENTRY_LED = 0;
const byte PIN_EXIT_LED = 1;


int status = WL_IDLE_STATUS;
WiFiClient wifi;
HttpClient client(wifi, serverId, 80);

void setup() {
  /*** Setup RGB led ***/
  WiFiDrv::pinMode(25, OUTPUT);
  WiFiDrv::pinMode(26, OUTPUT);
  WiFiDrv::pinMode(27, OUTPUT);
                                
  pinMode(PIN_ENTRY_CAPTOR, INPUT);
  pinMode(PIN_EXIT_CAPTOR, INPUT);
  pinMode(PIN_ENTRY_LED, OUTPUT);
  pinMode(PIN_EXIT_LED, OUTPUT);

  /*** No WiFi module ***/
  if (WiFi.status() == WL_NO_MODULE) {
    //Red led
    RGB(255, 0, 0);
    while (true);
  }

  /*** WiFi not connected ***/
  while (status != WL_CONNECTED) {
    //Orange Led
    RGB(255, 165, 0);

    status = WiFi.begin(ssid, pass);
    delay(1000);
  }

  /*** WiFi connected ***/
  RGB(0, 255, 0);
}

void loop() {

  /** Wait for captor to reinitialize before detect again **/
  if (detectedRecord) {
    if(digitalRead(PIN_ENTRY_CAPTOR) == LOW && digitalRead(PIN_EXIT_CAPTOR) == LOW) {
      resetVariables();
    } else {
      delay(200);
      return;
    }
  }

  /** Send record data **/
  if (savedDirection == "exit") {
    if (millis() - startedTimeout < DETECTION_TIMEOUT) {
      if (digitalRead(PIN_ENTRY_CAPTOR) == HIGH) {
        digitalWrite(PIN_EXIT_LED, HIGH);
        delay(200);
        digitalWrite(PIN_EXIT_LED, LOW);
        resetVariables();
        detectedRecord = true;
        sendData("exit");
      }
    } else {
      resetVariables();
    }
  } else if (savedDirection == "entry") {
    if (millis() - startedTimeout < DETECTION_TIMEOUT) {
      if (digitalRead(PIN_EXIT_CAPTOR) == HIGH) {
        digitalWrite(PIN_ENTRY_LED, HIGH);
        delay(200);
        digitalWrite(PIN_ENTRY_LED, LOW);
        resetVariables();
        detectedRecord = true;
        sendData("entry");
      }
    } else {
      resetVariables();
    }
  }

  /** Save the direction detection **/
  if(detectedDirection == "exit" && savedDirection == "") {
    if (digitalRead(PIN_EXIT_CAPTOR) == LOW) {
      resetVariables();
      savedDirection = "exit";
      startedTimeout = millis();
    }
  } else if (detectedDirection == "entry" && savedDirection == "") {
    if (digitalRead(PIN_ENTRY_CAPTOR) == LOW) {
      resetVariables();
      savedDirection = "entry";
      startedTimeout = millis();
    }
  }

  /** Start the direction detection**/
  if(digitalRead(PIN_EXIT_CAPTOR) == HIGH && digitalRead(PIN_ENTRY_CAPTOR) == LOW) {
    detectedDirection = "exit";
  } else if(digitalRead(PIN_ENTRY_CAPTOR) == HIGH && digitalRead(PIN_EXIT_CAPTOR) == LOW) {
    detectedDirection = "entry"; 
  }
}

void RGB(int r, int g, int b) {
  WiFiDrv::analogWrite(25, g);
  WiFiDrv::analogWrite(26, r);
  WiFiDrv::analogWrite(27, b);
}

void resetVariables() {
  savedDirection = "";
  detectedDirection = "";
  startedTimeout = 0;
  detectedRecord = false;
}

String getMacAddress() {
  byte mac[6];
  WiFi.macAddress(mac);
  String cMac = "";
  for (int i = 0; i < 6; ++i) {
    if (String(mac[i],HEX).length() < 2)
      {
        cMac += 0;
      }
    cMac += String(mac[i],HEX);
  }
  cMac.toUpperCase();
  return cMac;
}

void sendData(String recType) {
  const String contentType = "application/x-www-form-urlencoded";
  String body = "ardMacAddress=" + getMacAddress() + "&recType=" + recType;
  if (client.connect(serverId, 80)){
    client.post("/ProjetPreTPI/api/addrecord", contentType, body);
    client.stop();
  }
  exit;
}
