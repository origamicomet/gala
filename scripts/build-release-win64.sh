#!/usr/bin/env bash

set -e

scripts/configure-release-win64.sh
make clean && make all
rm build/agl-release-win64.ilk || true
