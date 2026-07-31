/*
 * Task 1 — ESP32 HTTP Client
 * Smart Methods — Robot Dog
 *
 * Reads latest command from web control panel via get_state.php
 *
 * Setup:
 *   1. Edit WIFI_SSID and WIFI_PASS below
 *   2. Board: ESP32 Dev Module
 *   3. Upload and open Serial Monitor @ 115200
 *   4. Change command from manual.html or voice.html
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// ===== عدّل هنا =====
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* SERVER_URL = "https://webtask1.free.je/h/get_state.php";
// ====================

const unsigned long POLL_MS = 2000;

WiFiClientSecure secureClient;
String lastCommand = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("=== Robot Dog — Task 1 ESP32 ===");

  connectWiFi();

  secureClient.setInsecure();  // HTTPS for InfinityFree (testing)

  Serial.println("Polling: " + String(SERVER_URL));
  Serial.println("Open control panel and send a command...");
  Serial.println();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  static unsigned long lastPoll = 0;
  if (millis() - lastPoll >= POLL_MS) {
    lastPoll = millis();
    fetchCommand();
  }
}

void connectWiFi() {
  Serial.print("Connecting WiFi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 30) {
    delay(500);
    Serial.print(".");
    tries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi OK!");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi FAILED — check SSID/password");
  }
}

void fetchCommand() {
  HTTPClient http;

  if (!http.begin(secureClient, SERVER_URL)) {
    Serial.println("HTTP begin failed");
    return;
  }

  http.setTimeout(10000);
  int code = http.GET();

  if (code <= 0) {
    Serial.printf("HTTP error: %s\n", http.errorToString(code).c_str());
    http.end();
    return;
  }

  String body = http.getString();
  http.end();

  String cmd = parseCommand(body);

  if (cmd.length() == 0) {
    Serial.println("Could not parse: " + body);
    return;
  }

  if (cmd != lastCommand) {
    lastCommand = cmd;
    Serial.println(">>> NEW COMMAND: " + cmd + " (" + commandLabel(cmd) + ")");
  }
}

String parseCommand(String json) {
  int key = json.indexOf("\"command\"");
  if (key < 0) return "";

  int q1 = json.indexOf('"', json.indexOf(':', key) + 1);
  int q2 = json.indexOf('"', q1 + 1);

  if (q1 < 0 || q2 < 0) return "";

  return json.substring(q1 + 1, q2);
}

String commandLabel(String c) {
  if (c == "f") return "forward";
  if (c == "b") return "backward";
  if (c == "l") return "left";
  if (c == "r") return "right";
  if (c == "S") return "stop";
  if (c == "j") return "sit";
  return "unknown";
}
