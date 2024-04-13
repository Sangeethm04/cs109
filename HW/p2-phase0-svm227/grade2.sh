#!/bin/bash

points=0
comments=""

dir=$(pwd)
if [ -f "makefile" ] || [ -f "Makefile" ]; then  # 5 points possible
  comments="makefile or Makefile found (+5)"
  if [ -f "makefile" ]; then
    mFile="makefile"; points=$(( $points + 5 ))
  else
    mFile="Makefile"
  fi
  rc=$(grep -c -- -Wall $mFile)
  rc1=$(grep -c -- -Wextra $mFile)
  rc2=$(grep -c -- -Wwrite-strings $mFile)
  rc=$(( $rc + $rc1 + $rc2 ))
  if [[ "$rc" -eq 3 ]]; then   # 5 
    comments="$comments: -Wall, -Wextra, -Wwrite-strings used in make (+5)"; points=$(( $points + 5 ))
  else 
    comments="$comments: -Wall, -Wextra, -Wwrite-strings not all used in make (-5)"
  fi
  make clean 1>/dev/null 2>&1
  if [ -f "syscalls.o" ] || [ -f "filePlayFuncs.o" ] || [ -f "filePlay.o" ] || [ -f "filePlay" ]; then   # 5
    comments="$comments; 'make clean' did not remove all .o files or filePlay (-5)"
    rm -f syscalls.o filePlayFuncs.o filePlay.o filePlay 1>/dev/null 2>&1
  else
    comments="$comments; 'make clean' removed all .o files and filePlay (+5)"; points=$(( $points + 5 ))
  fi
  rm -f compile.out 1>/dev/null 2>&1
  for file in "syscalls.o" "filePlayFuncs.o" "filePlay.o" "filePlay"; do  #  5 * 4 = 20
    make $file 1>>compile.out 2>&1
    if [ -f "$file" ]; then
      comments="$comments; $file created from make (+5)"; points=$(( $points + 5 ))
    else
      comments="$comments; $file not created from make (-5)"
    fi
  done
else  # no makefile was found
  comments="neither makefile nor Makefile found (-74)"
  echo -e "\nscore: $dir - 1 comments: Bummer! $comments\n"; exit 1
fi
if [ -f "filePlay" ]; then   # 5
  comments="$comments; compiles (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; compiles (-5)"
fi
lines=$(grep -vc ^gcc compile.out)
if [ $lines -eq 0 ]; then  # no warnings   5
  comments="$comments; compiles without warnings (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; compiles with warnings (-5)"
fi

