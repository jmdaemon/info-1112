#!/bin/bash
for i in $(seq 0 10); do
    echo "1000 $i" | ./bin/l2
done
