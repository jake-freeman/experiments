//Sample code to read in test cases:
var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        var ints = line.split(' '),
            stack = [];
        ints.forEach(function(num) {
           stack.push(num);
        });
        var i = 1,
            values = [];
        while (stack.length !== 0) {
            value = stack.pop();
            if (i % 2 !== 0) {
                values.push(value);
            }
            i++;
        }
        console.log(values.toString().replace(',',' '));
    }
});
