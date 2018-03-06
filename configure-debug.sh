#!/bin/bash

exec sh ./configure --enable-debug --disable-shared CFLAGS="-O0 -ggdb" CXXFLAGS="-ggdb -O0" "$@"
