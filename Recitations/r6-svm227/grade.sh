#!/bin/bash

unalias -a

points=0
comments=""

hasPipe=$(grep ^pipe: makefile 2>/dev/null | wc -l)
hasPipeDoto=$(grep ^pipe.o: makefile 2>/dev/null | wc -l)
hasSyscallsDoto=$(grep ^syscalls.o: makefile 2>/dev/null | wc -l)
hasClean=$(grep ^clean: makefile 2>/dev/null | wc -l)
if [[ "$hasPipe" -eq 1 ]] && [[ "$hasPipeDoto" -eq 1 ]] && [[ "$hasSyscallsDoto" -eq 1 ]] && [[ "$hasClean" -eq 1 ]]; then
  comments="makefile has targets of pipe, pipe.o, syscalls.o, and clean (+15)"; points=$(( points + 15 ))
else
  comments="makefile does not have targets of pipe, pipe.o, syscalls.o, and/or clean (-99)"
  exit 1
fi
make clean 2>/dev/null
if [ -f "pipe" ] || [ -f "pipe.o" ] || [ -f "syscalls.o" ]; then
  comments="$comments; 'make clean' did not remove pipe, pipe.o, and/or syscalls.o (-5)"
  rm -f pipe pipe.o syscalls.o 1>/dev/null 2>&1
else
  comments="$comments; 'make clean' removed pipe, pipe.o, and syscalls.o (+5)"; points=$(( points + 5 ))
fi
make 1>|compile.out 2>&1
if [ -f "pipe" ]; then  # if compiles w/o errors
  comments="$comments; compiles w/o errors (+30)"
  points=$(( points + 30 ))
  bytes=$(grep -v ^gcc compile.out 2>/dev/null| wc -c)
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
  hasPipe=$(grep -E "^\s*(int|void)\s*Pipe\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasNanosleep=$(grep -E "^\s*(int|void)\s*Nanosleep\s*\(" syscalls.h 2>/dev/null | wc -l)
  hasFork=$(grep -E "^\s*pid_t\s*Fork\s*\(" syscalls.h 2>/dev/null | wc -l)
  if [[ "$hasFopen" -eq 1 ]] && [[ "$hasFread" -eq 1 ]] && [[ "$hasFwrite" -eq 1 ]] && \
     [[ "$hasFseek" -eq 1 ]] && [[ "$hasFtell" -eq 1 ]] && [[ "$hasFclose" -eq 1 ]] && \
     [[ "$hasOpenDir" -eq 1 ]] && [[ "$hasReadDir" -eq 1 ]] && [[ "$hasCloseDir" -eq 1 ]] && \
     [[ "$hasMalloc" -eq 1 ]] && [[ "$hasSystem" -eq 1 ]] && [[ "$hasPipe" -eq 1 ]] && \
     [[ "$hasNanosleep" -eq 1 ]] && [[ "$hasFork" -eq 1 ]]; then
    comments="$comments; syscalls.h has all the required prototypes (+20)"; points=$(( points + 20 ))
  else
    comments="$comments; syscalls.h missing one or more required prototypes (-20)"
  fi
  callsFork=$(grep -E "Fork\s*\(" pipe.c 2>/dev/null | wc -l)
  callsRead=$(grep -E "Read\s*\(" pipe.c 2>/dev/null | wc -l)
  callsWrite=$(grep -E "Write\s*\(" pipe.c 2>/dev/null | wc -l)
  if [[ "$callsFork" -gt 0 ]] && [[ "$callsRead" -gt 0 ]] && [[ "$callsWrite" -gt 0 ]]; then
    comments="$comments; pipe.c calls Fork, Read, and Write (+10)"; points=$(( points + 10 ))
  else
    comments="$comments; pipe.c does not call Fork, Read, and/or Write (-10)"
  fi
  pid=$$
  { time ./pipe; } 2>/tmp/time.out.$pid
  checkTime=$(grep ^real /tmp/time.out.$pid 2>/dev/null | grep 9.5 | wc -l)
  if [[ "$checkTime" -eq 1 ]]; then
    comments="$comments; pipe slept for 9.5s (+10)"; points=$(( points + 10 ))
  else
    comments="$comments; pipe did not sleep for 9.5s (-10)"
  fi
else
  comments="$comments; compiles w/ errors (-97)"
  exit 3
fi
echo "Score: $points, Comments: $comments"
if [[ "$points" -eq 100 ]]; then
  exit 0
else
  exit $points
fi
