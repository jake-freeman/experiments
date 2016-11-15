// string_searching.js

// You are given two strings. Determine if the second
// string is a substring of the first (Do NOT use any
// substr type library function). The second string
// may contain an asterisk(*) which should be treated
// as a regular expression i.e. matches zero or more
// characters. The asterisk can be escaped by a \ char
// in which case it should be interpreted as a regular
// '*' character. To summarize: the strings can contain
// alphabets, numbers, * and \ characters.

var fs  = require('fs');
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != '') {
        var strings = line.split(',');
        //console.log(strings[1].replace(/\\\\/g, ''));
        strings[1] = strings[1]
            .replace(/\\\\/g, '')
            .replace(/([^\\\*]|^)\*+/g, "$1[a-zA-Z0-9]*");
        //console.log(strings[1]);
        var out = "";
        strings[0].match(strings[1]) ? out = 'true' : out = 'false';
        console.log(out);
    }
});
