#!/bin/bash
#-*- sh -*-

PGR_DIR=`readlink -f .`

aclocal ${PGR_DIR}
autoheader ${PGR_DIR}
automake ${PGR_DIR}
autoconf ${PGR_DIR}

