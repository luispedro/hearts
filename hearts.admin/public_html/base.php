<?php

function do_header($title) {
	?><!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN">

<html>
<head>
<title><?=$title?></title>

<link rel="made" href="mailto:luis@luispedro.org" />
<link rel="stylesheet" href="style/bluegrey.css" type="text/css" />

<META CONTENT="hearts, game, linux game, card game" NAME="keywords">
<META CONTENT="This is a clone of the hearts game that comes with Windows 9x for KDE." NAME="description">


</head>


<body>
<div id="title">
<h1><?=$title?></h1>
</div>

<div class="boxxed toc">
<p>
<a href="index.php">Main</a> <br />
 <a href="download.php">Download</a> <br />
 <a href="screenshots.php">Screenshots</a> <br />
 <a href="translations.php">Translations</a>
</div>
<div class="boxxed" id="author">
<p><b>Author Information</b><p>
<p>
Luís Pedro Coelho <br />
<a href="mailto:luis@luispedro.org">luis@luispedro.org</a> <br />
<a href="http://luispedro.org/">Home Page
</div>
<div id="content">
<?php 
}

function do_footer() {
	?>
</div>
</body></html>
<?php
}
?>
