<?php
// date_default_timezone_set('Asia/Jakarta');
$conn = mysqli_connect('localhost', 'siagabanjir', 'WebsiteAndroid2022', 'u665944158_siagabanjir');
$date = date('d-m-Y h:i:s');
$q = mysqli_query($conn, "INSERT INTO level (value1, value2) VALUES ('2', 'asd')");
