#!/usr/bin/env bash

set -e

./configure --paranoid --configuration=debug --architecture=x86-64 --toolchain=gcc --suffix=-debug-linux64
