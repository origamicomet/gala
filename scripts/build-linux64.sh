#!/usr/bin/env bash

set -e

scripts/build-debug-linux64.sh
scripts/build-development-linux64.sh
scripts/build-release-linux64.sh
