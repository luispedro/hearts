<?php include('base.php');
do_header('Download Hearts');
?>


<h2>Beta Version</h2>
<p><strong>Released on 22 March 2004</strong></p>
<p>This is a beta version of hearts 2.0</p>

<p><a href="http://prdownloads.sourceforge.net/hearts/hearts-1.95.tar.gz?download">Download it</a> (traditional source tarball). This is 
	a <a href="http://www.sf.net/">SourceForge</a> link as I don't want my bandwith bill to shoot up.</p>

<p>A helpful Rudi Pittman contributed a <a href="http://prdownloads.sourceforge.net/hearts/hearts-1.95-1.i586.rpm?download">SuSe 9.0 RPM</a></p>.

<h2 id="CVS"><a name="CVS">CVS Version</a></h2>
<p>There is public CVS access to a new version which includes the ability to connect to a public hearts server.</p>

<p>Here is how to download it and compile it:</p>

<pre>
cvs -d:pserver:anonymous@hearts.luispedro.org:/hearts co hearts
cd hearts
make -f Makefile.cvs
./configure
make
make install
</pre>

<p>The last step normally has to be done as root. Note that right now it is difficult to run the program without installing as it needs to find different executables in the path. You can get around this using the <code>--prefix</code> option to <code>./configure</code> and setting your <code>PATH</code> variable.

<?php do_footer(); ?>

