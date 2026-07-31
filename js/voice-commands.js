const COMMAND_LABELS = {
  forward: 'للأمام',
  backward: 'للخلف',
  left: 'يسار',
  right: 'يمين',
  stop: 'توقف',
  sit: 'اجلس',
};

const RECOGNITION_LANG = {
  ar: 'ar-SA',
  en: 'en-US',
};

// كلمات إنجليزية تُكتب بالعربي لما اللغة ar-SA (تشوه شائع)
const ARABIC_TRANSCRIPTIONS = {
  'ستوب': 'stop',
  'ستوپ': 'stop',
  'فوروارد': 'forward',
  'فورورد': 'forward',
  'فوروور': 'forward',
  'فور وورد': 'forward',
  'فورورد': 'forward',
  'فرورد': 'forward',
  'فور': 'forward',
  'باكورد': 'backward',
  'باك وورد': 'backward',
  'باك': 'backward',
  'ليفت': 'left',
  'رايت': 'right',
  'سيت': 'sit',
  'سيت داون': 'sit',
};

const VOICE_RULES = [
  {
    command: 'stop',
    keywords: [
      'stop', 'stopped', 'halt', 'stand still',
      'توقف', 'قف', 'وقف', 'توقيف', 'قف بسرعة', 'توقف الان', 'توقف الآن',
      'ستوب', 'ستوپ',
    ],
  },
  {
    command: 'sit',
    keywords: [
      'sit', 'sit down', 'sitting',
      'اجلس', 'اجلسي', 'قعد', 'قاعد', 'انحناء', 'انحني',
    ],
  },
  {
    command: 'forward',
    keywords: [
      'forward', 'forwards', 'go forward',
      'امام', 'الامام', 'للامام', 'للأمام', 'قدام', 'للقدام', 'تقدم', 'روح قدام', 'تحرك للامام',
      'فوروارد', 'فورورد', 'فور', 'فرورد',
    ],
  },
  {
    command: 'backward',
    keywords: [
      'backward', 'back', 'go back',
      'خلف', 'الخلف', 'للخلف', 'ورا', 'لورا', 'تراجع', 'ارجع', 'ارجعي',
      'باكورد', 'باك',
    ],
  },
  {
    command: 'left',
    keywords: [
      'left', 'go left', 'turn left',
      'يسار', 'اليسار', 'لليسار', 'ليفت',
    ],
  },
  {
    command: 'right',
    keywords: [
      'right', 'go right', 'turn right',
      'يمين', 'اليمين', 'لليمين', 'رايت',
    ],
  },
];

function normalizeSpeech(text) {
  return text
    .trim()
    .toLowerCase()
    .replace(/[ًٌٍَُِّْ]/g, '')
    .replace(/[^\u0600-\u06FFa-z0-9\s]/gi, ' ')
    .replace(/\s+/g, ' ');
}

function applyTransliterations(text) {
  let result = text;

  const sorted = Object.entries(ARABIC_TRANSCRIPTIONS).sort(
    (a, b) => b[0].length - a[0].length
  );

  for (const [arabic, english] of sorted) {
    const key = normalizeSpeech(arabic);
    if (key && result.indexOf(key) !== -1) {
      result = result.split(key).join(english);
    }
  }

  return result;
}

function parseVoiceCommand(text) {
  const normalized = applyTransliterations(normalizeSpeech(text));

  for (const rule of VOICE_RULES) {
    for (const keyword of rule.keywords) {
      const key = normalizeSpeech(keyword);
      if (key && normalized.includes(key)) {
        return rule.command;
      }
    }
  }

  return null;
}

function getCommandLabel(command) {
  return COMMAND_LABELS[command] || command;
}

function getRecognitionLang(mode) {
  return RECOGNITION_LANG[mode] || RECOGNITION_LANG.ar;
}

function getLangHint(mode) {
  if (mode === 'en') {
    return 'وضع إنجليزي: قل forward, backward, left, right, stop, sit';
  }
  return 'وضع عربي: قل للأمام، للخلف، يسار، يمين، قف، اجلس';
}
