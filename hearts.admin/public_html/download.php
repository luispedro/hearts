<?php include('base.php');
do_header('Download Hearts');
?>


<h2>Beta Version</h2>
<p><strong>Released on 22 March 2004</strong></p>
<p>This is a beta version of hearts 2.0</p>

<p><a href="http://prdownloads.sourceforge.net/hearts/hearts-1.95.tar.gz?download">Download it</a> (traditional source tarball). This is 
	a <a href="http://www.sf.net/">SourceForge</a> link as I don't want my bandwith bill to shoot up.</p>

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

<h2>Stable version</h2>
<p>This is unmaintained and will be surplanted as soon as possible by a release of the current cvs version.

<p>This version is for single player only. The current stable version is <a href="http://prdownloads.sourceforge.net/hearts/hearts-1.2pre5.tar.gz">1.2pre5, available as a source tarball</a> or as <a href="http://prdownloads.sourceforge.net/hearts/hearts-1.2pre5-1.rpm">RPM for RedHat linux 7.1</a> (don't know whether it will work on 7.0 - mail me if it does).

<?php do_footer(); ?>

