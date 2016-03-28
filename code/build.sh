#!/bin/bash
rm -fr bin
mkdir bin
rm -fr build
mkdir build
cd build
cmake ..
make

cd ..
cp -r data bin
cp parameters.txt bin
