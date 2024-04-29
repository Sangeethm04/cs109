#!/bin/bash

unalias -a

points=0
comments=""

hasSocketpair=$(grep ^socketpair: makefile 2>/dev/null | wc -l)
hasSocketpairDoto=$(grep ^socketpair.o: makefile 2>/dev/null | wc -l)
hasSyscallsDoto=$(grep ^syscalls.o: makefile 2>/dev/null | wc -l)
hasClean=$(grep ^clean: makefile 2>/dev/null | wc -l)
if [[ "$hasSocketpair" -eq 1 ]] && [[ "$hasSocketpairDoto" -eq 1 ]] && [[ "$hasSyscallsDoto" -eq 1 ]] && [[ "$hasClean" -eq 1 ]]; then
  comments="makefile has targets of socketpair, socketpair.o, syscalls.o, and clean (+15)"; points=$(( points + 15 ))
else
  comments="makefile does not have targets of socketpair, socketpair.o, syscalls.o, and/or clean (-99)"
  echo "Score: 1, Comments: $comments"
  exit 1
fi
make clean 2>/dev/null
if [ -f "socketpair" ] || [ -f "socketpair.o" ] || [ -f "syscalls.o" ]; then
  comments="$comments; 'make clean' did not remove socketpair, socketpair.o, and/or syscalls.o (-5)"
  rm -f socketpair socketpair.o syscalls.o 1>/dev/null 2>&1
else
  comments="$comments; 'make clean' removed socketpair, socketpair.o, and syscalls.o (+5)"; points=$(( points + 5 ))
fi
make 1>|compile.out 2>&1
if [ -f "socketpair" ]; then  # if compiles w/o errors
  comments="$comments; compiles w/o errors (+30)"
  points=$(( points + 30 ))
  bytes=$(grep -v ^g++ compile.out 2>/dev/null| wc -c)
  if [[ "$bytes" -eq 0 ]]; then  # if compiles w/o warnings
    comments="$comments; compiles w/o warnings (+10)"; points=$(( points + 10 ))
  else
    comments="$comments; compile w/ warnings (-10)"
  fi
  hasFopen=$(grep -E "^\s*FILE\s*\*\s*Fopen\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasFread=$(grep -E "^\s*size_t\s*Fread\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasFwrite=$(grep -E "^\s*size_t\s*Fwrite\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasFseek=$(grep -E "^\s*int\s*Fseek\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasFtell=$(grep -E "^\s*long\s*Ftell\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasFclose=$(grep -E "^\s*(int|void)\s*Fclose\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasOpenDir=$(grep -E "^\s*DIR\s*\*\s*Opendir\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasReadDir=$(grep -E "^\s*struct\s*dirent\s*\*\s*Readdir\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasCloseDir=$(grep -E "^\s*(int|void)\s*Closedir\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasMalloc=$(grep -E "^\s*void\s*\*\s*Malloc\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasSystem=$(grep -E "^\s*int\s*System\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasNanosleep=$(grep -E "^\s*(int|void)\s*Nanosleep\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasFork=$(grep -E "^\s*pid_t\s*Fork\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasSocketpair=$(grep -E "^\s*(int|void)\s*Socketpair\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasWait=$(grep -E "^\s*pid_t\s*Wait\s*\(" syscalls.h 2>/dev/null | wc -l)
  if [[ "$hasFopen" -eq 1 ]] && [[ "$hasFread" -eq 1 ]] && [[ "$hasFwrite" -eq 1 ]] && \
     [[ "$hasFseek" -eq 1 ]] && [[ "$hasFtell" -eq 1 ]] && [[ "$hasFclose" -eq 1 ]] && \
     [[ "$hasOpenDir" -eq 1 ]] && [[ "$hasReadDir" -eq 1 ]] && [[ "$hasCloseDir" -eq 1 ]] && \
     [[ "$hasMalloc" -eq 1 ]] && [[ "$hasSystem" -eq 1 ]] && [[ "$hasSocketpair" -eq 1 ]] && \
     [[ "$hasWait" -eq 1 ]] && [[ "$hasNanosleep" -eq 1 ]] && [[ "$hasFork" -eq 1 ]]; then
    comments="$comments; syscalls.h has all the required prototypes (+10)"; points=$(( points + 10 ))
  else
    comments="$comments; syscalls.h missing one or more required prototypes; look at grade.sh to see what's expected (-10)"
  fi
  if [ -f socketpair.cpp ]; then
    hasPrintf=$(grep -E "printf\s*\(" socketpair.cpp 2>/dev/null | wc -l)
    if [[ "$hasPrintf" -eq 0 ]]; then 
      comments="$comments; socketpair.cpp has 0 calls to [f]printf (+10)"; points=$(( points + 10 ))
    else
      comments="$comments; socketpair.cpp has 1 or more calls to [f]printf (-10)"
    fi
    callsFork=$(grep -E "Fork\s*\(" socketpair.cpp 2>/dev/null | wc -l)
    callsSocketpair=$(grep -E "Socketpair\s*\(" socketpair.cpp 2>/dev/null | wc -l)
    callsWait=$(grep -E "Wait\s*\(" socketpair.cpp 2>/dev/null | wc -l)
    callsRead=$(grep -E "Read\s*\(" socketpair.cpp 2>/dev/null | wc -l)
    callsWrite=$(grep -E "Write\s*\(" socketpair.cpp 2>/dev/null | wc -l)
    if [[ "$callsFork" -gt 0 ]] && [[ "$callsSocketpair" -gt 0 ]] &&[[ "$callsWait" -gt 0 ]] &&[[ "$callsRead" -gt 0 ]] &&   [[ "$callsWrite" -gt 0 ]]; then
      comments="$comments; socketpair.cpp calls Fork, Socketpair, Wait, Read, and Write (+10)"; points=$(( points + 10 ))
    else
      comments="$comments; socketpair.cpp does not call Fork, Socketpair, Wait, Read, and/or Write (-10)"
    fi
    pid=$$
    ./socketpair 1>|my.out
    checkParent=$(grep -E "\s*parent:\s*decrypted\s*message\s*=>\s*'Professor Erle has a \"MOM\" tattoo and wears a wig.'" my.out 2>/dev/null | wc -l)
    checkChild=$(grep -E "\s*child:\s*decrypted\s*reply\s*=>\s*'That doesn't surprise me!'" my.out 2>/dev/null | wc -l)
    # parent: decrypted message          => 'Professor Erle has a "MOM" tattoo and wears a wig.'
    # child:  decrypted reply            => 'That doesn't surprise me!'
    if [[ "$checkParent" -eq 1 ]]; then
      comments="$comments; correct parent message (+5)"; points=$(( points + 5 ))
    else
      comments="$comments; incorrect parent message (-5)"
    fi
    if [[ "$checkChild" -eq 1 ]]; then
      comments="$comments; correct child reply (+5)"; points=$(( points + 5 ))
    else
      comments="$comments; incorrect child reply (-5)"
    fi
  else
    comments="$comments; expecting socketpair.cpp (-10)"
  fi
else
  comments="$comments; compiles w/ errors (-97)"
  echo "Score: 3, Comments: $comments"
  exit 3
fi
echo "Score: $points, Comments: $comments"
if [[ "$points" -eq 100 ]]; then
  exit 0
else
  exit $points
fi
