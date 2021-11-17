-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost
-- Généré le : mer. 17 nov. 2021 à 13:29
-- Version du serveur :  5.7.11
-- Version de PHP : 8.0.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `db_pretpi`
--

-- --------------------------------------------------------

--
-- Structure de la table `linkedto`
--

CREATE TABLE `linkedto` (
  `regId` int(11) NOT NULL,
  `ardMacAddress` varchar(17) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `linkedto`
--

INSERT INTO `linkedto` (`regId`, `ardMacAddress`) VALUES
(2, '123456'),
(1, 'f0:08:d1:cf:17:70');

-- --------------------------------------------------------

--
-- Structure de la table `test`
--

CREATE TABLE `test` (
  `id` int(11) NOT NULL,
  `abc` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `test`
--

INSERT INTO `test` (`id`, `abc`) VALUES
(1, 'Salut'),
(2, 'Salut'),
(3, 'Salut'),
(4, 'Salut'),
(5, 'Salut'),
(6, 'Salut'),
(7, 'Salut'),
(8, 'Salut'),
(9, 'Salut'),
(10, 'Salut'),
(11, 'Salut'),
(12, 'Salut'),
(13, 'Salut'),
(14, 'Salut'),
(15, 'Salut'),
(16, 'Salut'),
(17, 'Salut'),
(18, 'Salut'),
(19, 'Salut'),
(20, 'Salut'),
(21, 'Salut'),
(22, 'Salut'),
(23, 'Salut'),
(24, 'Salut'),
(25, 'Salut'),
(26, 'Salut'),
(27, 'Salut'),
(28, 'Salut'),
(29, 'Salut'),
(30, 'Salut'),
(31, 'Salut'),
(32, 'Salut'),
(33, 'Salut'),
(34, 'Salut'),
(35, 'Salut'),
(36, 'Salut'),
(37, 'Salut'),
(38, 'Salut'),
(39, 'Salut'),
(40, 'Salut'),
(41, 'Salut'),
(42, 'Salut'),
(43, 'Salut'),
(44, 'Salut'),
(45, 'Salut'),
(46, 'Salut'),
(47, 'Salut'),
(48, 'Salut'),
(49, 'Salut'),
(50, 'Salut'),
(51, 'Salut'),
(52, 'Salut'),
(53, 'Salut'),
(54, 'Salut'),
(55, 'Salut'),
(56, 'Salut'),
(57, 'Salut'),
(58, 'Salut'),
(59, 'Salut'),
(60, 'Salut'),
(61, 'Salut'),
(62, 'Salut'),
(63, 'Salut'),
(64, 'Salut'),
(65, 'Salut'),
(66, 'Salut'),
(67, 'Salut'),
(68, 'Salut'),
(69, 'Salut'),
(70, 'Salut'),
(71, 'Salut'),
(72, 'Salut'),
(73, 'Salut'),
(74, 'Salut'),
(75, 'Salut'),
(76, 'Salut'),
(77, 'Salut'),
(78, 'Salut'),
(79, 'Salut'),
(80, 'Salut'),
(81, 'Salut'),
(82, 'Salut'),
(83, 'Salut'),
(84, 'Salut'),
(85, 'Salut'),
(86, 'Salut'),
(87, 'Salut'),
(88, 'Salut'),
(89, 'Salut'),
(90, 'Salut'),
(91, 'Salut');

-- --------------------------------------------------------

--
-- Structure de la table `t_arduino`
--

CREATE TABLE `t_arduino` (
  `ardMacAddress` varchar(17) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `t_arduino`
--

INSERT INTO `t_arduino` (`ardMacAddress`) VALUES
('123456'),
('f0:08:d1:cf:17:70');

-- --------------------------------------------------------

--
-- Structure de la table `t_record`
--

CREATE TABLE `t_record` (
  `recId` int(11) NOT NULL,
  `recDate` datetime NOT NULL,
  `recType` varchar(50) NOT NULL,
  `ardMacAddress` varchar(17) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `t_record`
--

INSERT INTO `t_record` (`recId`, `recDate`, `recType`, `ardMacAddress`) VALUES
(10, '2021-10-07 16:15:46', 'entry', 'f0:08:d1:cf:17:70'),
(11, '2021-10-07 16:25:14', 'exit', 'f0:08:d1:cf:17:70'),
(12, '2021-11-12 09:17:17', 'entry', 'f0:08:d1:cf:17:70'),
(13, '2021-11-12 09:18:23', 'exit', 'f0:08:d1:cf:17:70');

-- --------------------------------------------------------

--
-- Structure de la table `t_region`
--

CREATE TABLE `t_region` (
  `regId` int(11) NOT NULL,
  `regType` varchar(50) NOT NULL,
  `regName` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `t_region`
--

INSERT INTO `t_region` (`regId`, `regType`, `regName`) VALUES
(1, 'labo', 'N501'),
(2, 'labo', 'N512B');

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `linkedto`
--
ALTER TABLE `linkedto`
  ADD PRIMARY KEY (`regId`,`ardMacAddress`),
  ADD KEY `linkedTo_t_arduino0_FK` (`ardMacAddress`);

--
-- Index pour la table `test`
--
ALTER TABLE `test`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `t_arduino`
--
ALTER TABLE `t_arduino`
  ADD PRIMARY KEY (`ardMacAddress`);

--
-- Index pour la table `t_record`
--
ALTER TABLE `t_record`
  ADD PRIMARY KEY (`recId`),
  ADD KEY `t_record_t_arduino_FK` (`ardMacAddress`),
  ADD KEY `recType` (`recType`);

--
-- Index pour la table `t_region`
--
ALTER TABLE `t_region`
  ADD PRIMARY KEY (`regId`),
  ADD KEY `regName` (`regName`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `test`
--
ALTER TABLE `test`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=92;

--
-- AUTO_INCREMENT pour la table `t_record`
--
ALTER TABLE `t_record`
  MODIFY `recId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT pour la table `t_region`
--
ALTER TABLE `t_region`
  MODIFY `regId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `linkedto`
--
ALTER TABLE `linkedto`
  ADD CONSTRAINT `linkedTo_t_arduino0_FK` FOREIGN KEY (`ardMacAddress`) REFERENCES `t_arduino` (`ardMacAddress`),
  ADD CONSTRAINT `linkedTo_t_region_FK` FOREIGN KEY (`regId`) REFERENCES `t_region` (`regId`);

--
-- Contraintes pour la table `t_record`
--
ALTER TABLE `t_record`
  ADD CONSTRAINT `t_record_t_arduino_FK` FOREIGN KEY (`ardMacAddress`) REFERENCES `t_arduino` (`ardMacAddress`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
