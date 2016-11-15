// string_perm.js

var perm_string = "";

function factorial(n) {
    var j = 1;
    for (var i = 1; i <= n; i++) {
        j = j * i;
    }
    return j;
}

function swap(arr, i, j) {
    var temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return arr;
}

function generate(n, arr) {
    if (n === 1) {
        perm_string += arr.toString().replace(/,/g,'') + ',';
    }
    else {
        for (var i = 0; i < n - 1; i++) {
            generate(n-1, arr);
            if ((n % 2) === 0) {
                arr = swap(arr, i, n - 1);
            }
            else {
                arr = swap(arr, 0, n - 1);
            }
        }
        generate(n - 1, arr);
    }
}

function permutation(arr) {
    perm_string = '';
    return generate(arr.length, arr);
}

function uniq(arr) {
    return arr.sort().filter(function(item, pos, arr) {
        return !pos || item != arr[pos - 1];
    });
}

var fs  = require('fs');
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != '') {
        var chars = line.split('');
        permutation(chars);

        var perm = perm_string.replace(/,$/, '').split(',');
        perm = uniq(perm);
        console.log(perm.toString());
    }
});
