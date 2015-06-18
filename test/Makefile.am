AM_CPPFLAGS = -I ../src

TESTS = tree_traversal_test

check_PROGRAMS = 

lib_LTLIBRARIES = libtest.la
libtest_la_SOURCES = test.h test.cc time_util.h time_util.cc

tree_traversal_test_SOURCES = test.h tree_traversal_test.cc $(top_builddir)/src/tree_traversal.h
tree_traversal_test_LDADD = $(top_builddir)/src/libtree_traversal.la libtest.la

check_PROGRAMS += tree_traversal_test
