<?php include('base.php');
	require('config.php');
do_header('Register');

import_request_variables('pg','r_');

$done = false;
if (isset($r_name)) {
	if (!$r_name) {
		$error = 'Name needed';
	} else if (!$r_email) {
		$error = 'Email needed';
	} else if (!$r_pwd) {
		$error = 'Password needed';
	} else if ($r_pwd != $r_pwd2) {
		$error = 'Passwords do not match';
		$r_pwd = $r_pwd2 = '';
	} else { // ok
		$handle = mysql_connect($config_db_host, $config_db_user, $config_db_pwd);
		if (!$handle) {
			die('Connection to database failed: ' . mysql_error());
		}
		mysql_select_db($config_db_db);
		if (!$handle) {
			die('Select database failed: ' . mysql_error());
		}
		$res = mysql_query("SELECT * FROM users WHERE username = '$r_name'",$handle);
		if (!$res) {
			die('Query failed: ' . mysql_error());
		}
		if (mysql_num_rows($res)) {
			$error = 'Nickname is use';
			$r_name = '';
		} else {
			$res = mysql_query("SELECT * FROM users WHERE email = '$r_email'");
			if (mysql_num_rows($res)) {
			if (!$res) {
				die('Query failed: ' . mysql_error());
			}
				$error = 'Email already registered. <a href="recover.php">Recover Password</a>';
				$r_email = '';
			} else {
				$notify = 'FALSE';
				if ($r_notify == 'on') $notify = 'TRUE';
				mysql_query("INSERT INTO users(email,username,password,lastLogin,notifyreleases) " .
						"VALUES('$r_email','$r_name','$r_pwd',NOW(),'$notify')")
				or die ('Error: ' . mysql_error());
				$done = true;
			}
		}
		mysql_close($handle);
	}
}

if (!$done) {
	?>
	<h2>Registration on hearts.luispedro.org</h2>
	<?php
	if (isset($error)) {
			?><p>An error occurred: <?=$error?></p><?php
		}
	?>

	<form action="register.php" method="get">
	<table>
	<tr><td>Nickname wanted</td><td><input type="text" name="name" value="<?=$r_name?>" />
	<tr><td>Email</td><td><input type="text" name="email" value="<?=$r_email?>" />
	<tr><td>Password</td><td><input type="password" name="pwd" value="<?=$r_pwd?>" />
	<tr><td>Password (again)</td><td><input type="password" name="pwd2" value="<?=$r_pwd2?>" />
	<tr><td>Notification of releases</td><td>
			<input type="checkbox" <?=($r_notify == "on")?'checked=true':''?> name="notify" />
	<tr><td /><td><input type="submit" value="Register" />
	</table>
	</form>
	
	<hr />
<p>Registration is <b>not necessary</b> in order to use the <b>hearts.luispedro.org</b> server for online gaming. However, without registring, you will not be able to set a user name and you will be known as a guest.</p>
	<?php
} else {
	?>
	<h2>Registration Successful</h2>
	<?php
}

do_footer();

