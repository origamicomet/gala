#!/usr/bin/env bash

set -e

scripts/configure-debug-win64.sh
make clean && make all
