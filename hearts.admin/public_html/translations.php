<?php include_once('base.php');
do_header();
?>
<h1>Translations</h1>
<DIV align="center">
<TABLE width="620">
<TR>
	<TH>Language
	<TH>Translator
	<TH>Po Files
	<TH>Documentation
<TR>
	<TD>French
	<TD><a href="mailto:paudoux@chez.com">Pascal Audoux</a>
	<TD>updated for v0.0.10
	<TD>updated for v0.0.10
<TR>
	<TD>German
	<TD>Norbert Andres
	<TD>updated for v0.0.13
	<TD>Not Available
<TR>
	<TD>Portuguese
	<TD><a href="mailto:luis@luispedro.org">Me</a>
	<TD>updated for v0.0.10
	<TD>updated for v0.0.10
<TR>
	<TD>Danish
	<TD>Anders Lund
	<TD>updated for v0.0.6
	<TD>No

<TR>
	<TD>Spanish
	<TD>Ale Feltes Quenhan
	<TD>updated for v0.0.10
	<TD>No
<TR>
	<TD>Dutch
	<TD>Japie
	<TD><a href="mailto:House-Mouse@hetnet.nl">Japie</a>
	<TD>Updated for v1.2pre6
	<TD>No

</TR>
</TABLE>
</DIV>

<p>If you want to translate the game use either the hearts.pot and index.sgml files available from the newest source release or 
     download the, now:
<UL>
	<LI><a href="heart.txt">hearts.pot</a> This has a .txt ending on the server, due to Geocities' restrictions on <cite>File&nbsp;Types</cite></LI>
	<LI><a href="index.sgml">index.sgml</a></LI>
</UL>

<p>Do <strong>not</strong> use that automated tool to extract the messages from sourcecode. It will not find a lot of them, since they are in arrays or are otherwise indirectly acessed.

<?php do_footer(); ?>
