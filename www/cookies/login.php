<?php
ob_start();
session_start();

if (isset($_COOKIE["name"]) && isset($_COOKIE["email"]) && isset($_COOKIE["profile"])) {
    echo "<meta http-equiv='refresh' content='0; url=profile.php'>";
    exit(0);
}

if (isset($_POST["submit"])) {
    setcookie("name", $_POST["name"], time() + (60 * 60 * 24), "/");
    setcookie("email", $_POST["email"], time() + (60 * 60 * 24), "/");

    // setcookie("profile", "", time() + (60 * 60 * 24), "/");
    echo "<meta http-equiv='refresh' content='0; url=profile.php'>";
    exit(0);

}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Create Account</title>
    <style>
        body {
            font-family: Arial, Helvetica, sans-serif;
            background-color: #f2f2f2;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }

        form {
            max-width: 400px;
            min-width: 400px;
            padding: 20px;
            background-color: #fff;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
            border-radius: 10px;
        }

        label {
            display: block;
            font-weight: bold;
            margin-bottom: 5px;
        }

        input[type="text"],
        input[type="email"],
        input[type="file"] {
            width: 100%;
            padding: 10px;
            margin-bottom: 15px;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
        }

        input[type="submit"] {
            background-color: #3498db;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-weight: bold;
            transition: background-color 0.3s ease;
        }

        input[type="submit"]:hover {
            background-color: #2980b9;
        }
    </style>
</head>
<body>
<form action="" method="POST" >
    <label for="name">Name:</label>
    <input type="text" name="name" ><br><br>
    <label for="email">Email:</label>
    <input type="email" name="email" ><br><br>
    <input type="submit" name="submit" value="Upload">
</form>
</body>
</html>
