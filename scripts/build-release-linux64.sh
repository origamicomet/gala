#!/usr/bin/env bash

set -e

scripts/configure-release-linux64.sh
make clean && make all
