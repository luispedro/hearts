<?php include_once('base.php');
do_header('History of Hearts');
?>

<h2>Full Hearts History</H2>

<p>This is everything which happened in the project so far, for anyone which might be interested.




<h3>Changes in version 1.98</h3>
<li>Fix all known bugs:
	<ul>
		<li>The card passing is always to the right.</li>
		<li>Portability issue regarding setting the random seed.</li>
		<li>A lot of processes are left running.</li>
		<li>Only one match (ie, a series of games until a player gets 100 points) is possible.</li>
	</ul>
<li>Have the status bar help on what the user should do at every step (play, give cards right, etc.)

<h3>Changes in version 1.97</h3>
<ul>
		<li>Fix important bug regarding the points (you got your partners' points).</li>
		<li>Make the local game start immediately (before you had a small delay).</li>
		<li>Small GUI fixes:
				<ul>
				<li>Accelerator clashes fixed</li>
				<li>Use the same strings in the local and remote game setup</li>
				</ul>
		</li>
		<li>Code cleanup: removed unnecessary files, includes and fixed whitespace
</ul>

<h3>Changes in version 1.96</h3>
<ul>
	<li>Support for private network games
	<li>No leaving of temporary files in <tt>/tmp</tt></li>
	<li>Don't compile the network server by default
</ul>
<h3>Changes in version 1.95</h3>
<ul>
	<li>Alive again
	<li>Sounder setup GUI
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

<h3>Changes in version 1.2pre6</h3>
<ul>
	<li>One bug fixed
	<li>A dutch translation was added thanks to Japie
</ul>


<h3>Changes in version 1.91</h3>
<ul>
	<li>A little animation to show who won (not perfect yet, though)
	<li>Now works with unix sockets for local players (a bonus if you don't have IP address 127.0.0.1 up).
</ul>

<h3>Changes in version 1.2pre5</h3>
<ul>
	<li>A RPM version is available
	<li>Installs itself in /usr and not in /usr/local/kde
</ul>

<h3>Version 1.90</h3>
<p>This is an unstable release with support for networking.

<h3>Version 1.2pre4</h3>
<p>A packaging bug introduced in 1.2pre3 was corrected.

<h3>Moved to sourceforge</h3>
<p>If you are here, you already noticed this.

<h3>Version 1.2pre3</h3>
<p>Another bugfix release.

<h3>Version 1.2pre2</h3>
<p>Another bugfix. Earlier versions weren't even supposed to compile except for a bug in g++. However, if they do compile on your system, they work Ok.

<h3>Version 1.2pre1</h3>
<p>This is a little bugfix version.

<h3>Version 1.2pre0</h3>
<p>V1.0 was supposed to be the end of that code base, but I kind of didn't do anything to get the new rewritten version of the game to work, so I hacked this version together which supposedly works for KDE 2.

<h3>Version 1.0</h3>
<p>Since there were no problems reported with version 0.90, I pumped it up to 1.0. This also marks the end of that code base.

<h3>Changes in v0.90</h3>
<ul>
	<li>The computer players are now (I hope) a little bit better.
Actually, up until now every player had the same algorithm. Now there are
two slightly different algorithms, which are selectedly randomly at runtime.
</ul>

<h3>Changes in v0.0.13</h3>
<ul>
	<li>It is now possible to interrupt a game and start a new one.
	<li>Norbert Andres sent a german translation of the game.
</ul>

<h3>New translation file available - 18 July 2000</h3>
<p>There is now a new <a href="translations.php">translation file available for translators</a>. Note that this file contains strings which are not yet used, but will be in a new version.

<h3>Changes in v0.0.12</h3>
<ul>
	<li>Robert Paulsen sent me a couple of bug fixes, which I&nbsp;believe solve some long standing problems 
	with some versions of gcc. Thank you.
	<li>Minor tweaks in the code.
</ul>

<h3>Page redesign</h3>
<p>The old hearts page was done in about half an hour as a quick hack to put the thing online. I have now decided to do it a bit
better. 

<h3>Changes in v0.0.11</h3>
<ul>
	<li>An updated french translation was submited by Pascal Audoux
	<li>There are small interface details which changed
	<li>There were a lot of internal changes. The code has been cleaned of many useless stuff.
</ul>


<h3>Changes in v0.0.10(es)</h3>
<ul>
	<li>Stupid "draw  game" bug fixed
	<li>The es version contains a spanish translation (and all the others too).
</ul>

<h3>Changes in v0.0.9</h3>
<ul>
	<li>Bugs fixed
</ul>

<h3>Changes in v0.0.7</h3>
<ul>
	<li>Session Management works, which means that you can log out of KDE and
	come back later to find the game exactly like it was.
	<li>There is now a french translation by Pascal Audoux and a Danish one by
	Anders Lund. Thanks for your work!
</ul>

<h3>Changes in v0.0.6 </h3>
<ul>
	<li>There is now a much better handling of idle loops. The program used to suck up resources when it had nothing to do. It now sleeps instead. 
	<li>The order in which the cards are displayed has changed, to make it easier to distinguish the various suits.
	This was suggested to me by Josh Stroup.
	<li>The "One click" card passing facillity now works as expected. 
	<li>Minor changes to the internal playing methods made it (slightly) more powerful. The computer is getting tought to beat. 
	<li>A lot of things in the source code were renamed
</ul>

<h3>in v0.0.5</h3>
<ul>
	<li>There is finally a way to change the name of the players and details like that.</li>
	<li>A couple of bugs were fixed in the computer players.</li>
</ul>

<h3> in v0.0.4:</h3>
<UL>
	<LI>The players are now more intelligent (you used to win 9 out of 10 easily)</LI>
	<LI>I slowed the program down, making the computer players take at least half a secound before moving</LI>
	<LI>By popular demand (both my sister and my girlfriend said they missed it),
	the card passing is now like the one in MS-Hearts
</LI>
	<LI>Some filename changes (to lowercase) and some source code renaming took
	place. The goal of changing the code to KNamingStandard isn't achieved yet,
	though.
	<LI>The portuguese translation is complete
</ul>

<H3>in v0.0.3:
</H3>
<UL>
	<LI>A better icon</LI>
	<LI>More descriptive status messages (they now tell you where you're passing the cards to).</LI>
	<LI>The player names are now visible in the player interface</LI>
	<LI>Some changes to the internal code and file names</LI>
	<LI>The begginnings of a portuguese tranlation</LI>
	<LI>Some bugs in the distribution were fixed </LI>
</UL>

<?php do_footer();?> 
