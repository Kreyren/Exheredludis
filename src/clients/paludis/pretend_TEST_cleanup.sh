#!/bin/bash
# vim: set ft=sh sw=4 sts=4 et :

if [ -d pretend_TEST_dir ] ; then
    rm -fr pretend_TEST_dir
else
    true
fi
