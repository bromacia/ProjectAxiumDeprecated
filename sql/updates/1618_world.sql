-- Glyph of power word: shield
INSERT INTO `spell_proc_event` VALUES (55672, 0x00, 6, 0x00000001, 0x00000000, 0x00000000, 0x00004000, 0x00000000, 0.000000, 0.000000, 0);

-- Bloodsurge
DELETE FROM `spell_proc_event` WHERE `entry` IN (46915);
INSERT INTO `spell_proc_event` VALUES (46915, 0x00, 4, 0x00000040, 0x00000404, 0x00000000, 0x00000000, 0x00000002, 0.000000, 0.000000, 0);