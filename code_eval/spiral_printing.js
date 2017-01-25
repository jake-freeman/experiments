// spiral_printing.js

var fs  = require('fs');
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != '') {
        var split_line = line.split(';'),
            rows  = parseInt(split_line[0]),
            cols  = parseInt(split_line[1]),
            items = split_line[2].split(' '),
            matrix = new Array(rows);

        // make 2D martrix
        for (var i = 0; i < rows; i++) {
            matrix[i] = new Array(cols);
        }

        // fill 2D matrix
        for (var i = 0, x = 0; x < rows; x++) {
            for (var y = 0; y < cols; y++, i++) {
                martrix[x][y] = items[i];
            }
        }

        var row_max = rows - 1,
            col_max = cols - 1;

        var counter = 0,
            output = "";
        while (counter < items.length) {
            
        }
    }
});
