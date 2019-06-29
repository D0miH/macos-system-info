const natives = require('./build/Release/smcnodekit.node');

const SMCNodeKit = new natives.SMCNodeKit();
SMCNodeKit.open();
console.log(SMCNodeKit.isOnAc());
SMCNodeKit.close();
