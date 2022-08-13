<?php

// $conn = mysqli_connect("localhost", "phpmyadmin", "password", "3sensor");

$conn = mysqli_connect("localhost", "root", "", "3sensor");

$result = mysqli_query($conn, "SELECT * FROM sensortiga ORDER BY id DESC");

$result1 = mysqli_query($conn, "SELECT * FROM sensortiga ORDER BY id DESC limit 1");
