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

<h3>Release 1.98</h3>
<p><strong>19th April 2004</strong><br />
<h4>Change Log</h4>
<ul>
<li>Fixed all known bugs:
	<ul>
		<li>The card passing was always to the right.</li>
		<li>Portability issue regarding setting the random seed (std::random_shuffle + std::srand issue).</li>
		<li>A lot of processes were left running.</li>
		<li>Only one match (ie, a series of games until a player gets 100 points) was possible.</li>
	</ul>
<li>Status bar tells the user what he he should do at every step (play, give cards right, etc.)</li>
</ul>


<p>You can see every change in <a href="history.php">the history page</a>.
<?php do_footer(); ?>
