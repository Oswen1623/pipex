#!/usr/bin/env bash
set -euo pipefail

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

cleanup_all() {
  echo -e "${YELLOW}🧹 Cleaning up temporary files...${RESET}"
  cd scripts 2>/dev/null || true
  rm -f test_input.txt output*.txt expected*.txt 2>/dev/null || true
  rm -f empty_file.txt long_line.txt special_chars.txt big_file.txt 2>/dev/null || true
  rm -f readonly_file.txt 2>/dev/null || true
  cd .. 2>/dev/null || true
  echo -e "${GREEN}✓ Cleanup complete${RESET}"
  echo ""
}

check_norminette() {
  echo -e "${CYAN}${BOLD}╔═══════════════════════════════════════════╗${RESET}"
  echo -e "${CYAN}${BOLD}║         NORMINETTE CHECK 📋              ║${RESET}"
  echo -e "${CYAN}${BOLD}╚═══════════════════════════════════════════╝${RESET}"
  echo ""

  if ! command -v norminette &> /dev/null; then
    echo -e "${YELLOW}⚠️  norminette not found, skipping...${RESET}"
    echo ""
    return 0
  fi

  local norm_output=$(norminette *.c *.h libft/*.c libft/*.h 2>&1)
  local norm_errors=$(echo "$norm_output" | grep -c "Error" || true)

  if [ $norm_errors -eq 0 ]; then
    echo -e "  ${GREEN}${BOLD}✓ All files pass norminette!${RESET}"
    echo ""
    return 0
  else
    echo -e "  ${RED}${BOLD}✗ Found $norm_errors norminette error(s)${RESET}"
    echo "$norm_output" | grep "Error" || true
    echo ""
    return 1
  fi
}

usage() {
  echo -e "${CYAN}${BOLD}╔═══════════════════════════════════════════╗${RESET}"
  echo -e "${CYAN}${BOLD}║         PIPEX TEST SUITE 🚀              ║${RESET}"
  echo -e "${CYAN}${BOLD}╚═══════════════════════════════════════════╝${RESET}"
  echo -e ""
  echo -e "${BOLD}Usage:${RESET} ./test.sh [mandatory|bonus|all|norm|clean|help]"
  echo -e ""
  echo -e "  ${YELLOW}mandatory${RESET}  🔧 Run mandatory tests only"
  echo -e "  ${MAGENTA}bonus${RESET}      ⭐ Run bonus tests only"
  echo -e "  ${GREEN}all${RESET}        🎯 Run mandatory then bonus"
  echo -e "  ${BLUE}norm${RESET}       📋 Check norminette"
  echo -e "  ${YELLOW}clean${RESET}      🧹 Clean temporary test files"
  echo -e "  ${BLUE}help${RESET}       ❓ Show this help"
}

run_mandatory() {
  bash ./scripts/mandatory.sh
}

run_bonus() {
  # Vérifier si la règle bonus existe
  if ! make -q bonus 2>/dev/null; then
    echo -e "${YELLOW}⚠️  Compiling bonus...${RESET}"
    if ! make bonus >/dev/null 2>&1; then
      echo -e "${RED}✗ Bonus compilation failed${RESET}"
      return 1
    fi
  fi
  bash ./scripts/bonus.sh
}

if [ ${1:-} = "help" ] || [ $# -eq 0 ]; then
  usage
  exit 0
fi

case "$1" in
  mandatory)
    check_norminette
    run_mandatory
    ;;
  bonus)
    check_norminette
    run_bonus
    ;;
  norm)
    check_norminette
    ;;
  clean)
    cleanup_all
    exit 0
    ;;
  all)
    check_norminette
    norm_result=$?
    set +e
    run_mandatory
    m=$?
    echo ""
    echo -e "${CYAN}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
    echo ""
    run_bonus
    b=$?
    echo ""
    echo -e "${CYAN}${BOLD}╔═══════════════════════════════════════════╗${RESET}"
    echo -e "${CYAN}${BOLD}║           OVERALL RESULTS 📊             ║${RESET}"
    echo -e "${CYAN}${BOLD}╚═══════════════════════════════════════════╝${RESET}"
    if [ $norm_result -eq 0 ] && [ $m -eq 0 ] && [ $b -eq 0 ]; then
      echo -e "${GREEN}${BOLD}✓ ALL TESTS PASSED! 🎉${RESET}"
      echo ""
      cleanup_all
      exit 0
    fi
    echo -e "${RED}${BOLD}✗ SOME TESTS FAILED 😞${RESET}"
    echo ""
    cleanup_all
    exit 1
    ;;
  *)
    usage
    exit 1
    ;;
esac
