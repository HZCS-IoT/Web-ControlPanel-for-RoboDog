<?php
// انسخ هذا الملف إلى db.php وعدّل بياناتك من InfinityFree
$host = "sqlXXX.infinityfree.com";
$user = "if0_XXXXXXX";
$pass = "YOUR_PASSWORD_HERE";
$dbname = "if0_XXXXXXX_database";

$conn = new mysqli($host, $user, $pass, $dbname);

if ($conn->connect_error) {
    die(json_encode(["status" => "error", "message" => "فشل الاتصال: " . $conn->connect_error]));
}
?>
