<?php
$bgColor = isset($_COOKIE["background"]) ? $_COOKIE["background"] : "#ffffff";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $bgColor = isset($_POST["bg-color"]) ? $_POST["bg-color"] : "#ffffff"; // Default color if not set
    // Sanitize and validate $bgColor here if needed
    setcookie("background", $bgColor);
    // Redirect after setting the cookie to prevent form resubmission
    header("Location: " . $_SERVER["PHP_SELF"]);
    exit();
}
?>

<style>
    body { background-color: <?php echo $bgColor; ?>; }
</style>

<form action="bg.php" method="POST">
    <label for="bg-color">Choose Background Color:</label>
    <input type="color" id="bg-color" name="bg-color" value="<?php echo $bgColor; ?>">
    <input type="submit" value="Choose Color">
</form>


