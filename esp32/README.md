# ESP32 — Task 1

<p align="center">
  <img src="../docs/images/esp32-board.png" alt="ESP32 board" width="360">
</p>

ESP32 يتصل بـ WiFi ويقرأ آخر أمر من `get_state.php` كل ثانيتين.

## Setup

1. Open `task1_http_client/task1_http_client.ino`
2. Set `WIFI_SSID`, `WIFI_PASS`, and `SERVER_URL` (your PC IP + XAMPP)
3. Board: **ESP32 Dev Module** · Baud: **115200**
4. Upload and open Serial Monitor

## Test

1. Start XAMPP (Apache + MySQL)
2. Open `http://YOUR_PC_IP/h/manual.html` from phone (same WiFi)
3. Press **Forward** → Serial shows: `>>> NEW COMMAND: f (forward)`

## Demo Videos

| | Link |
|---|------|
| Voice (laptop) | [youtu.be/Qn9NiOmC40Q](https://youtu.be/Qn9NiOmC40Q) |
| Manual (mobile) | [youtube.com/shorts/7RdiBsMd9t4](https://youtube.com/shorts/7RdiBsMd9t4) |

> InfinityFree blocks ESP32 HTTP requests — use **local XAMPP** for Task 1.
