#!/usr/bin/env bash

set -e

scripts/configure-release-linux32.sh
make clean && make all
