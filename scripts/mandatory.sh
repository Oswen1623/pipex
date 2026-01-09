#!/usr/bin/env bash
set -euo pipefail

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

# Mandatory tests for pipex (2 commands)

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
  printf "  ${BLUE}[M%-2s]${RESET} %-30s" "$test_num" "$description"

  eval "$pipex_cmd" 2>/dev/null || true
  eval "$shell_cmd" 2>/dev/null || true

  if diff "$output_file" "$expected_file" >/dev/null 2>&1; then
    echo -e " ${GREEN}${BOLD}✓ PASS${RESET}"
    TESTS_PASSED=$((TESTS_PASSED + 1))
  else
    echo -e " ${RED}${BOLD}✗ FAIL${RESET}"
    TESTS_FAILED=$((TESTS_FAILED + 1))
  fi
}

run_error_cmd() {
  local test_num=$1
  local description=$2
  local command=$3

  TOTAL_TESTS=$((TOTAL_TESTS + 1))
  printf "  ${BLUE}[M%-2s]${RESET} %-30s" "$test_num" "$description"

  set +e
  eval "$command" 2>/dev/null
  local exit_code=$?
  set -e

  if [ $exit_code -ne 0 ]; then
    echo -e " ${GREEN}${BOLD}✓ PASS${RESET}"
    TESTS_PASSED=$((TESTS_PASSED + 1))
  else
    echo -e " ${RED}${BOLD}✗ FAIL${RESET}"
    TESTS_FAILED=$((TESTS_FAILED + 1))
  fi
}

cleanup() {
  rm -f test_input.txt output*.txt expected*.txt
  rm -f empty_file.txt long_line.txt special_chars.txt big_file.txt
  rm -f readonly_file.txt test_output.txt
  rm -f fichier_inexistant.txt extra_arg
}

trap 'cleanup; exit 130' INT TERM

echo -e "${CYAN}${BOLD}╔═══════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}${BOLD}║      MANDATORY TESTS 🔧                  ║${RESET}"
echo -e "${CYAN}${BOLD}╚═══════════════════════════════════════════╝${RESET}"
echo ""
printf "${YELLOW}⚙️  Building...${RESET}"
make >/dev/null 2>&1 || make -C ../ >/dev/null 2>&1
echo -e " ${GREEN}Done!${RESET}"
echo ""

cat > test_input.txt << EOF
bonjour tout le monde
ceci est un test
avec plusieurs lignes
pour tester pipex
un autre test
EOF

echo -e "${YELLOW}${BOLD}📝 Running Tests:${RESET}"
echo ""

run_test 1 \
  "grep test | wc -l" \
  "../pipex test_input.txt \"grep test\" \"wc -l\" output1.txt" \
  "< test_input.txt grep test | wc -l > expected1.txt"

run_test 2 \
  "cat | grep test" \
  "../pipex test_input.txt \"cat\" \"grep test\" output2.txt" \
  "< test_input.txt cat | grep test > expected2.txt"

run_test 3 \
  "ls -l | grep pipex" \
  "../pipex test_input.txt \"ls -l\" \"grep pipex\" output3.txt" \
  "< test_input.txt ls -l | grep pipex > expected3.txt"

run_test 4 \
  "head -3 | tail -2" \
  "../pipex test_input.txt \"head -3\" \"tail -2\" output4.txt" \
  "< test_input.txt head -3 | tail -2 > expected4.txt"

run_test 5 \
  "cat | sort" \
  "../pipex test_input.txt \"cat\" \"sort\" output5.txt" \
  "< test_input.txt cat | sort > expected5.txt"

run_test 6 \
  "ls -la | grep test" \
  "../pipex test_input.txt \"ls -la\" \"grep test\" output6.txt" \
  "< test_input.txt ls -la | grep test > expected6.txt"

run_test 7 \
  "cat | grep -i TEST" \
  "../pipex test_input.txt \"cat\" \"grep -i TEST\" output7.txt" \
  "< test_input.txt cat | grep -i TEST > expected7.txt"

run_test 8 \
  "/bin/cat | wc -l" \
  "../pipex test_input.txt \"/bin/cat\" \"wc -l\" output8.txt" \
  "< test_input.txt /bin/cat | wc -l > expected8.txt"

