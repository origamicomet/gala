#!/usr/bin/env bash

set -e

scripts/configure-development-win32.sh
make clean && make all
