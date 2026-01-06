#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Compile
echo -e "${YELLOW}Compilation...${NC}"
make re
if [ $? -ne 0 ]; then
    echo -e "${RED}Erreur de compilation${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Compilation réussie${NC}\n"

# Créer fichier de test
cat > test_input.txt << EOF
bonjour tout le monde
ceci est un test
avec plusieurs lignes
pour tester pipex
un autre test
EOF

echo -e "${YELLOW}=== Tests basiques ===${NC}\n"

# Test 1: grep et wc
echo "Test 1: grep + wc -l"
./pipex test_input.txt "grep test" "wc -l" output1.txt
< test_input.txt grep test | wc -l > expected1.txt
if diff output1.txt expected1.txt > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Test 1 réussi${NC}"
else
    echo -e "${RED}✗ Test 1 échoué${NC}"
    echo "Attendu:"
    cat expected1.txt
    echo "Obtenu:"
    cat output1.txt
fi

# Test 2: cat et grep
echo "Test 2: cat + grep"
./pipex test_input.txt "cat" "grep test" output2.txt
< test_input.txt cat | grep test > expected2.txt
if diff output2.txt expected2.txt > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Test 2 réussi${NC}"
else
    echo -e "${RED}✗ Test 2 échoué${NC}"
fi

# Test 3: ls et grep
echo "Test 3: ls + grep"
./pipex test_input.txt "ls -l" "grep pipex" output3.txt
< test_input.txt ls -l | grep pipex > expected3.txt
if diff output3.txt expected3.txt > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Test 3 réussi${NC}"
else
    echo -e "${RED}✗ Test 3 échoué${NC}"
fi

# Test 4: head et tail
echo "Test 4: head + tail"
./pipex test_input.txt "head -3" "tail -2" output4.txt
< test_input.txt head -3 | tail -2 > expected4.txt
if diff output4.txt expected4.txt > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Test 4 réussi${NC}"
else
    echo -e "${RED}✗ Test 4 échoué${NC}"
fi

# Test 5: sort et uniq
echo "Test 5: sort + uniq"
./pipex test_input.txt "cat" "sort" output5.txt
< test_input.txt cat | sort > expected5.txt
if diff output5.txt expected5.txt > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Test 5 réussi${NC}"
else
    echo -e "${RED}✗ Test 5 échoué${NC}"
fi

echo -e "\n${YELLOW}=== Tests d'erreurs ===${NC}\n"

# Test 6: Fichier d'entrée inexistant
echo "Test 6: Fichier inexistant"
./pipex fichier_qui_nexiste_pas.txt "cat" "wc -l" output6.txt 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ Test 6 réussi (erreur détectée)${NC}"
else
    echo -e "${RED}✗ Test 6 échoué (devrait échouer)${NC}"
fi

# Test 7: Commande invalide
echo "Test 7: Commande invalide"
./pipex test_input.txt "commande_invalide" "wc -l" output7.txt 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ Test 7 réussi (erreur détectée)${NC}"
else
    echo -e "${RED}✗ Test 7 échoué (devrait échouer)${NC}"
fi

# Test 8: Mauvais nombre d'arguments
echo "Test 8: Mauvais arguments"
./pipex test_input.txt "cat" 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ Test 8 réussi (erreur détectée)${NC}"
else
    echo -e "${RED}✗ Test 8 échoué (devrait échouer)${NC}"
fi

echo -e "\n${YELLOW}=== Nettoyage ===${NC}"
rm -f test_input.txt output*.txt expected*.txt
echo -e "${GREEN}Fichiers de test supprimés${NC}"

echo -e "\n${GREEN}Tests terminés !${NC}"
