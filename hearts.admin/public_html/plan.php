<?php
		include('base.php');
		do_header('Hearts\' Development Plan');

		function cvsdone() {
				print '[FIXED IN <a href="download.php#CVS">CVS</a>]';
		}
?>

<p>This is basically what I plan to do. There are no dates assigned to any of the steps,
	and there is no guarantee that I will keep the plan 100%, but here it is.</p>

<p>Latest update: <b>16th April 2004</b></p>

<h2>Version 1.98</h2>

<ul>
	<li>Fix all known bugs:
		<ul>
			<li>The card passing is always to the right. <?=cvsdone()?>
			<li>Portability issue regarding setting the random seed. <?=cvsdone()?>
			<li>A lot of processes are left running. <?=cvsdone()?>
			<li>Only one match (ie, a series of games until a player gets 100 points) is possible. <?=cvsdone()?>
		</ul>
	<li>Have the status bar help on what the user should do at every step (play, give cards right, etc.) <?=cvsdone()?>
</ul>

<h2>Version 1.99</h2>

<ul>
<li>Make Network Gaming a reality, even if it's very simple.
<li>Show who's online, a Message of the day, have some stats (this is mostly back-end work).
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

