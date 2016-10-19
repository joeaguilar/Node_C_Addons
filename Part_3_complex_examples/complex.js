// complex.js
var addon = require('bindings')("addon.node");


console.log( addon.numbers([1,2,3,4,5,6, 9002, 1000000]) );
console.log( addon.strings(["This", "is", "an", "array", "of", "strings"]) );
console.log( addon.bools([true, true, false, false, true, false, true, false]) ); 
console.log( addon.bools([true, true, true, true, true, true]) ); 
console.log( addon.bools([false, false, false, false, false, false]) ); 
console.log( addon.objects([
  {
    height: 100,
    width: 200
  }, {
    height: 400,
    width: 200
  }, {
    height: 300,
    width: 300
  }, {
    height: 1000,
    width: 1,
    length: 50
  } 
]) );

addon.functions([function(msg1){
  console.log(msg1);
}, function(msg2) {
  console.log(msg2);
}, function(msg3) {
  console.log(msg3); 
}]);
