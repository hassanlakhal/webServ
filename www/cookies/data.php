<?php
ob_start();
session_start();

if (isset($_COOKIE["name"])) {
    echo "Hi " . $_COOKIE["name"];
} else {
    echo "<meta http-equiv='refresh' content='0; url=login.php'>";
}
?>
