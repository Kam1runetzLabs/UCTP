#!/usr/bin/env bash
files=$(find . -name "*.c" -or -name "*.h" -or -name "*.cpp" -or -name "*.hpp" | grep -v "./tools/*" | grep -v "./src/application_server/thirdparty/*" | grep -v "./cmake-build-debug/*" | grep -v "./_builds/*")
filter=-build/c++11,-runtime/references,-whitespace/braces,-whitespace/indent,-whitespace/comments,-build/include_order,-build/header_guard,-build/include_subdir
echo $files | xargs cpplint --filter=$filter
