#!/bin/bash

points=0
comments=""

make clean 1>/dev/null 2>&1
if [ -f "procInfo" ]; then 
  comments="'make clean' did not remove all .o files and/or procInfo (-5)"
  rm -f *.o procInfo 1>/dev/null 2>&1
else
  comments="'make clean' worked (+5)"; points=$(( $points + 5 ))
fi

numPrintfs=$(grep -c printf *.cpp | grep -E -v '(sprintf|snprintf)' | awk 'BEGIN {FS=":"} $2 > 0 {print $0}' | wc -l)
if [[ "$numPrintfs" -eq 0 ]]; then
  comments="$comments; no .cpp files using printf (+10)"; points=$(( $points + 10 ))
else
  comments="$comments; 1 or more .cpp files using printf (-10)"
fi

# friend ostream & operator  <<(
overLoad=$(grep -c "friend[[:blank:]]\+ostream[[:blank:]]\+&[[:blank:]]\+operator[[:blank:]]\+<<" *.cpp | awk 'BEGIN {FS=":"} $2 > 0 {print $0}' | wc -l)
if [[ "$overLoad" -gt 0 ]]; then
  comments="$comments; found overloaded insertion operator (+10)"; points=$(( $points + 10 ))
else
  comments="$comments; overloaded insertion operator not found (-10)"
fi

make procInfo 1>compile.out 2>&1
#touch procInfo  # uncomment for testing purposes
if [ -f "procInfo" ]; then
  comments="$comments; 'make procInfo' worked (+20)"; points=$(( $points + 20 ))
else
  comments="$comments; 'make procInfo' did not generate procInfo (-20)"
fi

lines=$(grep -vc ^g++ compile.out)  
if [ $lines -eq 0 ]; then  # no warnings   5
  comments="$comments; compiles without warnings (+5)"; points=$(( $points + 5 ))
else
  comments="$comments; compiles with warnings (-5)"
fi

# 50 points max thus far

# test of searching for a pid that does not exist
currProcInfo=$(./procInfo 9999999 1>|/tmp/tmp.out.$$ 2>|/tmp/tmp.err.$$)
rc=$?
if [[ "$rc" -eq 0 ]]; then
  comments="$comments; pid not found handled correctly (rc=0; +2)"; points=$(( $points + 2 ))
else
  comments="$comments; pid not found handled incorrectly (rc=$rc; -2)"
fi
wco=$(wc -c /tmp/tmp.out.$$ | awk '{print $1}')
if [[ "$wco" -eq 0 ]]; then
  comments="$comments; pid not found does not print to cout (+1)"; points=$(( $points + 1 ))
else
  comments="$comments; pid not found incorrectly prints to cout (-1)"
fi
wce=$(wc -c /tmp/tmp.err.$$ | awk '{print $1}')
if [[ "$wce" -eq 0 ]]; then
  comments="$comments; pid not found does not print to cerr (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; pid not prints to cerr (-2)"
fi

# test of searching for a user that does not exist
currProcInfo=$(./procInfo -u yomama 1>|/tmp/tmp.out.$$ 2>|/tmp/tmp.err.$$)
rc=$?
if [[ "$rc" -ne 0 ]]; then
  comments="$comments; invalid user handled correctly (rc!=0; +2)"; points=$(( $points + 2 ))
else
  comments="$comments; invalid user handled incorrectly (rc=0; -2)"
fi
wco=$(wc -c /tmp/tmp.out.$$ | awk '{print $1}')
if [[ "$wco" -eq 0 ]]; then
  comments="$comments; invalid user does not print to cout (+1)"; points=$(( $points + 1 ))
else
  comments="$comments; invalid user prints to cout (-1)"
fi
wce=$(wc -c /tmp/tmp.err.$$ | awk '{print $1}')
if [[ "$wce" -gt 0 ]]; then
  comments="$comments; invalid user prints to cerr (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; invalid user does not print to cerr (-2)"
fi

# test of searching for a pid with invalid characters 
currProcInfo=$(./procInfo --pid yomama 1>|/tmp/tmp.out.$$ 2>|/tmp/tmp.err.$$)
rc=$?
if [[ "$rc" -ne 0 ]]; then
  comments="$comments; invalid pid chars handled correctly (rc!=0; +2)"; points=$(( $points + 2 ))
else
  comments="$comments; invalid pid chars handled incorrectly (rc=0; -2)"
fi
wco=$(wc -c /tmp/tmp.out.$$ | awk '{print $1}')
if [[ "$wco" -eq 0 ]]; then
  comments="$comments; invalid pid chars does not print to cout (+1)"; points=$(( $points + 1 ))
else
  comments="$comments; invalid pid chars prints to cout (-1)"
fi
wce=$(wc -c /tmp/tmp.err.$$ | awk '{print $1}')
if [[ "$wce" -gt 0 ]]; then
  comments="$comments; invalid pid chars prints to cerr (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; invalid pid chars does not print to cerr (-2)"
fi

# test of searching for a pid with invalid number 
currProcInfo=$(./procInfo --pid 0 1>|/tmp/tmp.out.$$ 2>|/tmp/tmp.err.$$)
rc=$?
if [[ "$rc" -ne 0 ]]; then
  comments="$comments; invalid pid number handled correctly (rc!=0; +2)"; points=$(( $points + 2 ))
else
  comments="$comments; invalid pid number handled incorrectly (rc=0; -2)"
