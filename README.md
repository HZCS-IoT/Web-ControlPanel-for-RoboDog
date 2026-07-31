<div align="center">

# 🐕 Web Control Panel for RoboDog

**لوحة تحكم ويب للكلب الروبوتي — Smart Methods**

[![Live Demo](https://img.shields.io/badge/Live_Demo-webtask1.free.je-22d3ee?style=for-the-badge)](https://webtask1.free.je/h/)
[![Demo Video](https://img.shields.io/badge/Demo_Video-YouTube-ff0000?style=for-the-badge&logo=youtube&logoColor=white)](https://youtu.be/-kLJGbAwb0M)
[![PHP](https://img.shields.io/badge/PHP-777BB4?style=for-the-badge&logo=php&logoColor=white)](https://php.net)
[![MySQL](https://img.shields.io/badge/MySQL-4479A1?style=for-the-badge&logo=mysql&logoColor=white)](https://mysql.com)
[![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)](https://developer.mozilla.org/en-US/docs/Web/HTML)

*تحكم يدوي + تحكم صوتي · Speech to Text · MySQL · ESP32 HTTP GET*

**HZCS-IoT** · Smart Methods — Web & Applications Track

</div>

---

## 🎬 Demo | العرض

<table>
<tr>
<td align="center"><strong>🏠 Home</strong><br><a href="https://webtask1.free.je/h/">webtask1.free.je/h</a></td>
<td align="center"><strong>🎮 Manual</strong><br><a href="https://webtask1.free.je/h/manual.html">manual.html</a></td>
<td align="center"><strong>🎤 Voice</strong><br><a href="https://webtask1.free.je/h/voice.html">voice.html</a></td>
<td align="center"><strong>📹 Video</strong><br><a href="https://youtu.be/-kLJGbAwb0M">YouTube Demo</a></td>
</tr>
</table>

> ⚠️ الدومين جديد — قد يستغرق DNS حتى **72 ساعة** ليعمل عند الجميع.

---

## ✨ Features | المميزات

<table>
<tr>
<td width="50%">

### Task 2 — Web
- 🎮 **Manual pad** — forward, back, left, right, stop, sit
- 🎤 **Voice control** — Speech to Text
- 🇸🇦 / 🇬🇧 Arabic & English modes
- 💾 Saves commands + speech to **MySQL**
- 🌙 Modern dark UI

</td>
<td width="50%">

### Task 1 — ESP32
- 📡 HTTP GET from `get_state.php`
- 🔤 Single-char protocol: `f b l r S j`
- 🔄 Real-time command polling
- 🔗 Ready for Arduino Uno bridge

</td>
</tr>
</table>

---

## 🗺️ System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    🌐 Browser                           │
│         index.html → manual.html / voice.html           │
└────────────────────────┬────────────────────────────────┘
                         │ POST
                         ▼
┌─────────────────────────────────────────────────────────┐
│              ⚙️ PHP Backend                             │
│   update_command.php  ·  save_speech.php                │
└────────────────────────┬────────────────────────────────┘
                         │
                         ▼
┌─────────────────────────────────────────────────────────┐
│              🗄️ MySQL                                   │
│   robot_state (command)  ·  speech_logs (text)          │
└────────────────────────┬────────────────────────────────┘
                         │ GET
                         ▼
┌─────────────────────────────────────────────────────────┐
│              📟 ESP32 → Arduino Uno → 🤖 RoboDog       │
└─────────────────────────────────────────────────────────┘
```

---

## 🕹️ Commands | الأوامر

| Action | Voice 🇸🇦 | Voice 🇬🇧 | DB | ESP32 |
|--------|-----------|-----------|-----|-------|
| ↑ Forward | للأمام / قدام | forward | `f` | ✅ |
| ↓ Backward | للخلف / ورا | backward | `b` | ✅ |
| ← Left | يسار | left | `l` | ✅ |
| → Right | يمين | right | `r` | ✅ |
| ■ Stop | قف / توقف | stop | `S` | ✅ |
| 🐕 Sit | اجلس / انحناء | sit | `j` | ✅ |

> 💡 **Voice tip:** Choose **🇸🇦 عربي** for Arabic — **🇬🇧 English** for forward/backward.

---

## 📁 Project Structure

```
Web-ControlPanel-for-RoboDog/
├── 📄 index.html              ← Choose manual or voice
├── 📄 manual.html             ← Control pad
├── 📄 voice.html              ← Speech to Text
├── 📁 css/style.css
├── 📁 js/api.js
├── ⚙️ update_command.php
├── ⚙️ get_state.php           ← ESP32 reads here
├── ⚙️ save_speech.php
├── ⚙️ get_speech.php
├── 🗄️ setup.sql
├── 🔐 db.example.php          ← Copy to db.php
└── 📖 README.md
```

---

## 🚀 Quick Start

### 1️⃣ Database (InfinityFree)

```sql
-- Run setup.sql in phpMyAdmin
CREATE TABLE robot_state (...);
CREATE TABLE speech_logs (...);
```

### 2️⃣ Configure

```bash
cp db.example.php db.php
# Edit db.php with your InfinityFree credentials
```

```php
$host   = "sqlXXX.infinityfree.com";
$user   = "if0_XXXXXXX";
$pass   = "YOUR_PASSWORD";
$dbname = "if0_XXXXXXX_database";
```

> 🔒 **Never commit `db.php`** — it's in `.gitignore`

### 3️⃣ Upload to `htdocs/h/`

Upload all files via File Manager or FTP.

### 4️⃣ Test

| Check | Expected |
|-------|----------|
| `manual.html` → forward | `robot_state.command = f` |
| `voice.html` → say "قف" | `speech_logs` + command updated |
| `get_state.php` | JSON response |

---

## 📡 ESP32 — Task 1

```http
GET https://webtask1.free.je/h/get_state.php
```

```json
{
  "command": "f",
  "updated_at": "2026-07-31 12:00:00"
}
```

Poll every ~2 seconds → map character → control motors/servos.

---

## 🛠️ Tech Stack

| | |
|---|---|
| Frontend | HTML5 · CSS3 · JavaScript |
| Backend | PHP |
| Database | MySQL |
| Speech | Web Speech API |
| Hosting | InfinityFree |
| Hardware | ESP32 + Arduino Uno |

---

## 🌐 Browser Requirements

| Requirement | Details |
|-------------|---------|
| Browser | **Chrome** or **Edge** |
| Mic | Permission required |
| Network | Internet (Speech API) |
| Protocol | HTTPS |

---

## 👥 Team

<div align="center">

**[HZCS-IoT](https://github.com/HZCS-IoT)**

Smart Methods · Internship · Web & Applications Track

</div>

---

<div align="center">

📹 **[Watch Full Demo on YouTube](https://youtu.be/-kLJGbAwb0M)** · 🌐 **[Try Live Demo](https://webtask1.free.je/h/)**

*Educational project — Smart Methods training program*

</div>
