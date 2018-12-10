#!/bin/bash

exec sh ./configure CFLAGS="-march=native -mtune=native" CXXFLAGS="-march=native -mtune=native" "$@"
