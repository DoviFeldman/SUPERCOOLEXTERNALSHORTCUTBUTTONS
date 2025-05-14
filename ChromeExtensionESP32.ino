#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "HOMEWIFI"; // Replace with your WiFi SSID
const char* password = "CHOCOLATESANDCOOKIES"; // Replace with your WiFi password

WebServer server(80);

int buttonPressed = 0;
bool prevTouch0 = false;
bool prevTouch1 = false;

void handleStatus() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(buttonPressed));
  buttonPressed = 0;
}

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  server.on("/status", handleStatus);
  server.begin();
}

void loop() {
  bool currentTouch0 = touchRead(T5) < 40; // Adjust threshold as needed
  bool currentTouch1 = touchRead(T9) < 40; // Adjust threshold as needed
  if (!prevTouch0 && currentTouch0) {
    buttonPressed = 1;
  }
  if (!prevTouch1 && currentTouch1) {
    buttonPressed = 2;
  }
  prevTouch0 = currentTouch0;
  prevTouch1 = currentTouch1;
  server.handleClient();
}
