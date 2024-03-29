<?php
		include('base.php');
		do_header('Hearts\' Development Plan');

		function cvsfixed() {
				print '[FIXED IN <a href="download.php#CVS">CVS</a>]';
		}
		function cvsdone() {
				print '[DONE IN <a href="download.php#CVS">CVS</a>]';
		}
?>

<p>This is basically what I plan to do. There are no dates assigned to any of the steps,
	and there is no guarantee that I will keep the plan 100%, but here it is.</p>

<p>Latest update: <b>28th July 2004</b></p>

<h2>Version 1.98</h2>

<ul>
	<li>Fix all known bugs:
		<ul>
			<li>The card passing is always to the right. <?=cvsfixed()?>
			<li>Portability issue regarding setting the random seed. <?=cvsfixed()?>
			<li>A lot of processes are left running. <?=cvsfixed()?>
			<li>Only one match (ie, a series of games until a player gets 100 points) is possible. <?=cvsfixed()?>
		</ul>
	<li>Have the status bar help on what the user should do at every step (play, give cards right, etc.) <?=cvsdone()?>
</ul>

<h2>Version 1.99</h2>

<p>The focus is on Network Gaming, namelly:</p>

<ul>
<li>Show who's online <?=cvsdone()?>
<li>Message of the Day <?=cvsdone()?>
<li>Allow Registration (and Authentication)
<li>Generate Statistics
</ul>

<h2>Version 2.0 </h2>
<ul>
<li>Make the interface more complete (a Menu Bar with common options).
<li>Write Documentation.
<li>Make the AI players less stupid.
</ul>

<h2>Version 2.1 -- The future</h2>

<p>Some ideas for the future (but low on the priority list):

<ul>

	<li>Have a training mode where you can get tips
	<li>Show what cards the players played at the end of the game
	<li>Plug in to kopete (or similar) for setting up network games
	<li>Clean up the code
	<li>Make good AI players using learning algorithms
</ul>


<?php do_footer(); ?>

