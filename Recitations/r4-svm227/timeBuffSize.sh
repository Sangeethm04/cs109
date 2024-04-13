#!/bin/bash

if [ ! -f 1MBfile.in ]; then
  echo "Score: 0, Comments: no 1MBfile.in test file found"
  exit 99
fi
points=0
comments=""
size=1
clock_tCheck=1
while true; do  # loop will run 18 times
  make clean
  make BUFFSIZE=$size 2>&1 1>| compile.out
  if [ -f buffSize ]; then  # if compiles w/o errors, total of 36 points
    points=$(( points + 2 ))
    comments="$comments; compiles w/o errors"
    bytes=$(cat compile.out | grep -v ^gcc | wc -c)
    if [[ "$bytes" -eq 0 ]]; then  # if compiles w/o warnings, total of 18 points
      points=$(( points + 1 ))
      comments="$comments; compiles w/o warnings"
    else
      comments="$comments; compile warnings (-1)"
    fi
    ./buffSize < 1MBfile.in >| 1MBfile.out
    diff 1MBfile.in 1MBfile.out >/dev/null 2>&1
    rc=$?
    if [[ "$rc" -eq 0 ]]; then
      points=$(( points + 2 ))  # if creates 1MBfile.out correctly, total of 36 points
      comments="$comments; created 1MBfile.out correctly"
    else
      comments="$comments; 1MBfile.out not correct (-2)"
    fi
    clock_tInstances=$(grep "clock_t" buffSize.c | wc -l)
    if [[ "$clock_tCheck" -eq 1 ]]; then
      clock_tCheck=0
      if [[ "$clock_tInstances" -ge 3 ]]; then
        points=$(( points + 10 ))  # if at least two variables declared, 10 points
        comments="$comments; declared at least 2 clock_t variables"
      else
        comments="$comments; did not declare at least 2 clock_t variables"
      fi
    fi
    size=$(( size * 2 ))
    if [ $size -gt 131072 ]; then
      break
    fi
  else
    comments="$comments; compile errors (-2)"
  fi
done
echo "Score: $points, Comments: $comments"
if [[ "$points" -eq 100 ]]; then
  exit 0
else
  exit $points
fi
