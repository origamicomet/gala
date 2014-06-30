#!/usr/bin/env bash

set -e

scripts/configure-debug-linux32.sh
make clean && make all
