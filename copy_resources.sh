#!/bin/bash

# first of all delete old folders
rm -rf cmake-build-debug/Shaders
rm -rf cmake-build-debug/Textures

# copy new
cp -r Shaders cmake-build-debug/
cp -r Textures cmake-build-debug/