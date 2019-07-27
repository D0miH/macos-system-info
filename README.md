# macos-system-info

[![Build Status](https://img.shields.io/travis/D0miH/macos-system-info.svg?style=flat-square)](https://travis-ci.org/D0miH/macos-system-info) [![npm](https://img.shields.io/npm/v/macos-system-info.svg?style=flat-square)](https://www.npmjs.com/package/macos-system-info)

### Library to easily read system information about your mac using Node.js

## Installation

```sh
npm install macos-system-info
```

or

```sh
yarn add macos-system-info
```

## Documentation

You can find the documentation [here](https://d0mih.github.io/macos-system-info/).

## Usage

This little code snipped shows how to read the current CPU temperature:

```javascript
// import the class
const { SystemInfo } = require('macos-system-info');

// create a new instance of the class and open the connection to the SMC
const systemInfo = new SystemInfo();
systemInfo.open();

// read the cpu temperature
console.log(systemInfo.getCpuTemp());

// close the connection to the SMC
systemInfo.close();
```

If you are using typescript you can use named imports:

```javascript
// import the class
import { SystemInfo } from 'macos-system-info';

// create a new instance of the class and open the connection to the SMC
const systemInfo: SystemInfo = new SystemInfo();
systemInfo.open();

// read the cpu temperature
console.log(systemInfo.getCpuTemp());

// close the connection to the SMC
systemInfo.close();
```
