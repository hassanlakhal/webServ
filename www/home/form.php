<?php
// Check if the request method is POST
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the form data from the request body
    $formData = file_get_contents("php://input");
    
    // Parse the x-www-form-urlencoded data
    parse_str($formData, $decodedData);

    // Set the content type
    header('Content-Type: text/html; charset=UTF-8');

    // Display the form data
    echo "<h2>Form Data:</h2>";
    foreach ($decodedData as $key => $value) {
        echo "<p><strong>$key:</strong> $value</p>";
    }
} else {
    echo "<p>No form data submitted.</p>";
}
?>

