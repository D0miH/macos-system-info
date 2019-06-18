const testAddon = require("./build/Release/smcnodekit.node");

console.log("addon", testAddon.test());
module.exports = testAddon;
