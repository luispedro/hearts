<?php include('base.php');
do_header('Hearts\' Development Plan');
?>

<p>This is basically what I plan to do. There are no dates assigned to any of the steps,
	and there is no garantee that I will keep the plan 100%, but here it is.

<h2>Version 1.98</h2>

<ul>
	<li>Fix all known bugs:
		<ul>
			<li>The card passing was always to the right.
			<li>Portability issue regarding setting the random seed.
			<li>A lot of processes were left running.
			<li>Make it valgrind clean.
		</ul>
	<li>Have the status bar help on what the user should do at every step (play, give cards right, etc.)
</ul>

<h2>Version 1.99</h2>

<ul>
<li>Make Network Gaming a reality, even if it's very simple.
<li>Show who's online, a Message of the day, have some stats. This is mostly back-end work
</ul>

<h2>Version 2.0 </h2>
<ul>
<li>Add some simple bells and whistles in the Interface.
<li>Make the AI players just a bit less stupid.
</ul>

<h2>Version 2.1 -- The future</h2>

<p>Some ideas for the future (but low on the priority list):

<ul>

	<li>Have a training mode where you can get tips
	<li>Show what cards the players played at the end of the game
	<li>Plug in to kopete (or similar) for setting up network games
	<li>Clean up the code
</ul>


<?php do_footer(); ?>

