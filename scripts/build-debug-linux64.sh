#!/usr/bin/env bash

set -e

scripts/configure-debug-linux64.sh
make clean && make all
