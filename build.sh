#!/bin/bash

if [ ! -d build ]; then
     mkdir -p build
fi

pushd build
cmake .. -DUSE_BOOST_LAYOUT_VERSIONED=on -DLINK_AGAINST_STATIC_BOOST=on
make VERBOSE=1
popd
