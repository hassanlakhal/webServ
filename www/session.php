<?php
session_start(); // Start the session

$_SESSION['name'] = "hassan";
isset($_SESSION['views']) ? $_SESSION['views']++ : $_SESSION['views'] = 1;


echo '<h1>Hello in test Session</h1>';

echo "Hello " . $_SESSION['name'] . " Views of the page " . $_SESSION['views'];
echo'<a href="script.php"> test </a>'; 


?>



