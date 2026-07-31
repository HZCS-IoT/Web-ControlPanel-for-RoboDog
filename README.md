<div align="center">

# 🐕 Web Control Panel for RoboDog

**لوحة تحكم ويب للكلب الروبوتي — Smart Methods Task 2**

[![Voice Demo](https://img.shields.io/badge/Voice_Control-voice.html-22d3ee?style=for-the-badge)](https://webtask1.free.je/h/voice.html)
[![Manual Demo](https://img.shields.io/badge/Manual_Control-manual.html-a78bfa?style=for-the-badge)](https://webtask1.free.je/h/manual.html)
[![Demo Video](https://img.shields.io/badge/Demo_Video-YouTube-ff0000?style=for-the-badge&logo=youtube&logoColor=white)](https://youtu.be/-kLJGbAwb0M)
[![PHP](https://img.shields.io/badge/PHP-777BB4?style=for-the-badge&logo=php&logoColor=white)](https://php.net)
[![MySQL](https://img.shields.io/badge/MySQL-4479A1?style=for-the-badge&logo=mysql&logoColor=white)](https://mysql.com)

*تحكم يدوي + تحكم صوتي · Speech to Text · MySQL*

**HZCS-IoT** · Smart Methods — Web & Applications Track

</div>

---

## 🎬 Live Demo | جرّب الآن

| | الرابط |
|---|--------|
| 🏠 **Home** | **[https://webtask1.free.je/h/](https://webtask1.free.je/h/)** |
| 🎤 **Voice Control** | **[https://webtask1.free.je/h/voice.html](https://webtask1.free.je/h/voice.html)** |
| 🎮 **Manual Control** | **[https://webtask1.free.je/h/manual.html](https://webtask1.free.je/h/manual.html)** |
| 📹 **Demo Video** | **[YouTube — اختبار يدوي + صوتي](https://youtu.be/-kLJGbAwb0M)** |

> ⚠️ الدومين جديد — قد يستغرق DNS حتى **72 ساعة** ليعمل عند الجميع.

---

## ✨ Features | المميزات

- 🎮 **Manual control pad** — forward, backward, left, right, stop, sit
- 🎤 **Voice control** — Speech to Text with Arabic / English modes
- 💾 **Database storage** — commands → `robot_state` · speech → `speech_logs`
- 🌙 **Modern UI** — dark theme, responsive design
- 🔐 **Secure config** — `db.example.php` template (passwords not in Git)

---

## 🗺️ System Flow

```
┌──────────────────────────────────────────┐
│           🌐 Browser                     │
│     manual.html  ·  voice.html           │
└──────────────────┬───────────────────────┘
                   │ POST
                   ▼
┌──────────────────────────────────────────┐
│         ⚙️ PHP Backend                   │
│  update_command.php · save_speech.php    │
└──────────────────┬───────────────────────┘
                   │
                   ▼
┌──────────────────────────────────────────┐
│         🗄️ MySQL                         │
│  robot_state · speech_logs               │
└──────────────────────────────────────────┘
```

---

## 🕹️ Commands | الأوامر

| Action | Voice 🇸🇦 | Voice 🇬🇧 | DB |
|--------|-----------|-----------|-----|
| ↑ Forward | للأمام / قدام | forward | `f` |
| ↓ Backward | للخلف / ورا | backward | `b` |
| ← Left | يسار | left | `l` |
| → Right | يمين | right | `r` |
| ■ Stop | قف / توقف | stop | `S` |
| 🐕 Sit | اجلس / انحناء | sit | `j` |

> 💡 **Voice tip:** Choose **🇸🇦 عربي** for Arabic commands — **🇬🇧 English** for forward/backward.

---

## 📁 Project Structure

```
Web-ControlPanel-for-RoboDog/
├── manual.html             ← Manual control pad
├── voice.html              ← Voice control (Speech to Text)
├── index.html              ← Home — choose manual or voice
├── css/style.css
├── js/api.js
├── update_command.php      ← Save robot command
├── save_speech.php         ← Save speech text
├── get_speech.php          ← Speech history
├── get_state.php           ← Read latest command (API)
├── setup.sql
├── db.example.php          ← Copy to db.php
└── README.md
```

---

## 🚀 Quick Start

### 1️⃣ Database

Run `setup.sql` in **phpMyAdmin** on InfinityFree.

### 2️⃣ Configure

```bash
cp db.example.php db.php
```

Edit `db.php` with your InfinityFree credentials.

> 🔒 **Never commit `db.php`** — it's in `.gitignore`

### 3️⃣ Upload to `htdocs/h/`

Upload all files via File Manager or FTP.

### 4️⃣ Test

| Page | Test | Expected |
|------|------|----------|
| `manual.html` | Click forward | `robot_state.command = f` |
| `voice.html` | Say "قف" | Text saved + command updated |

---

## 🛠️ Tech Stack

| Layer | Technology |
|-------|------------|
| Frontend | HTML5 · CSS3 · JavaScript |
| Backend | PHP |
| Database | MySQL |
| Speech | Web Speech API |
| Hosting | InfinityFree |

---

## 🌐 Browser Requirements

| | |
|---|---|
| Browser | **Chrome** or **Edge** |
| Microphone | Permission required for voice |
| Internet | Required for Speech API |

---

## 👥 Team

<div align="center">

**[HZCS-IoT](https://github.com/HZCS-IoT)**

Smart Methods · Internship · Web & Applications Track

</div>

---

<div align="center">

📹 **[Watch Demo on YouTube](https://youtu.be/-kLJGbAwb0M)**

🎤 **[Voice Control](https://webtask1.free.je/h/voice.html)** · 🎮 **[Manual Control](https://webtask1.free.je/h/manual.html)** · 🏠 **[Home](https://webtask1.free.je/h/)**

*Educational project — Smart Methods training program*

</div>
