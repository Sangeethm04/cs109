#!/bin/bash

function readProc {
  pid=$1
  if [ -d /proc/$pid ]; then
    actualUser=$(ps -o user= -p $pid)
    if ( [[ ! -z "$user" ]] && [[ "$actualUser" == "$user" ]] ) || [[ -z "$user" ]] ; then
      name=$(awk '/^Name:/ {print $2}' /proc/$pid/status 2>/dev/null)
      cmdLine=$(xargs -0 < /proc/$pid/cmdline 2>/dev/null)
      if [ ! -z "$shell" ]; then  # if shell name not NULL, remove '-' from listing of login shell
        cmdLine=$(echo "$cmdLine" | sed "s/-$shell/$shell/")
      fi
      exe=$(readlink -f /proc/$pid/exe 2>/dev/null)
      pssAndRss=$(awk '/^Pss:/ {TotPss+=$2}; /^Rss:/ {TotRss+=$2}; END {print TotPss,TotRss}' /proc/$pid/smaps 2>/dev/null)
      if [[ "$cmdLine" =~ ^/ ]]; then   # if the first field does not have a path in front of it...
        echo "$actualUser $pid '$cmdLine' '$name' $pssAndRss"
      else   # if the program does not include a path...
        cmdLine=$(echo -n $exe)   # build a new cmdline with the exe and the remaining arguments from cmdline
        remFields=$(echo $cmdLine | awk -v n=2 '{ for (i=n; i<=NF; i++) print $i }')
        if [ ! -z "$remFields" ]; then
          cmdLine="$cmdLine $remFields"
        fi
        echo "$actualUser $pid '$cmdLine' '$name' $pssAndRss"
      fi
    else
      echo "User $user is not the owner of pid $pid ($actualUser is the owner)"
      exit 97
    fi
  fi
}

# check number of arguments
pid=""
user=""
regex='^[0-9]+$'
if [[ "$#" -eq 0 ]]; then    # if no arguments
  pid=$$
elif [[ "$#" -eq 1 ]] && [[ "$1" =~ $regex ]] ; then   # if 1 argument and that argument is a #
  pid=$1
elif [[ "$#" -eq 2 ]]; then
  if [[ "$1" = "-u" ]] || [[ "$1" = "--user" ]]; then
    user=$2
  elif [[ "$1" = "-p" ]] || [[ "$1" = "--pid" ]]; then
    if [[ "$2" =~ $regex ]] && [[ "$2" -gt 0 ]]; then
      pid=$2
    else
      echo "Process $2 is not a valid pid"; exit 99
    fi
  else
    echo "Usage: procMemListing.sh [-u|--user <username>] [-p|--pid <pid>] [<pid>]"; exit 99
  fi
elif [[ "$#" -eq 4 ]]; then
  if [[ "$1" = "-u" ]] || [[ "$1" = "--user" ]]; then
    user=$2
    if [[ "$3" = "-p" ]] || [[ "$3" = "--pid" ]]; then
      if [[ "$4" =~ $regex ]] && [[ "$4" -gt 0 ]]; then
        pid=$4
      else
        echo "Process $4 is not a valid pid"; exit 99
      fi
    else
      echo "Usage: procMemListing.sh [-u|--user <username>] [-p|--pid <pid>] [<pid>]"
      exit 99
    fi
  elif [[ "$1" = "-p" ]] || [[ "$1" = "--pid" ]]; then
    if [[ "$2" =~ $regex ]] && [[ "$2" -gt 0 ]]; then
      pid=$2
    else
      echo "Process $2 is not a valid pid"; exit 99
    fi
    if [[ "$3" = "-u" ]] || [[ "$3" = "--user" ]]; then
      user=$4
    else
      echo "Usage: procMemListing.sh [-u|--user <username>] [-p|--pid <pid>] [<pid>]"
      exit 99
    fi
  else
    echo "Usage: procMemListing.sh [-u|--user <username>] [-p|--pid <pid>] [<pid>]"
    exit 99
  fi
else
  echo "Usage: procMemListing.sh [-u|--user <username>] [-p|--pid <pid>] [<pid>]"
  exit 99
fi

shell="${SHELL##*/}"
if ( [[ ! -z "$user" ]] && [[ ! -z "$pid" ]] ) || [[ -z "$user" ]] ; then
  readProc $pid
else
  if id "$user" 1>/dev/null 2>&1; then
    # following 4 lines are to read command output into associative array and were adapted from
    # https://unix.stackexchange.com/questions/355217/return-the-output-of-a-command-into-an-associative-array
    declare -A procs
    while IFS=" " read -r pid cmd ; do
      procs["$pid"]="$cmd"
    done < <(ps --user "$user" 2>/dev/null | awk '{ if ($1 != "PID" && $2 != "?") print $1, $4}')
  else
    echo "User $user does not exist"
    exit 98
  fi
fi

wd=$(readlink -f /proc/$$/cwd)
for pid in "${!procs[@]}" ; do
  readProc $pid
  # uncomment following line to print out the value stored in the associative array for the particular key
  #echo "$pid ${procs[$pid]}"
done
