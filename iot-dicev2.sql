CREATE TABLE `device_session` (
  `device_id` varchar(17) NOT NULL,
  `device_state` enum('waiting','ready','rolled') NOT NULL,
  PRIMARY KEY (`device_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci

CREATE TABLE `dice_rolls` (
  `roll_id` int(11) NOT NULL AUTO_INCREMENT,
  `rolled_number` int(11) NOT NULL,
  `throw_time` timestamp NOT NULL DEFAULT current_timestamp(),
  `device_id` varchar(17) NOT NULL,
  `session_participant_id` int(11) NOT NULL,
  PRIMARY KEY (`roll_id`),
  KEY `dice_rolls_ibfk_1` (`device_id`),
  KEY `dice_rolls_ibfk_2` (`session_participant_id`),
  CONSTRAINT `dice_rolls_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `device_session` (`device_id`) ON DELETE CASCADE,
  CONSTRAINT `dice_rolls_ibfk_2` FOREIGN KEY (`session_participant_id`) REFERENCES `session_participants` (`participant_id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=211 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci

CREATE TABLE `session_participants` (
  `participant_id` int(11) NOT NULL AUTO_INCREMENT,
  `player_name` varchar(255) NOT NULL,
  `device_id` varchar(17) NOT NULL,
  PRIMARY KEY (`participant_id`),
  KEY `session_participants_ibfk_1` (`device_id`),
  CONSTRAINT `session_participants_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `device_session` (`device_id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=102 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci