#!/bin/bash

if [ ! -d build ]; then
     mkdir -p build
fi

pushd build
cmake ..
make
popd
