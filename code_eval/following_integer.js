// following_integer.js

// You are writing out a list of numbers.Your list
// contains all numbers with exactly Di digits in
// its decimal representation which are equal to i,
// for each i between 1 and 9, inclusive. You are
// writing them out in ascending order. For example,
// you might be writing every number with two '1's and
// one '5'. Your list would begin 115, 151, 511, 1015, 1051.
// Given N, the last number you wrote, compute what the
// next number in the list will be. The number of 1s,
// 2s, ..., 9s is fixed but the number of 0s is arbitrary.

function swap(arr, i, j) {
    var temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return arr;
}

var fs  = require('fs');
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != '') {
        var digits = line.replace(/^0+/, '').split('');
        var done = false;

        // handle swap case
        for (var i = digits.length - 1; i > 0 && !done; i--) {
            if (+digits[i-1] < +digits[i]) {
                digits = swap(digits, i, i - 1);
                done = true;
            }
        }

        // handle 'simple add a zero' case
        if (!done) {
            var num_zero = 0, num_other = 0;
            digits.forEach(function (digit) {
                (+digit === 0) ? num_zero++ : num_other++;
            });
            if (num_zero !== 0 && num_other === 1) {
                digits.push('0');
                done = true;
            }
        }

        // handle 'reorder and add a zero' case
        if (!done) {
            digits.sort();
            var check_index = 0,
                check_value = digits[0];
            digits.forEach(function(digit, index) {
                if (digit == check_value) {
                    check_index = index;
                }
                if (digit < check_value) {
                    check_value = digit;
                    check_index = index;
                    return ;
                }
            });

            digits.push(check_value);
            digits.sort();
            digits[check_index + 1] = '0';
            done = true;
        }

        console.log(digits.join(''));
    }
});
