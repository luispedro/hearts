CREATE TABLE users
		(id INTEGER AUTO_INCREMENT PRIMARY KEY NOT NULL,
		email CHAR(200),
		username CHAR(40),
		password CHAR(40) NOT NULL,
		lastLogin DATETIME,
		notifyreleases BOOL NOT NULL);

