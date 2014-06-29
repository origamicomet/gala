#!/usr/bin/env bash

set -e

scripts/configure-development-win64.sh
make clean && make all
rm build/agl-development-win64.ilk || true
