#!/bin/bash

GREEN="\033[38;2;57;181;74m"
RED="\033[38;2;222;56;43m"
BLUE="\033[38;2;34;183;235m"
RESET="\033[0m"

printf "${BLUE}Running real command : < $1 $2 | $3 > $4_real$RESET\n"
< $1 $2 | $3 > $4_real
REAL_EXIT=$?

printf "${BLUE}Running my command   : ./pipex $1 \"$2\" \"$3\" $4_mine$RESET\n"
./pipex $1 "$2" "$3" $4_mine
MINE_EXIT=$?

echo ""

printf "${BLUE}Exit code of real command:$RESET\n"
echo "$REAL_EXIT"
printf "${BLUE}Exit code of my command:$RESET\n"
echo "$MINE_EXIT"

printf "\n${BLUE}cat -e of $4_real$RESET\n"
cat -e $4_real
printf "${BLUE}cat -e of $4_mine$RESET\n"
cat -e $4_mine

printf "\n${BLUE}ls -l out_*$RESET\n"
ls -l out_*


