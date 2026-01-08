#!/usr/bin/env bash
set -euo pipefail

echo "Deprecated: use ./test.sh [mandatory|bonus|all]"
exec bash ./test.sh "${1:-help}"
