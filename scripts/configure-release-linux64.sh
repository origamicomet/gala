#!/usr/bin/env bash

set -e

./configure --configuration=release --architecture=x86-64 --toolchain=gcc --suffix=-release-linux64
