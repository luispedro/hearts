<?php include('base.php');
do_header('Download Hearts');
?>


<h2>Beta Version 1.98</h2>
<p><strong>Released on 19th April 2004</strong></p>
<p>This is a beta version of hearts 2.0 -- version 1.98</p>

<p><a href="http://prdownloads.sourceforge.net/hearts/hearts-1.98.tar.bz2?download">Download it</a> (traditional source tarball). This is 
	a <a href="http://www.sf.net/">SourceForge</a> link as I don't want my bandwidth bill to shoot up.</p>


<h2 id="CVS"><a name="CVS">CVS Version</a></h2>
<p>There is public CVS access to the bleeding edge.</p>

<p>Here is how to download it and compile it:</p>

<pre>
cvs -d:pserver:anonymous@hearts.luispedro.org:/hearts co hearts
cd hearts
make -f Makefile.cvs
./configure
make
make install
</pre>

<p>The last step normally has to be done as root. Note that right now it is difficult to run the program without installing as it needs to find different executables in the path. You can get around this using the <code>--prefix</code> option to <code>./configure</code> and setting your <code>PATH</code> variable, but it's much simpler to just install.

<?php do_footer(); ?>

