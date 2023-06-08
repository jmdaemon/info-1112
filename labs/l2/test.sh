#!/bin/bash

AMOUNT=1000

# Test correct cases
for i in $(seq 0 10); do
    echo "$AMOUNT $i" | ./bin/l2
done

# Test invalid cases
echo "$AMOUNT -1" | ./bin/l2
echo "$AMOUNT 11" | ./bin/l2
