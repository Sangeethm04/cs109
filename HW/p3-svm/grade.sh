#!/bin/bash

unalias -a

points=0
comments=""

make clean 1>/dev/null 2>&1
if [ -f "syscalls.o" ] || [ -f "cIncludesFuncs.o" ] || [ -f "cIncludes.o" ] || [ -f "cIncludes" ]; then
  comments="'make clean' did not remove all .o files and/or cIncludes (-10)"
  rm -f *.o cIncludes 1>/dev/null 2>&1
else
  comments="'make clean' worked (+10)"; points=$(( $points + 10 ))
fi

make cIncludes 1>compile.out 2>&1
#touch syscalls.o cIncludesFuncs.o  # uncomment when DE is testing
if [ -f "syscalls.o" ] && [ -f "cIncludesFuncs.o" ] && [ -f "cIncludes.o" ]; then
  comments="$comments; 'make cIncludes' generated the 3 .o files (+10)"; points=$(( $points + 10 ))
else
  comments="$comments; 'make cIncludes' did not generate the 3 .o files (-10)"
fi

if [ -f "cIncludes" ]; then
  comments="$comments; 'make cIncludes' generated cIncludes file (+10)"; points=$(( $points + 10 ))
else
  comments="$comments; 'make cIncludes' did not generate cIncludes (-10)"
  echo "Score = $points"
  echo "Comments = $comments"
  exit $points
fi

lines=$(grep -vc ^gcc compile.out)
if [ $lines -eq 0 ]; then  # no warnings   5
  comments="$comments; compiles without warnings (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; compiles with warnings (-5)"
fi

# Test 0
# expecting nothing printed to stdout, an error message printed to stderr, and a nonzero return code
rm -f test0.out test0.err 2>&1 1>/dev/null
./cIncludes -nd . 1>test0.out 2>test0.err
rc=$?
wco=$(wc -c "test0.out" | awk '{print $1}')
wce=$(wc -c "test0.err" | awk '{print $1}')
if [[ "$wco" -eq 0 ]] && [[ "$wce" -gt 0 ]] && [[ "$rc" -ne 0 ]]; then
  comments="$comments; test0: './cIncludes -x .' generates error msg and exits with nonzero rc (+5)"; points=$(( $points + 5 ))
else 
  comments="$comments; test0: './cIncludes -x .' does not generate error msg or exits with 0 rc (-5)"
fi

# 40 points max at this point

# Test 1
rm -f tmp.h 2>&1 1>/dev/null
rm -f test1.out test1.diff 2>&1 1>/dev/null
cat <<EOF >tmp.h
line1
line2
#inc <no>
#include "local.h"
#include"local.h"
#include <remote.h>"
#include<remote.h>"
#include "count this one too!"
#include and this one!
EOF
./cIncludes -d tmp.h 1>test1.out 2>/dev/null
pwd=$(pwd)
diff test1.out <(echo "$pwd/tmp.h:6") 2>&1 1>test1.diff
rc=$?
if [[ "$rc" -eq 0 ]]; then
  comments="$comments; test1: './cIncludes -d tmp.h' matches expectation (+5)"; points=$(( $points + 5 ))
else 
  comments="$comments; test1: './cIncludes -d tmp.h' does not match expectation (-5)"
fi

# Test 2
rm -rf test2dir.h 2>&1 1>/dev/null
rm -f test2.out test2.diff 2>&1 1>/dev/null
mkdir test2dir.h
cat <<EOF >test2dir.h/tmp.h
line1
line2
#inc <no>
#include <remote.h>"
#include "count this one too!"
#include and this one!
EOF
cat <<EOF >test2dir.h/tmp.x
/* this file should be ignored! */
line1
line2
#include "local.h"
#include and this one!
EOF
./cIncludes -d test2dir.h 1>test2.out 2>/dev/null
pwd=$(pwd) 
diff test2.out <(echo "$pwd/test2dir.h/tmp.h:3") 2>&1 1>test2.diff
rc=$?
if [[ "$rc" -eq 0 ]]; then
  comments="$comments; test2: './cIncludes -d test2dir.h' matches expectation (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; test2: './cIncludes -d test2dir.h' does not match expectation (-5)"
fi

# 50 points max at this point
# Test 3
rm -f test3.out test3.diff 2>&1 1>/dev/null
./cIncludes -d /usr/include/video 1>test3.out 2>/dev/null
diff test3.out video.dictFwd.ref 2>&1 1>test3.diff
rc=$?
if [[ "$rc" -eq 0 ]]; then
  comments="$comments; test3: './cIncludes -d /usr/include/video' matches expectation (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; test3: './cIncludes -d /usr/include/video' does not match expectation (-5)"
fi

# Test 4
rm -f test4.out test4.diff 2>&1 1>/dev/null
./cIncludes -dr /usr/include/video 1>test4.out 2>/dev/null
diff test4.out video.dictRev.ref 2>&1 1>test4.diff
rc=$?
if [[ "$rc" -eq 0 ]]; then
  comments="$comments; test4: './cIncludes -dr /usr/include/video' matches expectation (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; test4: './cIncludes -dr /usr/include/video' does not match expectation (-5)"
fi

# Test 5
rm -f test5.out test5.diff 2>&1 1>/dev/null
./cIncludes -n /usr/include/video 1>test5.out 2>/dev/null
diff test5.out video.numFwd.ref 2>&1 1>test5.diff
rc=$?
if [[ "$rc" -eq 0 ]]; then
  comments="$comments; test5: './cIncludes -n /usr/include/video' matches expectation (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; test5: './cIncludes -n /usr/include/video' does not match expectation (-5)"
fi

# Test 6
rm -f test6.out test6.diff 2>&1 1>/dev/null
./cIncludes -nr /usr/include/video 1>test6.out 2>/dev/null
diff test6.out video.numRev.ref 2>&1 1>test6.diff
rc=$?
if [[ "$rc" -eq 0 ]]; then
  comments="$comments; test6: './cIncludes -nr /usr/include/video' matches expectation (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; test6: './cIncludes -nr /usr/include/video' does not match expectation (-5)"
fi

# Test 7
rm -f test7.out test7.diff 2>&1 1>/dev/null
./cIncludes -nro /usr/include/clang/ASTMatchers 1>test7.out 2>/dev/null
diff test7.out ASTMatchers.numRevOnly.ref 2>&1 1>test7.diff
rc=$?
if [[ "$rc" -eq 0 ]]; then
  comments="$comments; test7: './cIncludes -nro /usr/include/clang/ASTMatchers' matches expectation (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; test7: './cIncludes -nro /usr/include/clang/ASTMatchers' does not match expectation (-5)"
fi

echo "Score = $points"
if [[ "$points" -eq 75 ]]; then
  echo "Comments = Great job! $comments"
  exit 0
elif [[ "$points" -eq 70 ]]; then
  echo "Comments = Good job! $comments"
else
  echo "Comments = $comments"
fi
exit $points
