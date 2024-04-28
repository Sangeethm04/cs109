#!/bin/bash

runTime=${1:-10}
#/home/merle/cse109.spring2024/inClassPrograms/createProcs $runTIme &

# following 4 lines are to read command output into associative array and were adapted from
# https://unix.stackexchange.com/questions/355217/return-the-output-of-a-command-into-an-associative-array
declare -A procs
while IFS=" " read -r pid cmd ; do
  procs["$pid"]="$cmd"
done < <(ps --user "$USER" | awk '{ if ($1 != "PID" && $2 != "?") print $1, $4}')

wd=$(readlink -f /proc/$$/cwd)
shell="${SHELL##*/}"
for pid in "${!procs[@]}" ; do
  if [ -d /proc/$pid ]; then
    name=$(awk '/^Name:/ {print $2}' /proc/$pid/status)
    cmdLine=$(xargs -0 < /proc/$pid/cmdline)
    cmdLine=$(echo "$cmdLine" | sed "s/-$shell/$shell/")
    cwd=$(readlink -f /proc/$pid/cwd)
    rssAndPss=$(awk '/^Pss:/ {TotPss+=$2}; /^Rss:/ {TotRss+=$2}; END {print TotPss,TotRss}' /proc/$pid/smaps)
    if [[ $cmdLine =~ ^/ ]]; then
      echo "$USER $pid '$cmdLine' '$name' $rssAndPss"
    else
      echo "$USER $pid '$cwd/$cmdLine' '$name' $rssAndPss"
    fi
  fi
  # uncomment following line to print out the value stored in the associative array for the particular key
  #echo "$pid ${procs[$pid]}"
done

