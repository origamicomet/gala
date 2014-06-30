#!/usr/bin/env bash

set -e

scripts/configure-development-linux32.sh
make clean && make all
