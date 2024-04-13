#!/bin/bash

points=0
comments=""

make clean
make 1>|compile.out 2>&1 
if [ -f "malloc" ]; then  # if compiles w/o errors
  comments="$comments; compiles w/o errors (+60)"
  points=$(( points + 60 ))
  bytes=$(cat compile.out | grep -v ^gcc | wc -c)
  if [[ "$bytes" -eq 0 ]]; then  # if compiles w/o warnings
    points=$(( points + 30 ))
    comments="$comments; compiles w/o warnings (+30)"
  else
    comments="$comments; compile w/ warnings (-30)"
  fi
  pid=$$
  ./malloc 1>|/tmp/malloc.out.$pid 2>&1 
  lines=$(cat /tmp/malloc.out.$pid | wc -l)
  if [[ "$lines" -gt 0 ]]; then  # if print statement added to loop body
    points=$(( points + 10 ))
    comments="$comments; added print statements to loop body (+10)"
  else
    comments="$comments; did not add print statements to loop body (-10)"
  fi
else
  comments="$comments; compiles w/ errors (-100)"
fi
echo "Score: $points, Comments: $comments"
if [[ "$points" -eq 100 ]]; then
  exit 0
else
  exit $points
fi
