<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
		xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
		>

  <xsl:output method="text" version="1.0" indent="no" encoding="UTF-8"/>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- options -->
  <xsl:strip-space elements="rhs"/>

   <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- main: template: rule -->
  <xsl:template match="rule">
    <xsl:apply-templates select="rhs"/>
    <xsl:text>&#10;</xsl:text>    
  </xsl:template>
  
  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- main: template: rule/rhs -->
  <xsl:template match="rule/rhs">
    <xsl:value-of select="../@lhs"/>
    <xsl:text> -&gt;</xsl:text>
    <xsl:apply-templates select="*"/>
    <xsl:text>&#10;</xsl:text>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- main: template: rhs elements -->
  <xsl:template match="rule/rhs/*">
    <xsl:text> </xsl:text>
    <xsl:value-of select="text()"/>
  </xsl:template>

  <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
  <!-- main: default: just recurse -->
  <xsl:template match="@*|*|text()|processing-instruction()|comment()" priority="-1">
    <xsl:apply-templates select="@*|*|text()|processing-instruction()|comment()"/>
  </xsl:template>

</xsl:stylesheet>
