#!/usr/bin/perl -w


while (<>) {
  s/([^[:print:][:space:]])/sprintf("\\x{%02x}",ord($1))/eg;
  print;
}
