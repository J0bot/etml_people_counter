-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost
-- Généré le : ven. 26 nov. 2021 à 07:30
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

USE db_pretpi

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
(2, '7017CFD108F0');

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
('7017CFD108F0');

-- --------------------------------------------------------

--
-- Structure de la table `t_login`
--

CREATE TABLE `t_login` (
  `idLogin` int(11) NOT NULL,
  `logPassword` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

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
-- Index pour la table `t_arduino`
--
ALTER TABLE `t_arduino`
  ADD PRIMARY KEY (`ardMacAddress`);

--
-- Index pour la table `t_login`
--
ALTER TABLE `t_login`
  ADD PRIMARY KEY (`idLogin`);

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
-- AUTO_INCREMENT pour la table `t_login`
--
ALTER TABLE `t_login`
  MODIFY `idLogin` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT pour la table `t_record`
--
ALTER TABLE `t_record`
  MODIFY `recId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=424;

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
