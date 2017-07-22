-- phpMyAdmin SQL Dump
-- version 4.4.14.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: 2017-07-22 17:09:32
-- 服务器版本： 5.6.26
-- PHP Version: 5.5.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `teachingsystem`
--
CREATE DATABASE IF NOT EXISTS `teachingsystem` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `teachingsystem`;

-- --------------------------------------------------------

--
-- 表的结构 `course`
--

DROP TABLE IF EXISTS `course`;
CREATE TABLE IF NOT EXISTS `course` (
  `cID` varchar(11) NOT NULL,
  `cname` varchar(16) NOT NULL,
  `tID` varchar(11) NOT NULL,
  `startterm` int(1) NOT NULL,
  `classtime1` varchar(7) NOT NULL,
  `classroom1` varchar(5) NOT NULL,
  `classtime2` varchar(7) NOT NULL,
  `classroom2` varchar(5) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `course`
--

INSERT INTO `course` (`cID`, `cname`, `tID`, `startterm`, `classtime1`, `classroom1`, `classtime2`, `classroom2`) VALUES
('C01', '数据库系统', 'T0402', 1, '2/1-2', '2-300', '4/3-4', '2-301'),
('C02', '大型数据库技术', 'T0401', 1, '1/1-2', '3-300', '4/3-4', '3-301'),
('C03', '高数', 'T0401', 1, '1/1-2', '3-400', '4/3-4', '2-301'),
('C04', '数据结构', 'T0402', 1, '1/3-4', '2-201', '5/1-2', '2-300');

-- --------------------------------------------------------

--
-- 表的结构 `manager`
--

DROP TABLE IF EXISTS `manager`;
CREATE TABLE IF NOT EXISTS `manager` (
  `mID` varchar(11) NOT NULL,
  `mpassword` varchar(16) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `manager`
--

INSERT INTO `manager` (`mID`, `mpassword`) VALUES
('admin', '123');

-- --------------------------------------------------------

--
-- 表的结构 `presc`
--

DROP TABLE IF EXISTS `presc`;
CREATE TABLE IF NOT EXISTS `presc` (
  `cID` varchar(11) NOT NULL,
  `sID` varchar(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `presc`
--

INSERT INTO `presc` (`cID`, `sID`) VALUES
('C01', 'B4040905'),
('C01', 'B4040906'),
('C01', 'B4040907'),
('C02', 'B4040905'),
('C02', 'B4040906'),
('C02', 'B4040907');

-- --------------------------------------------------------

--
-- 表的结构 `selectcourse`
--

DROP TABLE IF EXISTS `selectcourse`;
CREATE TABLE IF NOT EXISTS `selectcourse` (
  `cID` varchar(11) NOT NULL,
  `sID` varchar(11) NOT NULL,
  `score` int(3) DEFAULT NULL,
  `grade` int(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `selectcourse`
--

INSERT INTO `selectcourse` (`cID`, `sID`, `score`, `grade`) VALUES
('C03', 'B4040905', 88, 1),
('C04', 'B4040905', 90, 2),
('C02', 'B4040905', 90, 3),
('C01', 'B4040905', NULL, 3);

-- --------------------------------------------------------

--
-- 表的结构 `start`
--

DROP TABLE IF EXISTS `start`;
CREATE TABLE IF NOT EXISTS `start` (
  `name` varchar(11) NOT NULL,
  `value` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `start`
--

INSERT INTO `start` (`name`, `value`) VALUES
('开始选课', 0);

-- --------------------------------------------------------

--
-- 表的结构 `state`
--

DROP TABLE IF EXISTS `state`;
CREATE TABLE IF NOT EXISTS `state` (
  `value` int(1) DEFAULT NULL,
  `name` varchar(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `state`
--

INSERT INTO `state` (`value`, `name`) VALUES
(1, '学期');

-- --------------------------------------------------------

--
-- 表的结构 `student`
--

DROP TABLE IF EXISTS `student`;
CREATE TABLE IF NOT EXISTS `student` (
  `sID` varchar(11) NOT NULL,
  `sname` varchar(16) NOT NULL,
  `spassword` varchar(16) NOT NULL,
  `grade` int(1) NOT NULL,
  `sex` varchar(2) NOT NULL,
  `institute` enum('计算机学院','管理学院','通信学院','自动化学院') NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `student`
--

INSERT INTO `student` (`sID`, `sname`, `spassword`, `grade`, `sex`, `institute`) VALUES
('B4040905', '胥艳', '199511', 3, '女', '计算机学院'),
('B4040907', '栾颖', '123456', 3, '女', '计算机学院'),
('B4040906', '钱程', '123456', 3, '女', '计算机学院');

-- --------------------------------------------------------

--
-- 表的结构 `teacher`
--

DROP TABLE IF EXISTS `teacher`;
CREATE TABLE IF NOT EXISTS `teacher` (
  `tID` varchar(11) NOT NULL,
  `tname` varchar(16) NOT NULL,
  `tpassword` varchar(16) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `teacher`
--

INSERT INTO `teacher` (`tID`, `tname`, `tpassword`) VALUES
('T0401', '王传栋', '123');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `course`
--
ALTER TABLE `course`
  ADD PRIMARY KEY (`cID`),
  ADD KEY `tID` (`tID`);

--
-- Indexes for table `manager`
--
ALTER TABLE `manager`
  ADD PRIMARY KEY (`mID`);

--
-- Indexes for table `presc`
--
ALTER TABLE `presc`
  ADD PRIMARY KEY (`cID`,`sID`);

--
-- Indexes for table `selectcourse`
--
ALTER TABLE `selectcourse`
  ADD PRIMARY KEY (`cID`,`sID`);

--
-- Indexes for table `student`
--
ALTER TABLE `student`
  ADD PRIMARY KEY (`sID`);

--
-- Indexes for table `teacher`
--
ALTER TABLE `teacher`
  ADD PRIMARY KEY (`tID`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
