#!/bin/bash

if [[ ! $OSTYPE =~ "linux" ]]; then
    echo "Only supported on Linux"
    exit 1
fi

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd)"

function init() {
    cd $SCRIPTPATH
    mkdir -p build
    rm -rf src_test
    mkdir -p src_test
    unzip src_zip/handin.zip -d src_test |& tee build/zip.log
    rm -f src_test/main.cpp
}

function cmake_debug() {
    init
    cd $SCRIPTPATH/build
    echo "------------- Running cmake -------------"
    cmake \
        -DCMAKE_C_COMPILER=/usr/bin/clang \
        -DCMAKE_CXX_COMPILER=/usr/bin/clang++ \
        -DCMAKE_BUILD_TYPE=Debug \
        .. \
        |& tee cmake.log
}

function cmake_release() {
    init
    cd $SCRIPTPATH/build
    echo "------------- Running cmake -------------"
    cmake \
        -DCMAKE_C_COMPILER=/usr/bin/clang \
        -DCMAKE_CXX_COMPILER=/usr/bin/clang++ \
        -DCMAKE_BUILD_TYPE=Release \
        .. \
       |& tee cmake.log
}

function make_debug() {
    cd $SCRIPTPATH/build
    echo "------------- Running make --------------"
    # make -j8 StaticSrcTest
    # make -j8 StaticSrcLF
    make -j8 Debug-test |& tee make.log
}

function make_release() {
    cd $SCRIPTPATH/build
    echo "------------- Running make --------------"
    # make -j8 StaticSrcTest
    # make -j8 StaticSrcLF
    make -j8 Release-test |& tee make.log
}

function run_debug() {
    cd $SCRIPTPATH/build/Debug
    echo "------------- Running test --------------"
    ./Debug-test --logger=HRF,all,stdout
    ./Debug-test --logger=HRF,all,result.log &>> result.log
    cd $SCRIPTPATH
    ./remove-path build/zip.log build/cmake.log build/make.log build/Debug/result.log
}

function run_release() {
    cd $SCRIPTPATH/build/Release
    echo "------------- Running test --------------"
    ./Release-test --logger=HRF,all,stdout
    ./Release-test --logger=HRF,all,result.log &>> result.log
    cd $SCRIPTPATH
    ./remove-path build/zip.log build/cmake.log build/make.log build/Release/result.log
}

function make_clean() {
    cd $SCRIPTPATH/build
    echo "------------- Running clean -------------"
    make clean
}

function remove_build() {
    rm -rf $SCRIPTPATH/build
}

function print_help() {
    echo "Arguments: "
    echo "cmake debug"
    echo "cmake release"
    echo "make debug"
    echo "make release"
    echo "run debug"
    echo "run release"
    echo "clean"
    echo "remove"
    echo "help"
}

if [[ $1 == "cmake" ]]; then
    if [[ $2 == "debug" ]]; then
        cmake_debug
    elif [[ $2 == "release" ]]; then
        cmake_release
    else
        print_help
    fi
elif [[ $1 == "make" ]]; then
    if [[ $2 == "debug" ]]; then
        cmake_debug
        make_debug
    elif [[ $2 == "release" ]]; then
        cmake_release
        make_release
    else
        print_help
    fi
elif [[ $1 == "run" ]]; then
    if [[ $2 == "debug" ]]; then
        cmake_debug
        make_debug
        run_debug
    elif [[ $2 == "release" ]]; then
        cmake_release
        make_release
        run_release
    else
        print_help
    fi
elif [[ $1 == "clean" ]]; then
    make_clean
elif [[ $1 == "remove" ]]; then
    remove_build
else
    print_help
fi
