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


<h3>Development Plan</h3>
<p>I put a <a href="plan.php">Development Plan</a> online for all to see.

<h3>Release 1.97</h3>
<p><strong>11th April 2004</strong><br />
<h4>Change Log</h4>
<ul>
	<li>Fix important bug regarding the points (you got your partners' points).</li>
	<li>Make the local game start immediatelly (before you had a small delay).</li>
	<li>Small GUI fixes:
		<ul>
			<li>Accelarator clashes fixed</li>
			<li>Use the same strings in the local and remote game setup</li>
		</ul></li>
	<li>Code cleanup: removed unnecessary files, includes and fixed whitespace
</ul>


<p>You can see every change in <a href="history.php">the history page</a>.
<?php do_footer(); ?>
