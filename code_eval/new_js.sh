#! /bin/bash

if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters"
    exit 1
fi

echo "\
// $@.js

var fs  = require('fs');
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != '') {
        //do something here
    }
});\
" > $@.js

echo "" > $@.txt
