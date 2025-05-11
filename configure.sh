#!/bin/bash

CWD=$(pwd)
GTEST_GIT="https://github.com/google/googletest.git"
SPDLOG_GIT="https://github.com/gabime/spdlog.git"
echo $CWD
echo "configuring dependencies"
echo "cloning googletest"

git clone "$GTEST_GIT" "$CWD/external/googletest" \
     || (echo "directory google test already exists, attempting to build")

echo 'building google test'
cd "$CWD/external/googletest/" || (echo "can't find googletest directory" | exit)
cmake -S . -B build/ -DCMAKE_INSTALL_PREFIX="$CWD/external/"
cd "$CWD/external/googletest/build/"
make
make install
cd $CWD || exit

echo "cloning spdlog"
git clone "$SPDLOG_GIT" "$CWD/external/spdlog/" \
    || (echo "directory spdlog already exists, attempting build")

echo "building spdlog"
cd "$CWD/external/spdlog" || exit
cmake -S . -B build/ -DCMAKE_INSTALL_PREFIX="$CWD/external/"
cd "$CWD/external/spdlog/build/"
make
make install
cd "$CWD/logging/"
cmake -S . -B build/
cd build/
make
make install

echo "downloading eigen"
cd "$CWD/external/"
git clone https://gitlab.com/libeigen/eigen.git



