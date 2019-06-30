# smc-node-kit

[![Build Status](https://img.shields.io/travis/D0miH/smc-node-kit.svg?style=flat-square)](https://travis-ci.org/D0miH/smc-node-kit) [![npm](https://img.shields.io/npm/v/smc-node-kit.svg?style=flat-square)](https://www.npmjs.com/package/smc-node-kit)

### Library to easily communicate with the Apple SMC through Node.js

## Installation

```sh
npm install smc-node-kit
```

or

```sh
yarn add smc-node-kit
```

## Documentation

You can find the documentation [here](https://d0mih.github.io/smc-node-kit/).

## Usage

This little code snipped shows how to read the current CPU temperature:

```javascript
// import the class
const { SMCNodeKit } = require('smc-node-kit');

// create a new instance of the class and open the connection to the SMC
const smcKit = new SMCNodeKit();
smcKit.open();

// read the cpu temperature
console.log(smcKit.getCpuTemp());

// close the connection to the SMC
smcKit.close();
```

If you are using typescript you can use named imports:

```javascript
// import the class
import { SMCNodeKit } from 'smc-node-kit';

// create a new instance of the class and open the connection to the SMC
const smcKit: SMCNodeKit = new SMCNodeKit();
smcKit.open();

// read the cpu temperature
console.log(smcKit.getCpuTemp());

// close the connection to the SMC
smcKit.close();
```
