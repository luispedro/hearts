<?php include('base.php');
do_header('Download Hearts');
?>


<h2>Beta Version 1.97</h2>
<p><strong>Released on 11th April 2004</strong></p>
<p>This is a beta version of hearts 2.0 -- version 1.97</p>

<p><a href="http://prdownloads.sourceforge.net/hearts/hearts-1.97.tar.bz2?download">Download it</a> (traditional source tarball). This is 
	a <a href="http://www.sf.net/">SourceForge</a> link as I don't want my bandwith bill to shoot up.</p>

<p><b>SuSe 9.0 RPM</b> available at <a href="http://www.freewebs.com/famewolf/hearts-1.97-1.i586.rpm">http://www.freewebs.com/famewolf/hearts-1.97-1.i586.rpm</a> (external link).

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

