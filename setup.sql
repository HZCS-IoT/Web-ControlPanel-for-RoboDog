-- Smart Methods — Robot Dog Control Panel
-- Run once in phpMyAdmin → SQL tab

CREATE TABLE IF NOT EXISTS robot_state (
    id INT PRIMARY KEY,
    command CHAR(1) NOT NULL,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

INSERT INTO robot_state (id, command) VALUES (1, 'S')
ON DUPLICATE KEY UPDATE command = command;

CREATE TABLE IF NOT EXISTS speech_logs (
    id INT AUTO_INCREMENT PRIMARY KEY,
    text TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
