AM_CPPFLAGS = -I ../src

TESTS = combinations_test major_element_test tree_traversal_test

check_PROGRAMS = 

lib_LTLIBRARIES = libtest.la
libtest_la_SOURCES = test.h test.cc time_util.h time_util.cc

combinations_test_SOURCES = combinations_test.cc $(top_builddir)/src/combinations.h
combinations_test_LDADD = $(top_builddir)/src/libcombinations.la libtest.la

major_element_test_SOURCES = major_element_test.cc $(top_builddir)/src/major_element.h
major_element_test_LDADD = $(top_builddir)/src/libmajor_element.la libtest.la

tree_traversal_test_SOURCES = test.h tree_traversal_test.cc $(top_builddir)/src/tree_traversal.h
tree_traversal_test_LDADD = $(top_builddir)/src/libtree_traversal.la libtest.la

check_PROGRAMS += combinations_test major_element_test tree_traversal_test
