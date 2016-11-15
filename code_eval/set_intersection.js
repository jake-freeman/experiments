var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        var lists = line.split(';');
        var list1 = lists[0].split(','),
            list2 = lists[1].split(',');

        var intersection = '';
        list1.forEach(function (li) {
            if (list2.indexOf(li) !== -1) {
                intersection += li.toString() + ',';
            }
        });
        console.log(intersection.replace(/,\s*$/, ""));
    }
});