fi
wco=$(wc -c /tmp/tmp.out.$$ | awk '{print $1}')
if [[ "$wco" -eq 0 ]]; then
  comments="$comments; invalid pid number does not print to cout (+1)"; points=$(( $points + 1 ))
else
  comments="$comments; invalid pid number prints to cout (-1)"
fi
wce=$(wc -c /tmp/tmp.err.$$ | awk '{print $1}')
if [[ "$wce" -gt 0 ]]; then
  comments="$comments; invalid pid number prints to cerr (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; invalid pid number does not print to cerr (-2)"
fi

# test of searching for a process and a user that does not own that process
currProcInfo=$(./procInfo --pid $$ --user root 1>|/tmp/tmp.out.$$ 2>|/tmp/tmp.err.$$)
rc=$?
if [[ "$rc" -ne 0 ]]; then
  comments="$comments; pid specified not owned by user specified handled correctly (rc!=0; +2)"; points=$(( $points + 2 ))
else
  comments="$comments; pid specified not owned by user specified handled incorrectly (rc=0; -2)"
fi
wco=$(wc -c /tmp/tmp.out.$$ | awk '{print $1}')
if [[ "$wco" -eq 0 ]]; then
  comments="$comments; pid specified not owned by user specified does not print to cout (+1)"; points=$(( $points + 1 ))
else
  comments="$comments; pid specified not owned by user specified prints to cout (-1)"
fi
wce=$(wc -c /tmp/tmp.err.$$ | awk '{print $1}')
if [[ "$wce" -gt 0 ]]; then
  comments="$comments; pid specified not owned by user specified prints to cerr (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; pid specified not owned by user specified does not print to cerr (-2)"
fi

# 75 points max thus far

# merle 2842119 '/usr/bin/bash' 'bash' 7491 12888
refOut=$(./procMemListing.sh --pid $$ 2>/dev/null)
read userRef pidRef cmdlineRef programRef pssRef rssRef <<< "$refOut"
testOut=$(./procInfo --pid $$ 2>/dev/null)
read userTest pidTest cmdlineTest programTest pssTest rssTest <<< "$testOut"
if [[ "$userRef" == "$userTest" ]]; then
  comments="$comments; pid \$\$ test matches the username (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; pid \$\$ test does not match the username ($userRef vs. $userTest; -2)"
fi
if [[ "$pidRef" == "$pidTest" ]]; then
  comments="$comments; pid \$\$ test matches the pid (+1)"; points=$(( $points + 1 ))
else
  comments="$comments; pid \$\$ test does not match the pid ($pidRef vs. $pidTest; -1)"
fi
if [[ "$cmdlineRef" == "$cmdlineTest" ]]; then
  comments="$comments; pid \$\$ test matches the cmdline (+3)"; points=$(( $points + 3 ))
else
  comments="$comments; pid \$\$ test does not match the cmdline ($cmdlineRef vs. $cmdlineTest; -3)"
fi
if [[ "$programRef" == "$programTest" ]]; then
  comments="$comments; pid \$\$ test matches the program name (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; pid \$\$ test does not match the program name ($programRef vs. $programTest; -2)"
fi
if [[ ! -z $pssTest ]] && $pssTest -gt 0 ]] && [[ ! -z $rssTest ]] && [[ $rssTest -gt 0 ]]; then
  comments="$comments; pid \$\$ test has numeric values for PSS and RSS (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; pid \$\$ test has non-numeric values for PSS and/or RSS ($pssTest, $rssTest; -2)"
fi

./procMemListing.sh --user root 2>/dev/null | sort -d 1>/tmp/refOut.$$
refOutLines=$(wc -l /tmp/refOut.$$)
read userRef pidRef cmdlineRef programRef pssRef rssRef <<< $(head -1 /tmp/refOut.$$)
./procInfo --user root 2>/dev/null | sort -d 1>/tmp/testOut.$$
testOutLines=$(wc -l /tmp/testOut.$$)
read userTest pidTest cmdlineTest programTest pssTest rssTest <<< $(head -1 /tmp/testOut.$$)
if [[ "$userRef" == "$userTest" ]]; then
  comments="$comments; user root test matches the username (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; user root test does not match the username ($userRef vs. $userTest; -2)"
fi
if [[ "$pidRef" == "$pidTest" ]]; then
  comments="$comments; user root test matches the pid (+1)"; points=$(( $points + 1 ))
else
  comments="$comments; user root test does not match the pid ($pidRef vs. $pidTest; -1)"
fi
if [[ "$cmdlineRef" == "$cmdlineTest" ]]; then
  comments="$comments; user root test matches the cmdline (+3)"; points=$(( $points + 3 ))
else
  comments="$comments; user root test does not match the cmdline ($cmdlineRef vs. $cmdlineTest; -3)"
fi
if [[ "$programRef" == "$programTest" ]]; then
  comments="$comments; user root test matches the program name (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; user root test does not match the program name ($programRef vs. $programTest; -2)"
fi
if [[ -z $pssTest ]] && [[ -z $rssTest ]]; then
  comments="$comments; user root test has no values for PSS and RSS (+2)"; points=$(( $points + 2 ))
else
  comments="$comments; user root test has values for PSS and/or RSS ($pssTest, $rssTest; -2)"
fi

# 95 points max thus far

# <<< NEED TO ADD A 5-POINT TEST FOR VALGRIND >>>

echo "Score = $points"
echo "Comments = $comments"
if [[ "$points" -eq 100 ]]; then
  exit 0
else
  exit $points
fi
