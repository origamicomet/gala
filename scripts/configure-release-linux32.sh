#!/usr/bin/env bash

set -e

./configure --configuration=release --architecture=x86 --toolchain=gcc --suffix=-release-linux32
