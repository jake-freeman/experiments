//Sample code to read in test cases:
var fs  = require("fs");
var first_line = true,
    num_list = 0,
    items = [];
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        if (first_line) {
            first_line = false;
            num_list = parseInt(line);
        }
        else {
            items.push({
                        length: line.length,
                        content: line
                    });
        }
    }
});

items.sort(function(a,b) {
    return b.length - a.length;
});

for (var j = 0; j < num_list; j++) {
    console.log(items[j].content);
}
