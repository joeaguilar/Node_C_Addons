var example = require('bindings')("example.node");

// for (i in bindings) {
//   console.log(i);
// }
console.log(example.number(25));
console.log(example.string("Hi guys"));
console.log(example.bool(true));
console.log(example.array([1,2,3,"hi",true]));
console.log(example.object({name: "Joe", age: 33, occupation: "Programmer"}));
example.function(function(msg){
  console.log("I will get called with " + msg);
});
