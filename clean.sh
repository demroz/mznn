#!/bin/bash

CWD=$(pwd)
echo "cleaning up external library files"
cd "$CWD/external/"
rm -rf lib/* lib64/* include/* googletest/ spdlog/
