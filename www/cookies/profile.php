<?php
if (!isset($_COOKIE["name"]) || !isset($_COOKIE["email"]) || isset($_POST["logout"])) {
    setcookie("name", "", time() - 3600, "/");
    setcookie("email", "", time() - 3600, "/");
    setcookie("profile", "", time() - 3600, "/");
    echo "<meta http-equiv='refresh' content='0; url=login.php'>";
    exit(0);
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Profile</title>
</head>
<body>
  <div class="card">
    <div class="card__header">
      <div class="card__name">
        <h2><?php echo $_COOKIE["name"] ?></h2>
        <div class="card__handle">
          <span class="handle"><?php echo $_COOKIE["email"] ?></span>
          <span class="circle"></span>
        </div>
      </div>
      <div class="card__button">
        <form action="" method="post">
            <span>
              <input class="heading score insights" type="submit" name="logout" value="Logout">
            </span>
        </form>
      </div>
    </div>
</body>

</html>
