#!/usr/bin/env bash

set -e

scripts/configure-development-linux64.sh
make clean && make all
