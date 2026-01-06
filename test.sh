#!/bin/bash

# ============================================================
# Script de test pour PIPEX
# Teste les fonctionnalités de base et les cas d'erreur
# ============================================================

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Compteurs de résultats
TESTS_PASSED=0
TESTS_FAILED=0
TOTAL_TESTS=0

# Fonction pour afficher le header
print_header() {
    echo -e "\n${CYAN}╔════════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║     TESTS AUTOMATIQUES - PIPEX         ║${NC}"
    echo -e "${CYAN}╔════════════════════════════════════════╗${NC}\n"
}

# Fonction pour afficher une section
print_section() {
    echo -e "\n${YELLOW}┌─────────────────────────────────────────┐${NC}"
    echo -e "${YELLOW}│ $1${NC}"
    echo -e "${YELLOW}└─────────────────────────────────────────┘${NC}\n"
}

# Fonction pour tester une commande
run_test() {
    local test_num=$1
    local description=$2
    local pipex_cmd=$3
    local shell_cmd=$4
    local output_file="output${test_num}.txt"
    local expected_file="expected${test_num}.txt"

    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    echo -e "${BLUE}Test $test_num:${NC} $description"
    echo -e "${CYAN}  Commande: $pipex_cmd${NC}"

    # Exécuter pipex
    eval "$pipex_cmd" 2>/dev/null

    # Exécuter la commande shell équivalente
    eval "$shell_cmd" 2>/dev/null

    # Comparer les résultats
    if diff "$output_file" "$expected_file" > /dev/null 2>&1; then
        echo -e "${GREEN}  ✓ RÉUSSI${NC}\n"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo -e "${RED}  ✗ ÉCHOUÉ${NC}"
        echo -e "${YELLOW}  Attendu:${NC}"
        cat "$expected_file" | sed 's/^/    /'
        echo -e "${YELLOW}  Obtenu:${NC}"
        cat "$output_file" | sed 's/^/    /'
        echo ""
        TESTS_FAILED=$((TESTS_FAILED + 1))
    fi
}

# Fonction pour tester les erreurs
run_error_test() {
    local test_num=$1
    local description=$2
    local command=$3

    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    echo -e "${BLUE}Test $test_num:${NC} $description"
    echo -e "${CYAN}  Commande: $command${NC}"

    eval "$command" 2>/dev/null

    if [ $? -ne 0 ]; then
        echo -e "${GREEN}  ✓ RÉUSSI (erreur correctement gérée)${NC}\n"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo -e "${RED}  ✗ ÉCHOUÉ (devrait retourner une erreur)${NC}\n"
        TESTS_FAILED=$((TESTS_FAILED + 1))
    fi
}

# Fonction pour nettoyer les fichiers de test
cleanup_test_files() {
    echo -e "${YELLOW}Nettoyage des fichiers temporaires...${NC}"
    rm -f test_input.txt output*.txt expected*.txt
    rm -f empty_file.txt long_line.txt special_chars.txt big_file.txt
    rm -f readonly_file.txt test_output.txt
    echo -e "${GREEN}✓ Fichiers temporaires supprimés${NC}"
}

# Fonction pour afficher le résumé
print_summary() {
    echo -e "\n${CYAN}╔════════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║           RÉSUMÉ DES TESTS             ║${NC}"
    echo -e "${CYAN}╚════════════════════════════════════════╝${NC}\n"
    echo -e "  Total de tests : ${BLUE}$TOTAL_TESTS${NC}"
    echo -e "  Tests réussis  : ${GREEN}$TESTS_PASSED${NC}"
    echo -e "  Tests échoués  : ${RED}$TESTS_FAILED${NC}"

    if [ $TESTS_FAILED -eq 0 ]; then
        echo -e "\n${GREEN}  🎉 TOUS LES TESTS SONT PASSÉS ! 🎉${NC}\n"
    else
        echo -e "\n${YELLOW}  ⚠️  Certains tests ont échoué${NC}\n"
    fi
}

