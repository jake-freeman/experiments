'use strict';
// telephone.js

var fs  = require('fs');
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != '') {
        var letters = ['0', '1', 'abc', 'def', 'ghi', 'jkl', 'mno', 'pqrs', 'tuv', 'wxyz'],
            permutations = 1;
        line.split('').forEach(function (num) {
            permutations *= letters[+num].length;
        });

        var words = new Array(permutations);
        for (let i = 0; i < words.length; i++) { words[i] = ""; }

        line.split('').forEach(function (num) {
            let modulo = letters[+num].length,
                letter = 0;
            for (let i = 0; i < permutations; i++) {
                words[i] += `${letters[+num][letter]}`;
                (letter >= (modulo - 1)) ? letter = 0 : letter++;
            }
            words = words.sort();
        });
        console.log(words.join());
    }
});
