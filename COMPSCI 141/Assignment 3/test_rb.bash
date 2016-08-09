#!/bin/bash

C1_EXPECTED='7
-1
7
-1
Data Segment Contents
0: -1
1: 7
2: -1
3: 0
4: 0'

echo '# C1'
diff -w <(./INTERPRETER.rb ./C1.txt | head -n 10) <(echo "$C1_EXPECTED") && echo pass || exit 1

C2_EXPECTED='1
1
1
1
1
1
1
1
2
3
4
1
6
1
1
1
1
1
1
1
1
1
2
1
2
1
2
7
1
1
3
1
5
3
1
1
2
1
4
1
2
1
1
1
1
1
1
1
1
1
2
3
2
1
6
1
1
1
1
1
1
1
1'

echo '# C2'
diff -w <(for i in `seq 11 19`; do for j in `seq 1 7`; do ./INTERPRETER.rb C2.txt <<< "$i
$j" | head -n 1; done; done) <(echo "$C2_EXPECTED") && echo pass || exit 1

C3_EXPECTED='1
3
7
15
31
63
127
255
511
1023'

echo '# C3'
diff -w <(for i in `seq 1 10`; do ./INTERPRETER.rb ./C3.txt <<< "$i" | head -n 1; done) <(echo "$C3_EXPECTED") && echo pass || exit 1

C3P_EXPECTED='3: 1
3: 1
3: 2
3: 3
3: 5
3: 8
3: 13
3: 21
3: 34
3: 55'

# testing D[3] for last returned value
# because C3P does not have print statement

echo '# C3P_value'
diff -w <(for i in `seq 1 10`; do ./INTERPRETER.rb ./C3P_value.txt <<< "$i" | grep '^3:'; done) <(echo "$C3P_EXPECTED") && echo pass || exit 1

echo '# C3P_reference'
diff -w <(for i in `seq 1 10`; do ./INTERPRETER.rb ./C3P_reference.txt <<< "$i" | grep '^3:'; done) <(echo "$C3P_EXPECTED") && echo pass || exit 1
