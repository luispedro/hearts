<?php include('base.php');
?>
<h1>Download hearts</h1>


<h2 id="CVS"><a name="CVS">Unstable version</a></h2>
<p>There is now public CVS access to a new version which includes the ability to connect to a public hearts server.
<p>Due to the fact that it is still very basic in functionallity and stability, there is no traditional source tarball yet.

<p>Here is to download it and compile it:

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

