DROP TABLE IF EXISTS `account_ip_history`;
CREATE TABLE `account_ip_history` 
(
  `id` int(11) unsigned NOT NULL,
  `RealmID` int(11) unsigned NOT NULL,
  `ip` varchar(30) NOT NULL,
  `last_access` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`,`RealmID`,`ip`)
) 
ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;