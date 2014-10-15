CREATE DATABASE  IF NOT EXISTS `code_metrics` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `code_metrics`;
-- MySQL dump 10.13  Distrib 5.6.19, for osx10.7 (i386)
--
-- Host: 127.0.0.1    Database: code_metrics
-- ------------------------------------------------------
-- Server version	5.6.21

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `code_locations`
--

DROP TABLE IF EXISTS `code_locations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `code_locations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `code_packages_id` int(11) NOT NULL,
  `label` varchar(256) NOT NULL,
  `file_name` varchar(256) NOT NULL,
  `line_number` int(11) NOT NULL,
  `git_commit` varchar(40) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `code_packages_id` (`code_packages_id`,`label`,`file_name`,`line_number`),
  CONSTRAINT `code_locations_ibfk_1` FOREIGN KEY (`code_packages_id`) REFERENCES `code_packages` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `code_packages`
--

DROP TABLE IF EXISTS `code_packages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `code_packages` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL,
  `descr` varchar(256) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `code_tick_timings`
--

DROP TABLE IF EXISTS `code_tick_timings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `code_tick_timings` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `code_locations_id` int(11) NOT NULL,
  `created` datetime NOT NULL,
  `start_processor` int(11) NOT NULL,
  `end_processor` int(11) NOT NULL,
  `cpu_mhz` double NOT NULL,
  `debug` int(11) NOT NULL,
  `ticks` bigint(20) NOT NULL,
  `normalized_ns` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `code_locations_id` (`code_locations_id`),
  CONSTRAINT `code_tick_timings_ibfk_1` FOREIGN KEY (`code_locations_id`) REFERENCES `code_locations` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `rusage_delta`
--

DROP TABLE IF EXISTS `rusage_delta`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `rusage_delta` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `code_locations_id` int(11) NOT NULL,
  `created` datetime NOT NULL,
  `start_processor` int(11) NOT NULL,
  `end_processor` int(11) NOT NULL,
  `cpu_mhz` double NOT NULL,
  `debug` int(11) NOT NULL,
  `user_time_sec` bigint(20) NOT NULL,
  `user_time_usec` bigint(20) NOT NULL,
  `system_time_sec` bigint(20) NOT NULL,
  `system_time_usec` bigint(20) NOT NULL,
  `ru_maxrss` bigint(20) NOT NULL,
  `ru_ixrss` bigint(20) NOT NULL,
  `ru_idrss` bigint(20) NOT NULL,
  `ru_isrss` bigint(20) NOT NULL,
  `ru_minflt` bigint(20) NOT NULL,
  `ru_majflt` bigint(20) NOT NULL,
  `ru_nswap` bigint(20) NOT NULL,
  `ru_inblock` bigint(20) NOT NULL,
  `ru_oublock` bigint(20) NOT NULL,
  `ru_msgsnd` bigint(20) NOT NULL,
  `ru_msgrcv` bigint(20) NOT NULL,
  `ru_nsignals` bigint(20) NOT NULL,
  `ru_nvcsw` bigint(20) NOT NULL,
  `ru_nivcsw` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `code_locations_id` (`code_locations_id`),
  CONSTRAINT `rusage_delta_ibfk_1` FOREIGN KEY (`code_locations_id`) REFERENCES `code_locations` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-10-15 10:41:34
