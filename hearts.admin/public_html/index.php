<?php
include('base.php');
do_header('Hearts for KDE');
?>

<h2>What is hearts?</h2>
<div style="padding: 1px;">
<img style="float:left; margin: 1em" src="images/Ha.png" />
<p>Hearts is a little card game for four persons.</p> 
<p>A computer version of the game comes with Microsoft Windows and is a pretty popular little thing. When I switched to using Linux, I really wanted to play it, but I didn't find anything at all, so I decided to write it myself and here it is.
</div>

<h2>What's New:</h2>

<h3>Release 1.96</h3>
<p><strong>3rd April 2004</strong><br />
<h4>Change Log</h4>
<ul>
	<li>Support for private network games
	<li>No leaving of temporary files in <tt>/tmp</tt></li>
</ul>

<h3>A hearts server where you can find other players on the internet was set up.</h3>
<ul>
	<li>A new version is in the works. Right now you can access it through <a href="download.php#CVS">anonymous CVS</a>, and more traditional release modes are planned.
	<li>A public hearts server was put online thanks to Pavel Troller who volunteered space on a machine of his. Thanks also to Imre, Nagy Jr who also volunteered some space.
</ul>

<h3>Changes in version 1.92</h3>
<ul>
	<li>The setup is different and not a separate program (which will allow me to set up error handling later)
	<li>A couple of display bugs fixed
</ul>

<p>You can see every change in <a href="history.php">the history page</a>.
<?php do_footer(); ?>
