#!/usr/bin/env bash

set -e

scripts/configure-release-win64.sh
make clean && make all
