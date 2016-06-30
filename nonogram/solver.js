const _ = require('lodash');

var self = module.exports;

function _main() {
  var puz = self.makePuzzle(25,25);
  self.printPuzzle(puz);
}

module.exports.makePuzzle = function(height, width) {
  function createMatrix(rows, cols, defaultValue) {
    var arr = [];
    for (var i=0; i < rows; i++) {
      arr.push([]);
      arr[i].push( new Array(cols));
      for(var j=0; j < cols; j++){
        arr[i][j] = defaultValue;
      }
    }
    return arr;
  }

  var puzzle = {
    rowHints: createMatrix(width,  ((height + 1) / 2).toFixed(0), 0),
    colHints: createMatrix(height, ((width  + 1) / 2).toFixed(0), 0),
    squares:  createMatrix(height, width, false),
    width:    width,
    height:   height
  };

  return puzzle;
};

// [HACK] this function can and should be cleaned up and simplified
//
module.exports.printPuzzle = function(puz) {
  var output = "";
  for (var j = puz.colHints[0].length - 1; j >=0; j--) {
    for (var k = 0; k < puz.rowHints[0].length; k++) {
      output += '   ';
    }
    output += '  ';
    for (var i = 0; i < puz.width; i++) {
      var hint = puz.colHints[i][j];
      output += (hint ? hint : '-') + '  ';
    }
    output += '\n';
  }
  output += '\n';
  for (var i = 0; i < puz.height; i++) {
    for (var j = 0; j < puz.rowHints[0].length; j++) {
      var hint = puz.rowHints[i][j];
      output += (hint ? hint : '-') + '  ';
    }
    output += '  ';
    for (var k = 0; k < puz.width; k++) {
      output += (puz.squares[i][k] ? '*' : ' ') + '  ';
    }
    output += '\n';
  }
  console.log(output);
};

_main();
