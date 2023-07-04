#!/bin/bash
clang++ wfn.cpp -o wfn.x
clang++ -std=c++17 d2ab.cpp -o d2ab.x
clang++ -std=c++17 d2aa.cpp -o d2aa.x
