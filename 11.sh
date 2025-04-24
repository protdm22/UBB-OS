#!/bin/bash

procs=$(grep -E -c "$2" ps.fake)
awk -v procs="$procs" 'BEGIN {sum = 0} {sum += $2} END {print sum/procs}' ps.fake
