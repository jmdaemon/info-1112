#!/bin/bash

#echo "1000 0" | ./bin/l2
#echo "1000 1" | ./bin/l2
#echo "1000 2" | ./bin/l2
#echo "1000 3" | ./bin/l2
#echo "1000 4" | ./bin/l2
#echo "1000 5" | ./bin/l2
#echo "1000 6" | ./bin/l2
#echo "1000 7" | ./bin/l2
#echo "1000 8" | ./bin/l2
#echo "1000 9" | ./bin/l2
#echo "1000 10" | ./bin/l2

for i in $(seq 0 10); do
    echo "1000 $i" | ./bin/l2
done