# Gérer l'interruption (Ctrl+C)
trap 'echo -e "\n${RED}Tests interrompus${NC}"; cleanup_test_files; exit 130' INT TERM

# ============================================================
# DÉBUT DES TESTS
# ============================================================

print_header

# Vérification de la norme
print_section "VÉRIFICATION DE LA NORME"
echo -e "${YELLOW}Exécution de norminette...${NC}"
norminette_output=$(norminette 2>&1)
norminette_errors=$(echo "$norminette_output" | grep -c "Error")

if [ $norminette_errors -eq 0 ]; then
    echo -e "${GREEN}✓ Norme respectée (aucune erreur)${NC}"
else
    echo -e "${RED}✗ Erreurs de norme détectées : $norminette_errors${NC}"
    echo "$norminette_output" | grep "Error" | head -10
    if [ $norminette_errors -gt 10 ]; then
        echo -e "${YELLOW}... et $((norminette_errors - 10)) autres erreurs${NC}"
    fi
fi

# Compilation
print_section "COMPILATION"
echo -e "${YELLOW}Compilation du projet avec 'make re'...${NC}"
make re
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Erreur de compilation${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Compilation réussie${NC}"

# Créer le fichier de test
cat > test_input.txt << EOF
bonjour tout le monde
ceci est un test
avec plusieurs lignes
pour tester pipex
un autre test
EOF

echo -e "${CYAN}Fichier de test créé (test_input.txt)${NC}"

# ============================================================
# TESTS DE FONCTIONNALITÉS
# ============================================================

print_section "TESTS DE FONCTIONNALITÉS"

run_test 1 \
    "Compter les lignes contenant 'test'" \
    "./pipex test_input.txt \"grep test\" \"wc -l\" output1.txt" \
    "< test_input.txt grep test | wc -l > expected1.txt"

run_test 2 \
    "Afficher les lignes contenant 'test'" \
    "./pipex test_input.txt \"cat\" \"grep test\" output2.txt" \
    "< test_input.txt cat | grep test > expected2.txt"

run_test 3 \
    "Lister et filtrer les fichiers" \
    "./pipex test_input.txt \"ls -l\" \"grep pipex\" output3.txt" \
    "< test_input.txt ls -l | grep pipex > expected3.txt"

run_test 4 \
    "Head et tail combinés" \
    "./pipex test_input.txt \"head -3\" \"tail -2\" output4.txt" \
    "< test_input.txt head -3 | tail -2 > expected4.txt"

run_test 5 \
    "Trier les lignes" \
    "./pipex test_input.txt \"cat\" \"sort\" output5.txt" \
    "< test_input.txt cat | sort > expected5.txt"

run_test 6 \
    "Commande avec options multiples" \
    "./pipex test_input.txt \"ls -la\" \"grep test\" output6.txt" \
    "< test_input.txt ls -la | grep test > expected6.txt"

run_test 7 \
    "Grep avec option -i (insensible à la casse)" \
    "./pipex test_input.txt \"cat\" \"grep -i TEST\" output7.txt" \
    "< test_input.txt cat | grep -i TEST > expected7.txt"

run_test 8 \
    "Chemin absolu pour une commande" \
    "./pipex test_input.txt \"/bin/cat\" \"wc -l\" output8.txt" \
    "< test_input.txt /bin/cat | wc -l > expected8.txt"

# ============================================================
# TESTS AVEC CAS SPÉCIAUX
# ============================================================

print_section "TESTS AVEC CAS SPÉCIAUX"

# Créer un fichier vide
touch empty_file.txt

run_test 9 \
    "Fichier d'entrée vide" \
    "./pipex empty_file.txt \"cat\" \"wc -l\" output9.txt" \
    "< empty_file.txt cat | wc -l > expected9.txt"

# Créer un fichier avec une très longue ligne
printf '%*s\n' 10000 | tr ' ' 'a' > long_line.txt

run_test 10 \
    "Ligne très longue (10000 caractères)" \
    "./pipex long_line.txt \"cat\" \"wc -c\" output10.txt" \
    "< long_line.txt cat | wc -c > expected10.txt"

# Créer un fichier avec caractères spéciaux
cat > special_chars.txt << 'EOF'
test with spaces
test	with	tabs
test,with,commas
test;with;semicolons
EOF

run_test 11 \
    "Fichier avec caractères spéciaux" \
    "./pipex special_chars.txt \"cat\" \"grep with\" output11.txt" \
    "< special_chars.txt cat | grep with > expected11.txt"

# Test fichier de sortie existant (doit être écrasé)
echo "ancien contenu" > output12.txt
run_test 12 \
    "Écrasement d'un fichier existant" \
    "./pipex test_input.txt \"cat\" \"head -2\" output12.txt" \
    "< test_input.txt cat | head -2 > expected12.txt"

# Test avec beaucoup de données
seq 1 1000 > big_file.txt

run_test 13 \
    "Gros fichier (1000 lignes)" \
    "./pipex big_file.txt \"cat\" \"tail -5\" output13.txt" \
    "< big_file.txt cat | tail -5 > expected13.txt"

run_test 14 \
    "Filtrer et compter sur gros fichier" \
    "./pipex big_file.txt \"grep 5\" \"wc -l\" output14.txt" \
    "< big_file.txt grep 5 | wc -l > expected14.txt"

# ============================================================
# TESTS DE GESTION D'ERREURS
# ============================================================

print_section "TESTS DE GESTION D'ERREURS"

echo -e "${BLUE}Test 15:${NC} Fichier d'entrée inexistant"
echo -e "${CYAN}  Commande: ./pipex fichier_inexistant \"cat\" \"wc -l\" output15.txt${NC}"
./pipex fichier_inexistant.txt "cat" "wc -l" output15.txt 2>/dev/null
# Le shell continue même si le fichier d'entrée n'existe pas
# On vérifie juste que le fichier de sortie est créé
if [ -f output15.txt ]; then
    echo -e "${GREEN}  ✓ RÉUSSI (fichier de sortie créé, comportement normal)${NC}\n"
    TESTS_PASSED=$((TESTS_PASSED + 1))
else
    echo -e "${RED}  ✗ ÉCHOUÉ${NC}\n"
    TESTS_FAILED=$((TESTS_FAILED + 1))
fi
TOTAL_TESTS=$((TOTAL_TESTS + 1))

run_error_test 16 \
    "Commande invalide (cmd2)" \
    "./pipex test_input.txt \"cat\" \"commande_invalide\" output16.txt"

run_error_test 17 \
    "Nombre d'arguments incorrect (trop peu)" \
    "./pipex test_input.txt \"cat\""

run_error_test 18 \
    "Nombre d'arguments incorrect (trop)" \
    "./pipex test_input.txt \"cat\" \"wc\" output.txt extra_arg"

# Test permissions - fichier en lecture seule
touch readonly_file.txt
chmod 000 readonly_file.txt

echo -e "${BLUE}Test 19:${NC} Fichier d'entrée sans permissions de lecture"
echo -e "${CYAN}  Commande: ./pipex readonly_file.txt \"cat\" \"wc -l\" output19.txt${NC}"
./pipex readonly_file.txt "cat" "wc -l" output19.txt 2>/dev/null
if [ $? -ne 0 ] || [ -f output19.txt ]; then
    echo -e "${GREEN}  ✓ RÉUSSI (erreur gérée ou fichier créé)${NC}\n"
    TESTS_PASSED=$((TESTS_PASSED + 1))
else
    echo -e "${RED}  ✗ ÉCHOUÉ${NC}\n"
    TESTS_FAILED=$((TESTS_FAILED + 1))
fi
TOTAL_TESTS=$((TOTAL_TESTS + 1))

chmod 644 readonly_file.txt 2>/dev/null
rm -f readonly_file.txt

# ============================================================
# NETTOYAGE ET RÉSUMÉ
# ============================================================

print_section "NETTOYAGE"
cleanup_test_files

print_summary
