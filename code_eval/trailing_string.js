// trailing_string.js

var fs  = require('fs');
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != '') {
        var strings = line.split(',');
        var out = '';
        strings[0].match(`${strings[1]}$`) ? out = '1' : out = '0';
        console.log(out);
    }
});
