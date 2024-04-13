#!/bin/bash

cFile="r0.c"
refLines=30
mg="gcc -Wall -Wextra -Wwrite-strings"
points=0
comment=""
rm -f a.out 2>&1 >/dev/null
rm -f compile.out 2>&1 >/dev/null
if [ -f "$cFile" ]; then
  lines=$(wc -l "$cFile" | awk '{print $1}')
  if [ $lines -le $refLines ]; then
    comment="no substantive work done"
  else
    $mg $cFile 1>compile.out 2>&1
    if [ -f "a.out" ]; then  # no errors
      points=$(( $points + 25 ))
      comment="compiles without errors"
      lines=$(grep -vc ^gcc compile.out)
      if [ $lines -eq 0 ]; then  # no warnings
        points=$(( $points + 20 ))
        comment="$comment; compiles without warnings"
      else
        comment="$comment; compiles with warnings"
      fi
    else
      comment="compile errors"
    fi
  fi
else
  comment="no $cFile file"
fi
echo -e "\nscore: $points, comment: $comment\n"
