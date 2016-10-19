// advanced.js
var addon = require('bindings')("addon.node");


// console.log(Object.getOwnPropertyNames(addon));
const filepath = __dirname +"/examples/"; 
const filename = "bbycat.jpg";

addon.PerformAction(filepath + filename, filepath + "brighter_" + filename, 10, function () {

  addon.PerformAction(filepath + filename, filepath + "darker_" + filename, -10, function() {
    addon.PerformAction(filepath + filename, filepath + "even_brighter_" + filename, 70, function() {
      console.log("Finished!");
    });
    
  });
  
});


