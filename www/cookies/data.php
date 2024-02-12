<?php
ob_start();
session_start();

if (isset($_COOKIE["username"])) {
    echo "Hi " . $_COOKIE["username"];
} else {
    echo "<meta http-equiv='refresh' content='0; url=login.php'>";
}
?>