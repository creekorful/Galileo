#!/bin/bash

# first of all delete old folders
rm -rf cmake-build-debug/Resources

# copy new
cp -r Resources cmake-build-debug/