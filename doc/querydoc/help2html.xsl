<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  >

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- options -->
  <xsl:output method="html" indent="yes"/>
  <xsl:strip-space elements="doc title author section subsection gsection"/>

  <xsl:param name="date">?</xsl:param>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: root -->
  <xsl:template match="/*">
    <html>
      <head>
	<meta http-equiv="content-type" content="text/html; charset=ISO-8859-1" />
	<title><xsl:value-of select="./head/title/text()"/></title>
	<link rel="stylesheet" href="querydoc.css" type="text/css"/>
      </head>
      <!--/head-->
      <body>
	<div class="outer">
	  <div class="title">
	    <h1><a name="top"><xsl:value-of select="./head/title/text()"/></a></h1>
	  </div>
	  <!--/title-->

	  <div class="headers">
	    <h2>Contents</h2>
	    <ul class="contents-list">
	      <xsl:for-each select="./body/section">
		<li>
		  <xsl:element name="a">
		    <xsl:attribute name="href">#<xsl:value-of select="./@name"/></xsl:attribute>
		    <xsl:value-of select="./@title"/>
		  </xsl:element>
	          <xsl:if test="./subsection|./subsubsection|./section">
  	          <ul>
		    <xsl:for-each select="./subsection|./subsubsection|./section">
			<li>
			  <xsl:element name="a">
			    <xsl:attribute name="href">#<xsl:value-of select="./@name"/></xsl:attribute>
			    <xsl:value-of select="./@title"/>
			  </xsl:element>
			  <xsl:if test="./subsection|./subsubsection|./section">
			    <ul>
			      <xsl:for-each select="./subsection|./subsubsection|./section">
				<li>
				  <xsl:element name="a">
				    <xsl:attribute name="href">#<xsl:value-of select="./@name"/></xsl:attribute>
				    <xsl:value-of select="./@title"/>
				  </xsl:element>
				</li>
			      </xsl:for-each>
			    </ul>
			  </xsl:if>
			</li>
		      </xsl:for-each>
		    </ul>
		  </xsl:if>
		</li>
	      </xsl:for-each>
	    </ul>
	  </div>
	  <!--/headers-->

	  <div class="contents">
	    <xsl:apply-templates select="./body"/>
	  </div>

	  <div class="footers">
	    <div class="footer_sig">
	      <address>
	      <xsl:element name="a">
		<xsl:attribute name="href">mailto:<xsl:value-of select="./head/author/@email"/></xsl:attribute>
		<xsl:value-of select="./head/author/@email"/>
	      </xsl:element>
	      </address>
	      <!-- hhmts start -->Last modified: <xsl:value-of select="$date"/><!-- hhmts end -->
	    </div>
	    <div class="footer_linkbar">
	      <p class="nopad">
		<a class="navLink" href="/">Root</a>
		<a class="navLink" href="./">Back</a>
		<span class="navLinkDisabled">Help</span>
	      </p>
	    </div>
	    <p class="dummy"/>
	  </div>
	  <!--/footers-->

	</div>
	<!--/outer-->
      </body>
    </html>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: section -->
  <xsl:template match="section">
    <div class="section">
      <h2>
	<xsl:element name="a">
	  <xsl:attribute name="name"><xsl:value-of select="./@name"/></xsl:attribute>
	  <xsl:value-of select="./@title"/>
	</xsl:element>
      </h2>
      <xsl:apply-templates select="./node()|text()"/>
    </div>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: subsubsection -->
  <xsl:template match="subsubsection|section/section/section|section/section/subsection" priority="20">
    <div class="subsubsection">
      <h4>
	<xsl:element name="a">
	  <xsl:attribute name="name"><xsl:value-of select="./@name"/></xsl:attribute>
	  <xsl:value-of select="./@title"/>
	</xsl:element>
      </h4>
      <xsl:apply-templates select="./node()|text()"/>
    </div>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: subsection -->
  <xsl:template match="subsection|section/section" priority="10">
    <div class="subsection">
      <h3>
	<xsl:element name="a">
	  <xsl:attribute name="name"><xsl:value-of select="./@name"/></xsl:attribute>
	  <xsl:value-of select="./@title"/>
	</xsl:element>
      </h3>
      <xsl:apply-templates select="./node()|text()"/>
    </div>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: subsection -->
  <xsl:template match="subsection|section/section" priority="1">
    <div class="subsection">
      <h3>
	<xsl:element name="a">
	  <xsl:attribute name="name"><xsl:value-of select="./@name"/></xsl:attribute>
	  <xsl:value-of select="./@title"/>
	</xsl:element>
      </h3>
      <xsl:apply-templates select="./node()|text()"/>
    </div>
  </xsl:template>


  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: rules -->
  <xsl:template match="rules">
    <table class="rulesTable">
      <xsl:apply-templates select="./rule"/>
    </table>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: rules: rule -->
  <xsl:template match="rule">
      <tr>
	<td>
	  <b>
	    <xsl:element name="a">
	      <xsl:attribute name="name">rule_<xsl:value-of select="./@lhs"/></xsl:attribute>
	      <xsl:value-of select="./@lhs"/>
	    </xsl:element>
	  </b>
	</td>
	<td>::=</td>
	<!--<td class="ruleRHS"><xsl:apply-templates select="./rhs[1]"/></td>-->
	<td/>
	<td class="ruleCommentTop">
	  <xsl:if test="./@cmt">
	    <xsl:text>/* </xsl:text>
	    <xsl:value-of select="./@cmt"/>
	    <xsl:text> */</xsl:text>
	  </xsl:if>
	</td>
      </tr>
      <xsl:for-each select="./rhs">
	<tr>
	  <td/><td/>
	  <xsl:element name="td">
	    <xsl:choose>
	      <xsl:when test="position()=1">
		<xsl:attribute name="class">ruleRHS1</xsl:attribute>
	      </xsl:when>
	      <xsl:otherwise>
		<xsl:attribute name="class">ruleRHS</xsl:attribute>
		<xsl:text>| </xsl:text>
	      </xsl:otherwise>
	    </xsl:choose>
	    <xsl:apply-templates select="."/>
	  </xsl:element>
	  <td class="ruleComment">
	    <xsl:text>/* </xsl:text>
	    <xsl:value-of select="./@cmt"/>
	    <xsl:text> */</xsl:text>
	  </td>
	</tr>
      </xsl:for-each>
      <tr><td/><td/><td><b>;</b></td></tr>
      <tr/>
  </xsl:template>


  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: rules: rule: rhs -->
  <xsl:template match="//rule/rhs">
    <xsl:for-each select="./n|t|xt">
      <xsl:choose>
	<xsl:when test="name()='n'">
	  <xsl:call-template name="nonterminal-value">
	    <xsl:with-param name="text" select="./text()"/>
	  </xsl:call-template>
	</xsl:when>
	<xsl:when test="name()='t'">
	  <xsl:call-template name="terminal-value">
	    <xsl:with-param name="text" select="./text()"/>
	  </xsl:call-template>
	</xsl:when>
	<xsl:when test="name()='xt'">
	  <xsl:call-template name="xterminal-value">
	    <xsl:with-param name="text" select="./text()"/>
	  </xsl:call-template>
	</xsl:when>
	<xsl:otherwise>
	  <xsl:apply-templates select="."/>
	</xsl:otherwise>
      </xsl:choose>
      <!--<xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>-->
      <xsl:text disable-output-escaping="yes"> </xsl:text>
    </xsl:for-each>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: rules: rule: rhs: comment -->
  <xsl:template match="//rule/rhs/@cmt">
    <span class="ruleComment">
      <xsl:text>/* </xsl:text>
      <xsl:value-of select="./text()"/>
      <xsl:text> */</xsl:text>
    </span>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: nonterminal values -->
  <xsl:template name="nonterminal-value">
    <xsl:param name="text"/>
    <span class="ruleNonterminal">
      <xsl:element name="a">
	<xsl:attribute name="href">#rule_<xsl:value-of select="$text"/></xsl:attribute>
	<xsl:apply-templates select="$text"/>
      </xsl:element>
    </span>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: terminal values -->
  <xsl:template name="terminal-value">
    <xsl:param name="text"/>
    <span class="ruleTerminal">
      <xsl:choose>
	<xsl:when test="./@href">
	  <xsl:element name="a">
	    <xsl:attribute name="href"><xsl:value-of select="./@href"/></xsl:attribute>
	    <xsl:value-of select="$text"/>
	  </xsl:element>
	</xsl:when>
	<xsl:otherwise>
	  <xsl:value-of select="$text"/>
	</xsl:otherwise>
      </xsl:choose>
    </span>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: extended terminal value -->
  <xsl:template name="xterminal-value">
    <xsl:param name="text"/>
    <span class="ruleXTerminal">
      <xsl:element name="a">
	<xsl:attribute name="href">#term_<xsl:value-of select="$text"/></xsl:attribute>
	<xsl:apply-templates select="$text"/>
      </xsl:element>
    </span>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- template: default: copy -->
  <xsl:template match="@*|node()">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>

</xsl:stylesheet>
