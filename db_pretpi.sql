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
(2, '7017CFD108F0'),
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
('7017CFD108F0'),
('AAA'),
('f0:08:d1:cf:17:70');

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

--
-- Déchargement des données de la table `t_record`
--

INSERT INTO `t_record` (`recId`, `recDate`, `recType`, `ardMacAddress`) VALUES
(351, '2021-11-19 10:29:11', 'exit', '7017CFD108F0'),
(352, '2021-11-19 10:34:01', 'exit', '7017CFD108F0'),
(353, '2021-11-19 10:38:29', 'entry', '7017CFD108F0'),
(354, '2021-11-19 10:38:35', 'entry', '7017CFD108F0'),
(355, '2021-11-19 10:41:27', 'entry', '7017CFD108F0'),
(356, '2021-11-19 10:41:45', 'exit', '7017CFD108F0'),
(357, '2021-11-19 10:41:50', 'exit', '7017CFD108F0'),
(358, '2021-11-19 10:41:50', 'exit', '7017CFD108F0'),
(359, '2021-11-19 10:41:53', 'exit', '7017CFD108F0'),
(360, '2021-11-19 10:41:54', 'exit', '7017CFD108F0'),
(361, '2021-11-19 10:41:56', 'exit', '7017CFD108F0'),
(362, '2021-11-19 10:42:09', 'exit', '7017CFD108F0'),
(363, '2021-11-19 10:42:15', 'exit', '7017CFD108F0'),
(364, '2021-11-19 10:48:38', 'exit', '7017CFD108F0'),
(365, '2021-11-19 10:49:07', 'entry', '7017CFD108F0'),
(366, '2021-11-19 10:50:11', 'exit', '7017CFD108F0'),
(367, '2021-11-19 10:50:12', 'exit', '7017CFD108F0'),
(368, '2021-11-19 10:50:12', 'exit', '7017CFD108F0'),
(369, '2021-11-19 10:50:22', 'exit', '7017CFD108F0'),
(370, '2021-11-19 10:50:24', 'exit', '7017CFD108F0'),
(371, '2021-11-19 10:50:24', 'exit', '7017CFD108F0'),
(372, '2021-11-19 10:50:37', 'entry', '7017CFD108F0'),
(373, '2021-11-19 10:50:40', 'entry', '7017CFD108F0'),
(374, '2021-11-19 10:51:34', 'entry', '7017CFD108F0'),
(375, '2021-11-19 10:52:19', 'exit', '7017CFD108F0'),
(376, '2021-11-19 10:52:20', 'exit', '7017CFD108F0'),
(377, '2021-11-19 10:52:22', 'exit', '7017CFD108F0'),
(378, '2021-11-19 10:52:23', 'exit', '7017CFD108F0'),
(379, '2021-11-19 10:52:53', 'entry', '7017CFD108F0'),
(380, '2021-11-19 10:55:03', 'exit', '7017CFD108F0'),
(381, '2021-11-19 10:55:04', 'entry', '7017CFD108F0'),
(382, '2021-11-19 10:55:06', 'entry', '7017CFD108F0'),
(383, '2021-11-19 10:55:09', 'entry', '7017CFD108F0'),
(384, '2021-11-19 10:55:11', 'exit', '7017CFD108F0'),
(385, '2021-11-19 11:00:15', 'exit', '7017CFD108F0'),
(386, '2021-11-19 11:06:32', 'exit', '7017CFD108F0'),
(387, '2021-11-19 11:11:57', 'exit', '7017CFD108F0'),
(388, '2021-11-24 15:03:13', 'exit', '7017CFD108F0'),
(389, '2021-11-24 15:03:42', 'entry', '7017CFD108F0'),
(390, '2021-11-24 15:03:49', 'entry', '7017CFD108F0'),
(391, '2021-11-24 15:04:01', 'entry', '7017CFD108F0'),
(392, '2021-11-24 15:04:33', 'exit', '7017CFD108F0'),
(393, '2021-11-24 15:04:42', 'entry', '7017CFD108F0'),
(394, '2021-11-24 15:04:52', 'exit', '7017CFD108F0'),
(395, '2021-11-24 15:12:07', 'exit', '7017CFD108F0'),
(396, '2021-11-24 15:12:10', 'entry', '7017CFD108F0'),
(397, '2021-11-24 15:12:19', 'entry', '7017CFD108F0'),
(398, '2021-11-24 15:12:24', 'exit', '7017CFD108F0'),
(399, '2021-11-24 15:16:05', 'entry', '7017CFD108F0'),
(400, '2021-11-24 15:16:12', 'exit', '7017CFD108F0'),
(401, '2021-11-24 15:16:33', 'entry', '7017CFD108F0'),
(402, '2021-11-24 15:16:40', 'exit', '7017CFD108F0'),
(403, '2021-11-24 15:16:42', 'exit', '7017CFD108F0'),
(404, '2021-11-24 15:19:27', 'exit', '7017CFD108F0'),
(405, '2021-11-24 15:19:51', 'exit', '7017CFD108F0'),
(406, '2021-11-24 15:20:37', 'exit', '7017CFD108F0'),
(407, '2021-11-24 15:20:47', 'entry', '7017CFD108F0'),
(408, '2021-11-24 15:20:59', 'exit', '7017CFD108F0'),
(409, '2021-11-24 15:21:06', 'entry', '7017CFD108F0'),
(410, '2021-11-24 15:21:23', 'exit', '7017CFD108F0'),
(411, '2021-11-24 15:21:25', 'exit', '7017CFD108F0'),
(412, '2021-11-24 15:21:28', 'exit', '7017CFD108F0'),
(413, '2021-11-24 15:31:07', 'exit', '7017CFD108F0'),
(414, '2021-11-24 15:31:16', 'entry', '7017CFD108F0'),
(415, '2021-11-24 15:31:18', 'entry', '7017CFD108F0'),
(416, '2021-11-24 15:31:20', 'exit', '7017CFD108F0'),
(417, '2021-11-24 15:31:21', 'exit', '7017CFD108F0'),
(418, '2021-11-24 15:31:32', 'exit', '7017CFD108F0'),
(419, '2021-11-24 15:31:35', 'exit', '7017CFD108F0'),
(420, '2021-11-24 15:31:37', 'exit', '7017CFD108F0'),
(421, '2021-11-24 15:31:40', 'entry', '7017CFD108F0'),
(422, '2021-11-24 15:35:05', 'exit', '7017CFD108F0'),
(423, '2021-11-24 15:37:02', 'exit', '7017CFD108F0');

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
-- AUTO_INCREMENT pour la table `test`
--
ALTER TABLE `test`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=92;

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
