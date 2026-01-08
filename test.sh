#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<EOF
Usage: ./test.sh [mandatory|bonus|all|help]

mandatory  Run mandatory tests only
bonus      Run bonus tests only
all        Run mandatory then bonus
help       Show this help
EOF
}

run_mandatory() {
  bash ./scripts/mandatory.sh
}

run_bonus() {
  bash ./scripts/bonus.sh
}

if [ ${1:-} = "help" ] || [ $# -eq 0 ]; then
  usage
  exit 0
fi

case "$1" in
  mandatory)
    run_mandatory
    ;;
  bonus)
    run_bonus
    ;;
  all)
    set +e
    run_mandatory
    m=$?
    echo "--"
    run_bonus
    b=$?
    echo "== Overall"
    if [ $m -eq 0 ] && [ $b -eq 0 ]; then
      echo "ok"
      exit 0
    fi
    echo "fail"
    exit 1
    ;;
  *)
    usage
    exit 1
    ;;
esac
