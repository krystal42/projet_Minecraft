var fs = require('fs');
fs.readFile('test.json', function (err, data)
{
 if (err)
 throw err; // Vous pouvez gérer les erreurs avant de parser le JSON
 var ledValues = JSON.parse(data);
    console.log('r = ' + ledValues.r + ' & g = ' + ledValues.g + ' &  b = ' + ledValues.b);
var http = require ('http');
var req = http.get("http://192.168.0.114/urlColor?r=" + ledValues.r  + "&g=" + ledValues.g + "&b=" + ledValues.b);
    });
