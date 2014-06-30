#!/usr/bin/env bash

set -e

scripts/configure-release-win32.sh
make clean && make all
