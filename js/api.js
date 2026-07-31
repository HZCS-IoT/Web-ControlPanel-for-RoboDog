async function sendRobotCommand(command) {
  const response = await fetch('update_command.php', {
    method: 'POST',
    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
    body: 'command=' + encodeURIComponent(command),
  });

  const data = await response.json();

  if (!response.ok || data.status !== 'success') {
    throw new Error(data.message || 'فشل إرسال الأمر');
  }

  return data;
}

async function saveSpeechText(text) {
  const response = await fetch('save_speech.php', {
    method: 'POST',
    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
    body: 'text=' + encodeURIComponent(text),
  });

  const data = await response.json();

  if (!response.ok || data.status !== 'success') {
    throw new Error(data.message || 'فشل حفظ النص');
  }

  return data;
}

function setStatus(element, text, type) {
  element.textContent = text;
  element.className = 'status' + (type ? ' ' + type : '');
}
