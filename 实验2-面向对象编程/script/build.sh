#!/usr/bin/env bash
set -e
cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.."

cmake -S . -B build -G "Unix Makefiles"
cmake --build build
