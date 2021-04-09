#!/usr/bin/env bash

CXX_CPPCHECK_OPTIONS="--language=c++ --std=c++11 --verbose "
cppcheck $CXX_CPPCHECK_OPTIONS --xml --xml-version=2 ./tests 2>stat-analyze-report-tests.xml
