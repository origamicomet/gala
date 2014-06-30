#!/usr/bin/env bash

set -e

./configure --configuration=development --architecture=x86 --toolchain=gcc --suffix=-development-linux32
