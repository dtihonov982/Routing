#!/bin/bash

if [ $# -eq 0 ]
then
    INPUT=data/input2.json
    CELLS=data/cells2.json
    OUTPUT=data/output2.json
elif [ $# -eq 3 ]
then
    INPUT=$1
    CELLS=$2
    OUTPUT=$3
else
    echo "Usage: test.sh input_json cells_json output_json"
    exit 1
fi


build/programs/route $INPUT $CELLS $OUTPUT &&
tests/draw.py $CELLS $OUTPUT
