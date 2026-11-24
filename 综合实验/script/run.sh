#!/usr/bin/env bash
set -e
cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.."

if [[ ! -x build/tests/training_main ]]; then
    echo "training_main does not exist. Run build.sh first." >&2
    exit 1
fi

exec build/tests/training_main
