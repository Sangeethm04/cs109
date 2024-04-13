#!/bin/bash

cFile="add2floats.c"
xFile="add2floats"
refLines=50
mg="gcc -o $xFile -Wall -Wextra -Wwrite-strings"
points=0
comment=""
rm -f $xFile 2>&1 >/dev/null
rm -f compile.out 2>&1 >/dev/null
if [ -f "$cFile" ]; then
  lines=$(wc -l "$cFile" | awk '{print $1}')
  if [ $lines -le $refLines ]; then
    comment="(-100) no substantive work done"
  else
    $mg $cFile 1>compile.out 2>&1
    if [ -f "$xFile" ]; then  # no errors
      points=$(( $points + 25 ))
      comment="compiles without errors"
      lines=$(grep -vc ^gcc compile.out)
      if [ $lines -eq 0 ]; then  # no warnings
        points=$(( $points + 20 ))
        comment="$comment; compiles without warnings"
      else
        comment="$comment; (-20) compiles with warnings"
      fi
      # following is unique to add2floats (r3)
      ./add2floats 1>/dev/null 2>&1  # expecting rc 99
      rc=$?
      if [[ "$rc" -eq 99 ]]; then
        points=$(( $points + 10 ))
        comment="$comment; wrong # of args returns 99"
      else
        comment="$comment; (-10) wrong # of args returns $rc instead of 99"
      fi
      ./add2floats -r 1.0 1.0 1>/dev/null 2>&1  # expecting rc 97
      rc=$?
      if [[ "$rc" -eq 97 ]]; then
        points=$(( $points + 10 ))
        comment="$comment; invalid mode returns 97"
      else
        comment="$comment; (-10) invalid mode returns $rc instead of 97"
      fi
      ./add2floats -x 3f800000 BF80000z 1>/dev/null 2>&1  # expecting rc 98
      rc=$?
      if [[ "$rc" -eq 98 ]]; then
        points=$(( $points + 10 ))
        comment="$comment; invalid hex returns 98"
      else
        comment="$comment; (-10) invalid hex returns $rc instead of 98"
      fi
      line=$(./add2floats -X 3f800000 BF800000 2>/dev/null)  # expecting rc 0
      rc=$?
      if [[ "$rc" -eq 0 ]]; then
        points=$(( $points + 10 ))
        comment="$comment; valid input returns 0"
      else
        comment="$comment; (-10) valid input returns $rc instead of 0"
      fi
      if [[ $line == "1.000000e+00 + -1.000000e+00 = 0.000000e+00" ]]; then
        points=$(( $points + 15 ))
        comment="$comment; valid input yields '1.000000e+00 + -1.000000e+00 = 0.000000e+00'"
      else
        comment="$comment; (-15) valid input does not yield '1.000000e+00 + -1.000000e+00 = 0.000000e+00'"
      fi
    else
      comment="(-100) compile errors"
    fi
  fi
else
  comment="(-100) no $cFile file"
fi
echo -e "\nscore: $points, comment: $comment\n"
exit $points
