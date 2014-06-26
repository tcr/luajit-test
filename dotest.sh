#!/bin/bash

./build.sh "$1"
node run.js stage/main
