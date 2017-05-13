#!/bin/bash
#-*- sh -*-

PGR_DIR=`readlink -f .`

aclocal 
autoheader 
automake --add-missing
autoconf 

