-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 17, 2022 at 02:02 PM
-- Server version: 10.5.13-MariaDB-cll-lve
-- PHP Version: 7.2.34

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `u665944158_siagabanjir`
--

-- --------------------------------------------------------

--
-- Table structure for table `curah`
--

CREATE TABLE `curah` (
  `id` int(6) UNSIGNED NOT NULL,
  `value1` varchar(10) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `Parameter_Hujan` varchar(30) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `reading_time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `curah`
--

INSERT INTO `curah` (`id`, `value1`, `Parameter_Hujan`, `reading_time`) VALUES
(1, '50', 'Bahaya', '2022-02-13 04:20:41'),
(2, '20', 'Siaga', '2022-02-13 04:20:41');

-- --------------------------------------------------------

--
-- Table structure for table `laju`
--

CREATE TABLE `laju` (
  `id` int(6) UNSIGNED NOT NULL,
  `reading_time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `WaterFlow1` double NOT NULL,
  `WaterFlow2` double NOT NULL,
  `WaterFlow3` double NOT NULL,
  `WaterFlow4` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `laju`
--

INSERT INTO `laju` (`id`, `reading_time`, `WaterFlow1`, `WaterFlow2`, `WaterFlow3`, `WaterFlow4`) VALUES
(1, '2022-02-13 04:21:11', 0, 0, 0, 0),
(2, '2022-02-13 04:21:11', 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `level`
--

CREATE TABLE `level` (
  `id` int(6) UNSIGNED NOT NULL,
  `value1` varchar(10) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `value2` varchar(10) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `reading_time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `level`
--

INSERT INTO `level` (`id`, `value1`, `value2`, `reading_time`) VALUES
(109, '47', 'Bahaya', '2022-02-12 07:46:11'),
(110, '42', 'Bahaya', '2022-02-12 07:46:12'),
(111, '56', 'Bahaya', '2022-02-12 07:46:12'),
(112, '54', 'Bahaya', '2022-02-12 07:46:15'),
(113, '66', 'Bahaya', '2022-02-12 07:46:15');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `curah`
--
ALTER TABLE `curah`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `laju`
--
ALTER TABLE `laju`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `level`
--
ALTER TABLE `level`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `curah`
--
ALTER TABLE `curah`
  MODIFY `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `laju`
--
ALTER TABLE `laju`
  MODIFY `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `level`
--
ALTER TABLE `level`
  MODIFY `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=114;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
