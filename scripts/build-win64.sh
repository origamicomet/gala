#!/usr/bin/env bash

set -e

scripts/build-debug-win64.sh
scripts/build-development-win64.sh
scripts/build-release-win64.sh
