#!/usr/bin/env bash
set -euo pipefail

# Bonus tests for pipex (multi-pipes and here_doc)

TESTS_PASSED=0
TESTS_FAILED=0
TOTAL_TESTS=0

run_test() {
  local test_num=$1
  local description=$2
  local pipex_cmd=$3
  local shell_cmd=$4
  local output_file="output${test_num}.txt"
  local expected_file="expected${test_num}.txt"

  TOTAL_TESTS=$((TOTAL_TESTS + 1))
  echo "[B$test_num] $description"

  eval "$pipex_cmd" 2>/dev/null || true
  eval "$shell_cmd" 2>/dev/null || true

  if diff "$output_file" "$expected_file" >/dev/null 2>&1; then
    echo "PASS"
    TESTS_PASSED=$((TESTS_PASSED + 1))
  else
    echo "FAIL"
    TESTS_FAILED=$((TESTS_FAILED + 1))
  fi
}

cleanup() {
  rm -f test_input.txt output*.txt expected*.txt
}

trap 'cleanup; exit 130' INT TERM

echo "== Build"
make >/dev/null 2>&1 || make -C ../ >/dev/null 2>&1

cat > test_input.txt << EOF
bonjour tout le monde
ceci est un test
avec plusieurs lignes
pour tester pipex
un autre test
EOF

echo "== Bonus"

run_test 20 \
  "cat | grep test | wc -l" \
  "../pipex test_input.txt \"cat\" \"grep test\" \"wc -l\" output20.txt" \
  "< test_input.txt cat | grep test | wc -l > expected20.txt"

run_test 21 \
  "tr → sed → cat -e" \
  "../pipex test_input.txt \"tr a-z A-Z\" \"sed s/TEST/OK/g\" \"cat -e\" output21.txt" \
  "< test_input.txt tr a-z A-Z | sed s/TEST/OK/g | cat -e > expected21.txt"

# here_doc
(
  echo "ligne 1"
  echo "ligne 2"
  echo "LIMIT"
) | ./pipex here_doc LIMIT "cat" "wc -l" output22.txt 2>/dev/null || true
echo -e "ligne 1\nligne 2" | cat | wc -l > expected22.txt 2>/dev/null
TOTAL_TESTS=$((TOTAL_TESTS + 1))
if diff output22.txt expected22.txt >/dev/null 2>&1; then
  echo "[B22] here_doc simple"
  echo "PASS"
  TESTS_PASSED=$((TESTS_PASSED + 1))
else
  echo "[B22] here_doc simple"
  echo "FAIL"
  TESTS_FAILED=$((TESTS_FAILED + 1))
fi

rm -f output23.txt expected23.txt
(
  echo "A"
  echo "STOP"
) | ./pipex here_doc STOP "cat" "tr A-Z a-z" output23.txt 2>/dev/null || true
(
  echo "B"
  echo "STOP"
) | ./pipex here_doc STOP "cat" "tr A-Z a-z" output23.txt 2>/dev/null || true
{
  echo "a"
  echo "b"
} > expected23.txt
TOTAL_TESTS=$((TOTAL_TESTS + 1))
if diff output23.txt expected23.txt >/dev/null 2>&1; then
  echo "[B23] here_doc append"
  echo "PASS"
  TESTS_PASSED=$((TESTS_PASSED + 1))
else
  echo "[B23] here_doc append"
  echo "FAIL"
  TESTS_FAILED=$((TESTS_FAILED + 1))
fi

cleanup

echo "== Summary"
echo "total=$TOTAL_TESTS pass=$TESTS_PASSED fail=$TESTS_FAILED"
exit $([ "$TESTS_FAILED" -eq 0 ] && echo 0 || echo 1)
