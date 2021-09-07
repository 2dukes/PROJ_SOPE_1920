#!/bin/bash

# Number of directories specified in the argument

COUNTER=2
while [ $COUNTER -le $1 ]; do
    dirName="TP${COUNTER}"
    echo "${dirName}"
    mkdir ${dirName}
    let COUNTER+=1
done