TESTS=test1
check_PROGRAMS = test1 test2 test3
lib_LTLIBRARIES = libkpass.la
libkpass_la_SOURCES = src/kpass.c
libkpass_la_LDFLAGS = -version-info 1:0:0
include_HEADERS = src/kpass.h
test1_SOURCES  = src/test1.c
test1_LDFLAGS = $(LTLIBINTL)
test1_LDADD = libkpass.la
test2_SOURCES  = src/test2.c
test2_LDFLAGS = $(LTLIBINTL)
test2_LDADD = libkpass.la
test3_SOURCES = src/test3.c
test3_LDFLAGS = $(LTLIBINTL)
test3_LDADD = libkpass.la

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = po

AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"

EXTRA_DIST = build-aux/config.rpath DbFormat.txt TODO

EXTRA_DIST += test/block0.kdb test/block1.kdb test/block2.kdb test/block3.kdb test/block4.kdb test/block5.kdb test/block6.kdb test/block7.kdb test/block8.kdb test/block9.kdb test/block10.kdb test/block11.kdb test/block12.kdb test/block13.kdb test/block14.kdb test/block15.kdb test/keyfile.keyfile test/keyfile.kdb