# 50 points from above, 25 points from below
for testNum in {0..7..1}; do
  rm -f test.out test.err 1>/dev/null 2>&1 
  if   [[ "$testNum" -eq 0 ]]; then
    ./filePlay -a 1>test.out 2>test.err; rc=$?
  elif [[ "$testNum" -eq 1 ]]; then
    ./filePlay -x cmdsFile.0 1>test.out 2>test.err; rc=$?
  elif [[ "$testNum" -eq 2 ]]; then
    ./filePlay -a missingFile 1>test.out 2>test.err; rc=$?
  elif [[ "$testNum" -eq 3 ]]; then
    ./filePlay -a cmdsFile.0 1>test.out 2>test.err; rc=$?
  elif [[ "$testNum" -eq 4 ]]; then
    ./filePlay -U cmdsFile.1 1>test.out 2>test.err; rc=$?
  elif [[ "$testNum" -eq 5 ]]; then
    ./filePlay -L cmdsFile.2 1>test.out 2>test.err; rc=$?
  elif [[ "$testNum" -eq 6 ]]; then
    ./filePlay -A cmdsFile.all 1>test.out 2>test.err; rc=$?
  elif [[ "$testNum" -eq 7 ]]; then
    rm -f 1MBbinaryFile.test 1>/dev/null 2>&1
    head -c 1M </dev/urandom > 1MBbinaryFile.test
    ./filePlay -U cmdsFile.all 1MBbinaryFile.test 1>test.out 2>test.err; rc=$?
  fi
  wco=$(wc -c "test.out" | awk '{print $1}')
  wce=$(wc -c "test.err" | awk '{print $1}')
  if [[ "$testNum" -le 2 ]]; then  # the first 3 tests should fail
    if [[ "$rc" -ne 0 ]]; then
      comments="$comments; test $testNum rc != 0 (+1)"; points=$(( $points + 1 ))
    else
      comments="$comments; test $testNum rc == 0 (-1)"
    fi
    if [[ "$wco" -eq 0 ]] && [[ "$wce" -gt 0 ]]; then
      comments="$comments; stdout empty and stderr nonempty (+1)"; points=$(( $points + 1 ))
    else
      comments="$comments; stdout nonempty or stderr empty (-1)"
    fi
  fi
  if [[ "$testNum" -ge 3 ]]; then
    if [[ "$rc" -eq 0 ]]; then
      comments="$comments; test $testNum rc == 0 (+1)"; points=$(( $points + 1 ))
    else
      comments="$comments; test $testNum rc != 0 (-1)"
    fi
    if [[ "$testNum" -eq 3 ]]; then
      bytes=$(tail -c +713209 1MBbinaryFile 2>/dev/null | head -c 2)  # have to add 1 to offset!
      if [[ "$bytes" == "Co" ]]; then
        comments="$comments; test $testNum 'Co' written (+2)"; points=$(( $points + 2 ))
      else
        comments="$comments; test $testNum 'Co' not written (-2)"
      fi
    fi
    if [[ "$testNum" -eq 4 ]]; then  # valid seeks from beginning and end
      bytes=$(tail -c +435363 1MBbinaryFile 2>/dev/null | head -c 2)  # have to add 1 to offset!
      if [[ "$bytes" == "rp" ]]; then
        comments="$comments; test $testNum 'rp' written (+2)"; points=$(( $points + 2 ))
      else
        comments="$comments; test $testNum 'rp' not written (-2)"
      fi
    fi
    if [[ "$testNum" -eq 5 ]]; then  # invalid seeks in between write of 'Co' and 'rp'
      bytes=$(tail -c +435363 1MBbinaryFile 2>/dev/null | head -c 2)  # have to add 1 to offset!
      if [[ "$bytes" == "rp" ]]; then
        comments="$comments; test $testNum 'rp' written (+2)"; points=$(( $points + 2 ))
      else
        comments="$comments; test $testNum 'rp' not written (-2)"
      fi
    fi 
    if [[ "testNum" -eq 6 ]]; then
      count=$(grep -c "Codee says..." test.out)
      count1=$(grep -c "Carpe proelium!" test.out)
      count2=$(grep -c "Be the change!" test.out)
      count3=$(grep -c "Code is love!" test.out)
      count=$(( $count + $count1 + $count2 + $count3 ))
      if [[ "$count" -eq 4 ]]; then
        comments="$comments; -A cmdsFile.all msgs are correct! (+4)"; points=$(( $points + 4 ))
      else
        pointsOff=$(( 4 - $count ))
        comments="$comments; -A cmdsFile.all msgs not all right (-$pointsOff)"; points=$(( $points + $count ))
      fi
    fi
    if [[ "testNum" -eq 7 ]]; then
      count=$(grep -c "CODEE SAYS..." test.out)
      count1=$(grep -c "CARPE PROELIUM!" test.out)
      count2=$(grep -c "BE THE CHANGE!" test.out)
      count3=$(grep -c "CODE IS LOVE!" test.out)
      count=$(( $count + $count1 + $count2 + $count3 ))
      if [[ "$count" -eq 4 ]]; then
        comments="$comments; -U cmdsFile.all msgs are correct! (+4)"; points=$(( $points + 4 ))
      else
        pointsOff=$(( 4 - $count ))
        comments="$comments; -U cmdsFile.all msgs not all right (-$pointsOff)"; points=$(( $points + $count ))
      fi
    fi
  fi
  testNum=$(( $testNum + 1 ))
done
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all filePlay -a cmdsFile.all 1>valgrind.out 2>&1
bytes=$(grep "definitely lost:" valgrind.out | awk '{print $4}')
if [[ "$bytes" -eq 0 ]]; then
  comments="$comments; valgrind clean! (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; valgrind fails (-5)"
fi
rm -f 1MBbinaryFile 1>/dev/null 2>&1
rm -f 1MBbinaryFile.test 1>/dev/null 2>&1
if [[ "$points" -eq 75 ]]; then
  echo -e "\nscore: $dir - $points comments: Great job! $comments\n"; exit 0
elif [[ $points -ge 65 ]]; then
  echo -e "\nscore: $dir - $points comments: Good job! $comments\n"; exit $points
else
  echo -e "\nscore: $dir - $points comments: $comments\n"; exit $points
fi
