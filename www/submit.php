<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Submitted Data</title>
</head>
<body>
    <h2>Submitted Data</h2>
    <?php
    if ($_SERVER["REQUEST_METHOD"] == "GET") {
        $name = $_GET['name'];
        $email = $_GET['email'];
        echo "<p>Name: $name</p>";
        echo "<p>Email: $email</p>";
    } else {
        echo "<p>No data submitted.</p>";
    }
    ?>
</body>
</html>
