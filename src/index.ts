const { SMCNodeKit } = require('../build/Release/smcnodekit.node');

const smc = new SMCNodeKit();
smc.open();
console.log('SMCNodeKit', smc.isOnAC());
smc.close();
module.exports = SMCNodeKit;
