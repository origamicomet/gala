#!/usr/bin/env bash

set -e

scripts/configure-debug-win32.sh
make clean && make all
rm build/agl-debug-win32.ilk || true
