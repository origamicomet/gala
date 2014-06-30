#!/usr/bin/env bash

set -e

./configure --configuration=development --architecture=x86-64 --toolchain=gcc --suffix=-development-linux64
