/*
 * Task 1 — ESP32 HTTP Client
 * Smart Methods — Robot Dog
 *
 * IMPORTANT: InfinityFree blocks ESP32 with JavaScript challenge.
 * For ESP32 testing use LOCAL mode (see WIFI_MODE below).
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// ===== WiFi =====
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";

// ===== MODE =====
// 0 = LOCAL (XAMPP on same WiFi) — recommended for ESP32
// 1 = ONLINE (InfinityFree) — usually blocked for ESP32
#define WIFI_MODE 0

#if WIFI_MODE == 0
  // IP جهازك اللي فيه XAMPP — غيّر الرقم
  const char* SERVER_URL = "http://192.168.1.100/h/get_state.php";
#else
  const char* SERVER_URL = "https://webtask1.free.je/h/get_state.php";
#endif

const unsigned long POLL_MS = 2000;
const unsigned long ERROR_LOG_MS = 10000;

WiFiClientSecure secureClient;
WiFiClient plainClient;
String lastCommand = "";
unsigned long lastErrorLog = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== Robot Dog — Task 1 ESP32 ===");
#if WIFI_MODE == 0
  Serial.println("MODE: LOCAL (XAMPP)");
#else
  Serial.println("MODE: ONLINE (InfinityFree)");
  secureClient.setInsecure();
#endif

  connectWiFi();
  Serial.println("URL: " + String(SERVER_URL));
  Serial.println("Send command from manual.html then watch here...");
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
    Serial.println("\nWiFi OK! IP: " + WiFi.localIP().toString());
  } else {
    Serial.println("\nWiFi FAILED");
  }
}

void logErrorThrottled(const String& msg) {
  if (millis() - lastErrorLog >= ERROR_LOG_MS) {
    lastErrorLog = millis();
    Serial.println(msg);
  }
}

void fetchCommand() {
  HTTPClient http;

#if WIFI_MODE == 0
  http.begin(plainClient, SERVER_URL);
#else
  if (!http.begin(secureClient, SERVER_URL)) {
    logErrorThrottled("HTTP begin failed");
    return;
  }
#endif

  http.setTimeout(10000);
  http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 RobotDog Task1)");
  http.addHeader("Accept", "application/json");

  int code = http.GET();

  if (code <= 0) {
    logErrorThrottled("HTTP error: " + http.errorToString(code));
    http.end();
    return;
  }

  String body = http.getString();
  http.end();

  if (body.indexOf("\"command\"") < 0) {
    logErrorThrottled("Not JSON (InfinityFree blocks ESP32). Use LOCAL mode + XAMPP.");
    return;
  }

  String cmd = parseCommand(body);
  if (cmd.length() == 0) return;

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
