#!/bin/bash
awk 'BEGIN {sum_even = 0; sum_odd = 0; count_odd = 0} NR % 2 == 0 {for (i = 1; i <= NF; i++) sum_even += $i} {for (i = 1; i <= NF; i++) if ($i % 2 == 1) {sum_odd += $i; count_odd += 1}} END {print "Sum on even lines: " sum_even; if (count_odd > 0) print "Average of odd numbers: " sum_odd / count_odd; else print 0}' number

