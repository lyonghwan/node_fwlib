const addon = require('bindings')('node_fwlib');

function javascriptPart (value) {
  const conn = addon.connect(1);
  const result = addon.getMachine('127.0.0.1',8183);
  return result;
}

javascriptPart()