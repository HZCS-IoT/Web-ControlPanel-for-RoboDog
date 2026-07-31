<?php
header('Content-Type: application/json; charset=utf-8');
include "db.php";

$limit = isset($_GET['limit']) ? min(50, max(1, (int) $_GET['limit'])) : 10;

$stmt = $conn->prepare("SELECT id, text, created_at FROM speech_logs ORDER BY id DESC LIMIT ?");
$stmt->bind_param("i", $limit);
$stmt->execute();
$result = $stmt->get_result();

$records = [];
while ($row = $result->fetch_assoc()) {
    $records[] = $row;
}

echo json_encode(["status" => "success", "records" => $records]);

$stmt->close();
$conn->close();
