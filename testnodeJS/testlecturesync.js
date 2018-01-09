'use strict';
const fs = require('fs');
let data = fs.readFileSync('test.json');
let ledValues = JSON.parse(data);
console.log(ledValues.r);
console.log(ledValues.g);
console.log(ledValues.b);
var http = require ('http');
var req = http.get("http://192.168.0.114/urlColor?r=" + ledValues.r  + "&g=" + ledValues.g + "&b=" + ledValues.b);
	
