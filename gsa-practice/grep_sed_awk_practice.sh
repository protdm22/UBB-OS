------Grep/Sed/Awk----------------------------------------------------------------------------------------------------------------
Probleme Boian:
    1. cat last.fake | grep -E "economica" | grep -E "Sun" | awk '{print $1}' | sort | uniq 
    2. cat last.fake | awk '{print $1,$7}' | sed 's/;/ /g' | head -n -1 | grep -E "^[^ ]* 2[3-9]" | awk '{print $1}' | sort | uniq 
    3. cat passwd.fake | grep -E "\<m[a-z 0-9]+:" | awk -F: '{if ($3%7==0) print $5}'
    4. cat ps.fake | grep -E "\<root" | awk '{print $6}' | sort | uniq
    5. cat passwd.fake | awk -F: '$1 ~ /88$/ {print $5}'
    6. cat passwd.fake | grep -E "[^:]+:x:23[0-9]" | sed 's/:/ /g' | awk '{print $5,$6}'
    7. cat last.fake | grep -E "^t[a-z0-9]+ pts/9" | awk '{print $1}'
    8. cat ps.fake | grep -E "^r" | awk '{print $1}' | sort | uniq | sed 's/\([aeiouAEIOU]\)/\1\1/g'
    9. cat passwd.fake | sed 's/[ a-z0-9A-Z]//g' | sort | uniq
    10. cat passwd.fake | sed 's/[^r]//g' | sort | uniq
    11. ver1:
            procs=$(grep -E -c "$2" ps.fake)
            sum=$(awk '{sum+= $2} END {print sum}' ps.fake)
            avg=$((sum/procs))
            echo "$avg"
        ver2:
            procs=$(grep -E -c "$2" ps.fake)
            awk -v procs="$procs" 'BEGIN {sum = 0} {sum += $2} END {print sum/procs}' ps.fake    

Probleme Bradut:
    GREP.1. grep -E '^.{3}*$' passwd.fake
    GREP.2. grep -E '([^AEIOU]*[AEIOU][^AEIOU]*){3,}' input | grep -E -v "[13579]"
    GREP.3. grep -E "^([13579]{2})*[^0-9]*[02468]([02468]{2})*$" input   
    GREP.4. grep -E -v '([^AEIOU]*[AEIOU][^AEIOU]*){3,}' input | grep -E -v "[13579]" # same as 2 but -v for reverse condition
    GREP.5.
    GREP.6. grep -E -v "[^A-Z]" input | wc -l
    GREP.7.
    GREP.8.
    GREP.9. grep -E -v "[0-9a-zA-z]+" # input.txt - does not work with []() and I think other characters as well
            grep -E "^[^0-9a-zA-z]*$" # input - alternate version, same issue   
 
    SED.1. sed 's/[aeiou]/\U&/g' input
    SED.2. sed 's/^..//' input | sed 's/...$//'
    SED.3. sed 's/[A-Z]/&&&/g' input
    SED.4. sed -E 's/([0-9]{2,})/{\1}/g' input
    SED.5. sed 's/\([^ ]*\) [^ ]* /\1 /' input
    SED.6. sed -E '/^[^ ]+ [^ ]+/s/^([^ ]+) (.*) ([^ ]+)$/\3 \2 \1/' input
    SED.7. sed 's/^\(.\)\(.*\)\(.\)$/\3\2\1/' input
    SED.8. sed -E 's/[AEIOU]{3,}//g' input

    AWK.1. awk 'BEGIN {sum_even = 0; sum_odd = 0; count_odd = 0} NR % 2 == 0 {for (i = 1; i <= NF; i++) sum_even += $i} {for (i = 1; i <= NF ; i++) if ($i % 2 == 1) {sum_odd += $i; count_odd += 1}} END {print "Sum on even lines: " sum_even; if (count_odd > 0) print "Average of odd numbers: " sum_odd / count_odd; else print 0}' number
    AWK.2.
    AWK.3.
    AWK.4.
    AWK.5.
    AWK.6.
    AWK.7.
    AWK.8.
    AWK.9.
    AWK.10.

