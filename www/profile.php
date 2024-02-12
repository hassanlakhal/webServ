<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>User Profile</title>
    <link rel="stylesheet" href="styles.css">
	<style>
	.container {
    max-width: 600px;
    margin: 0 auto;
    padding: 20px;
    border: 1px solid #ccc;
    border-radius: 5px;
	}

	.profile-info {
		margin-bottom: 20px;
	}

	.profile-info h2 {
		margin-bottom: 10px;
	}

	.profile-info p {
		margin-bottom: 5px;
	}

	</style>
</head>
<body>
    <div class="container">
        
		<?php
		session_start();
		// Check if the form is submitted
		if ($_SERVER["REQUEST_METHOD"] == "POST") {
			// Retrieve form data
			$name = $_POST["name"];
			$email = $_POST["email"];
			$bio = $_POST["bio"];
			$skills = explode(",", $_POST["skills"]);

			// Store profile information in session variables
			$_SESSION["profile"] = [
				'name' => $name,
				'email' => $email,
				'bio' => $bio,
				'skills' => $skills
			];
		} 

		// Check if profile information exists in session
		if (isset($_SESSION["profile"])) {
			$profile = $_SESSION["profile"];
			echo '<h1>User Profile</h1>';
			echo "<p><strong>Name:</strong> {$profile['name']}</p>";
			echo "<p><strong>Email:</strong> {$profile['email']}</p>";
			echo "<p><strong>Bio:</strong> {$profile['bio']}</p>";
			echo "<p><strong>Skills:</strong></p>";
			echo "<ul>";
			foreach ($profile['skills'] as $skill) {
				echo "<li>$skill</li>";
			}
			echo "</ul>";
		} else 
		{
			include 'index.html';
		}
		?>
	</div>

    </div>
</body>
</html>

