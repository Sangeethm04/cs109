#!/bin/bash

points=0
comments=""

rm -f syscalls.o 1>/dev/null 2>&1
gcc -g -c -Wall -Wextra -Wwrite-strings syscalls.c 1>compileSyscalls.o.out 2>&1
if [ -f "syscalls.o" ]; then
  points=$(( $points + 15 ))
  comments="$comments; syscalls.o created (+15)"
else
  comments="$comments; syscalls.o not created (-15)"
fi

rm -f filePlayFuncs.o 1>/dev/null 2>&1
gcc -g -c -Wall -Wextra -Wwrite-strings filePlayFuncs.c 1>compileFilePlayFuncs.o.out 2>&1 
if [ -f "filePlayFuncs.o" ]; then
  points=$(( $points + 15 ))
  comments="$comments; filePlayFuncs.o created (+15)"
else
  comments="$comments; filePlayFuncs.o not created (-15)"
fi

rm -f filePlay.o 1>/dev/null 2>&1
gcc -g -c -Wall -Wextra -Wwrite-strings filePlay.c 1>compileFilePlay.o.out 2>&1 
if [ -f "filePlay.o" ]; then
  points=$(( $points + 15 ))
  comments="$comments; filePlay.o created (+15)"
else
  comments="$comments; filePlay.o not created (-15)"
fi

rm -f filePlay 1>/dev/null 2>&1 
gcc -g -o filePlay filePlay.o filePlayFuncs.o syscalls.o 1>compileFilePlay.out 2>&1 
if [ -f "filePlay" ]; then
  points=$(( $points + 15 ))
  comments="$comments; filePlay created (+15)"
else
  comments="$comments; filePlay not created (-15)"
fi

./filePlay -a cmdsFile.0 1>/dev/null 2>&1
bytes=$(tail -c +713209 1MBbinaryFile 2>/dev/null | head -c 2)  # have to add 1 to offset!
if [[ "$bytes" == "Co" ]]; then
  points=$(( $points + 40 ))
  comments="$comments; correct bytes written (+40)"
else
  comments="$comments; incorrect or no bytes written (-40)"
fi

echo "Score = $points"
echo "Comments = $comments"
if [[ "$points" -eq 100 ]]; then
  exit 0
else
  exit $points
fi
