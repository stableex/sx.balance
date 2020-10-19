#!/bin/bash

# compile
g++ -std=c++11 -o balancer.t.out balancer.t.cpp -I __tests__

# test
./balancer.t.out --success

