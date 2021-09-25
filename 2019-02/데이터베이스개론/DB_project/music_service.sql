-- phpMyAdmin SQL Dump
-- version 4.9.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- 생성 시간: 19-11-30 02:52
-- 서버 버전: 10.4.8-MariaDB
-- PHP 버전: 7.3.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 데이터베이스: `musicservice`
--
CREATE DATABASE IF NOT EXISTS `musicservice` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `musicservice`;

-- --------------------------------------------------------

--
-- 테이블 구조 `album`
--

CREATE TABLE `album` (
  `a_id` int(11) NOT NULL,
  `a_title` varchar(30) NOT NULL,
  `artist_id` int(11) NOT NULL,
  `r_date` date NOT NULL,
  `genre` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 테이블의 덤프 데이터 `album`
--

INSERT INTO `album` (`a_id`, `a_title`, `artist_id`, `r_date`, `genre`) VALUES
(1, 'speak your mind', 1, '2018-04-27', 'pop'),
(2, 'everyday life', 2, '2019-11-20', 'rock'),
(3, 'a head full of dreams', 2, '2015-12-04', 'rock'),
(4, 'time', 3, '2019-07-12', 'hip-hop'),
(5, '21', 4, '2011-01-21', 'r&b'),
(6, 'when we were young', 4, '2016-02-05', 'r&b'),
(7, 'different world', 5, '2018-12-14', 'electronica');

-- --------------------------------------------------------

--
-- 테이블 구조 `artist`
--

CREATE TABLE `artist` (
  `artist_id` int(11) NOT NULL,
  `artist_name` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 테이블의 덤프 데이터 `artist`
--

INSERT INTO `artist` (`artist_id`, `artist_name`) VALUES
(1, 'anne-marie'),
(2, 'coldplay'),
(3, 'nf'),
(4, 'adele'),
(5, 'alan walker');

-- --------------------------------------------------------

--
-- 테이블 구조 `download_list`
--

CREATE TABLE `download_list` (
  `u_id` varchar(15) NOT NULL,
  `m_id` int(11) NOT NULL,
  `down_order` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 테이블 구조 `like_list`
--

CREATE TABLE `like_list` (
  `u_id` varchar(15) NOT NULL,
  `m_id` int(11) NOT NULL,
  `like_order` int(11) NOT NULL,
  `count` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 테이블 구조 `membership`
--

CREATE TABLE `membership` (
  `u_id` varchar(15) NOT NULL,
  `card` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 테이블 구조 `music`
--

CREATE TABLE `music` (
  `m_id` int(11) NOT NULL,
  `a_id` int(11) NOT NULL,
  `m_title` varchar(30) NOT NULL,
  `composer` varchar(30) NOT NULL,
  `m_order` int(11) NOT NULL,
  `lyricist` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 테이블의 덤프 데이터 `music`
--

INSERT INTO `music` (`m_id`, `a_id`, `m_title`, `composer`, `m_order`, `lyricist`) VALUES
(1, 1, '2002', 'ed sheeran', 1, 'ed sheeran'),
(2, 1, 'ciao adios', 'anne-marie', 2, 'anne-marie'),
(3, 2, 'daddy', 'coldplay', 1, 'coldplay'),
(4, 3, 'everglow', 'coldplay', 1, 'coldplay'),
(5, 4, 'time', 'nf', 1, 'nf'),
(6, 5, 'someone like you', 'adele', 1, 'adele'),
(7, 6, 'when we were young', 'adele', 1, 'adele'),
(8, 7, 'lost control', 'alan walker', 1, 'alanwalker'),
(9, 7, 'lily', 'alan walker', 2, 'alanwalker'),
(10, 7, 'different world', 'alan walker', 3, 'alanwalker');

-- --------------------------------------------------------

--
-- 테이블 구조 `user`
--

CREATE TABLE `user` (
  `u_id` varchar(15) NOT NULL,
  `pw` varchar(15) NOT NULL,
  `email` varchar(30) NOT NULL,
  `gender` varchar(10) NOT NULL,
  `license` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 테이블의 덤프 데이터 `user`
--

INSERT INTO `user` (`u_id`, `pw`, `email`, `gender`, `license`) VALUES
('manager1', 'm1111', 'mgr1@skku.edu', 'female', 'manager'),
('manager2', 'm2222', 'mgr2@skku.edu', 'male', 'manager'),
('user1', 'u1111', 'user1@skku.edu', 'female', 'general'),
('user2', 'u2222', 'user2@skku.edu', 'male', 'general');

--
-- 덤프된 테이블의 인덱스
--

--
-- 테이블의 인덱스 `album`
--
ALTER TABLE `album`
  ADD PRIMARY KEY (`a_id`),
  ADD KEY `artist_id` (`artist_id`);

--
-- 테이블의 인덱스 `artist`
--
ALTER TABLE `artist`
  ADD PRIMARY KEY (`artist_id`);

--
-- 테이블의 인덱스 `download_list`
--
ALTER TABLE `download_list`
  ADD PRIMARY KEY (`u_id`,`m_id`),
  ADD KEY `m_id` (`m_id`);

--
-- 테이블의 인덱스 `like_list`
--
ALTER TABLE `like_list`
  ADD PRIMARY KEY (`u_id`,`m_id`),
  ADD KEY `m_id` (`m_id`);

--
-- 테이블의 인덱스 `membership`
--
ALTER TABLE `membership`
  ADD PRIMARY KEY (`u_id`,`card`);

--
-- 테이블의 인덱스 `music`
--
ALTER TABLE `music`
  ADD PRIMARY KEY (`m_id`),
  ADD KEY `a_id` (`a_id`);

--
-- 테이블의 인덱스 `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`u_id`);

--
-- 덤프된 테이블의 제약사항
--

--
-- 테이블의 제약사항 `album`
--
ALTER TABLE `album`
  ADD CONSTRAINT `album_ibfk_1` FOREIGN KEY (`artist_id`) REFERENCES `artist` (`artist_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 테이블의 제약사항 `download_list`
--
ALTER TABLE `download_list`
  ADD CONSTRAINT `download_list_ibfk_1` FOREIGN KEY (`u_id`) REFERENCES `user` (`u_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `download_list_ibfk_2` FOREIGN KEY (`m_id`) REFERENCES `music` (`m_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 테이블의 제약사항 `like_list`
--
ALTER TABLE `like_list`
  ADD CONSTRAINT `like_list_ibfk_1` FOREIGN KEY (`u_id`) REFERENCES `user` (`u_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `like_list_ibfk_2` FOREIGN KEY (`m_id`) REFERENCES `music` (`m_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 테이블의 제약사항 `membership`
--
ALTER TABLE `membership`
  ADD CONSTRAINT `membership_ibfk_1` FOREIGN KEY (`u_id`) REFERENCES `user` (`u_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 테이블의 제약사항 `music`
--
ALTER TABLE `music`
  ADD CONSTRAINT `music_ibfk_1` FOREIGN KEY (`a_id`) REFERENCES `album` (`a_id`) ON DELETE CASCADE ON UPDATE CASCADE;