touch empty_file.txt
run_test 9 \
  "empty | wc -l" \
  "../pipex empty_file.txt \"cat\" \"wc -l\" output9.txt" \
  "< empty_file.txt cat | wc -l > expected9.txt"

printf '%*s\n' 10000 | tr ' ' 'a' > long_line.txt
run_test 10 \
  "long_line | wc -c" \
  "../pipex long_line.txt \"cat\" \"wc -c\" output10.txt" \
  "< long_line.txt cat | wc -c > expected10.txt"

cat > special_chars.txt << 'EOF'
test with spaces
test	with	tabs
test,with,commas
test;with;semicolons
EOF

run_test 11 \
  "special_chars | grep with" \
  "../pipex special_chars.txt \"cat\" \"grep with\" output11.txt" \
  "< special_chars.txt cat | grep with > expected11.txt"

echo "ancien contenu" > output12.txt
run_test 12 \
  "overwrite outfile" \
  "../pipex test_input.txt \"cat\" \"head -2\" output12.txt" \
  "< test_input.txt cat | head -2 > expected12.txt"

seq 1 1000 > big_file.txt
run_test 13 \
  "big | tail -5" \
  "../pipex big_file.txt \"cat\" \"tail -5\" output13.txt" \
  "< big_file.txt cat | tail -5 > expected13.txt"

run_test 14 \
  "grep 5 | wc -l" \
  "../pipex big_file.txt \"grep 5\" \"wc -l\" output14.txt" \
  "< big_file.txt grep 5 | wc -l > expected14.txt"

echo ""
echo -e "${YELLOW}${BOLD}⚠️  Error Handling:${RESET}"
echo ""

../pipex fichier_inexistant.txt "cat" "wc -l" output15.txt 2>/dev/null || true
TOTAL_TESTS=$((TOTAL_TESTS + 1))
printf "  ${BLUE}[M%-2s]${RESET} %-30s" "15" "infile missing"
if [ -f output15.txt ]; then
  echo -e " ${GREEN}${BOLD}✓ PASS${RESET}"
  TESTS_PASSED=$((TESTS_PASSED + 1))
else
  echo -e " ${RED}${BOLD}✗ FAIL${RESET}"
  TESTS_FAILED=$((TESTS_FAILED + 1))
fi

run_error_cmd 16 "invalid cmd2" "../pipex test_input.txt \"cat\" \"commande_invalide\" output16.txt"
run_error_cmd 17 "too few args" "../pipex test_input.txt \"cat\""
run_error_cmd 18 "too many args" "../pipex test_input.txt \"cat\" \"wc\" output.txt extra_arg"

touch readonly_file.txt && chmod 000 readonly_file.txt
../pipex readonly_file.txt "cat" "wc -l" output19.txt 2>/dev/null || true
TOTAL_TESTS=$((TOTAL_TESTS + 1))
printf "  ${BLUE}[M%-2s]${RESET} %-30s" "19" "unreadable infile"
if [ -f output19.txt ]; then
  echo -e " ${GREEN}${BOLD}✓ PASS${RESET}"
  TESTS_PASSED=$((TESTS_PASSED + 1))
else
  echo -e " ${RED}${BOLD}✗ FAIL${RESET}"
  TESTS_FAILED=$((TESTS_FAILED + 1))
fi
chmod 644 readonly_file.txt 2>/dev/null || true
rm -f readonly_file.txt

cleanup

echo ""
echo -e "${CYAN}${BOLD}╔═══════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}${BOLD}║           SUMMARY 📊                     ║${RESET}"
echo -e "${CYAN}${BOLD}╚═══════════════════════════════════════════╝${RESET}"
echo -e "  ${BOLD}Total:${RESET}  $TOTAL_TESTS tests"
echo -e "  ${GREEN}${BOLD}Passed:${RESET} $TESTS_PASSED ✓${RESET}"
echo -e "  ${RED}${BOLD}Failed:${RESET} $TESTS_FAILED ✗${RESET}"

if [ "$TESTS_FAILED" -eq 0 ]; then
  echo ""
  echo -e "  ${GREEN}${BOLD}🎉 ALL MANDATORY TESTS PASSED! 🎉${RESET}"
fi
exit $([ "$TESTS_FAILED" -eq 0 ] && echo 0 || echo 1)
