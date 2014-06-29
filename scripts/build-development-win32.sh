#!/usr/bin/env bash

set -e

scripts/configure-development-win32.sh
make clean && make all
rm build/agl-development-win32.ilk || true
