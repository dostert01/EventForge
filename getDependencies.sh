#!/bin/bash

DEPS_DIR=_deps

GOOGLE_TEST_VERSION="1.12.1"
GOOGLE_TEST_ZIP=release-${GOOGLE_TEST_VERSION}.zip
GOOGLE_TEST_DIR=${DEPS_DIR}/googletest

function getGoogleTests(){
    echo "downloading googletest"
    if [ ! -d "$GOOGLE_TEST_DIR" ]; then
        wget https://github.com/google/googletest/archive/$GOOGLE_TEST_ZIP
        unzip $GOOGLE_TEST_ZIP
        mv googletest-release-$GOOGLE_TEST_VERSION $GOOGLE_TEST_DIR
        rm $GOOGLE_TEST_ZIP
    else
        echo "$GOOGLE_TEST_DIR already present!"
    fi
}

if [ ! -d $DEPS_DIR ]; then
    mkdir $DEPS_DIR
fi

getGoogleTests
getMosquito
