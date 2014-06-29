#!/usr/bin/env bash

set -e

./configure --configuration=release --architecture=x86-64 --toolchain=msvc --platform=windows-mingw --windows-sdk="C:\Program Files\Microsoft SDKs\Windows\v7.1" --vs-path="C:\Program Files (x86)\Microsoft Visual Studio 12.0" --suffix=-release-win64
