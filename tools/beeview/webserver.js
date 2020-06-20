#!/usr/bin/env node

// index.js
var express = require('express');  
var app = express();  
var server = require('http').createServer(app);  
var io = require('socket.io')(server);

var amqp = require('amqplib/callback_api');
var path = require('path');

// determine our client directory
var wwwDir = '';
if(__dirname.endsWith('bin')) {
  // if the script is installed, then the html is located 
  // under the shared directory of the install
  wwwDir = path.join(__dirname,'..','share','www');
} else {
  // otherwise its in the repo location relative to this script
  wwwDir = path.join(__dirname,'client','html');
}
console.log("seeing www dir to " + wwwDir)

app.use(express.static(__dirname + '/node_modules'));  
app.use(express.static(wwwDir));

app.get('/', function(req, res,next) {  
    console.log('index requested: ' + path.join(wwwDir, index.html));
    console.log('old index requested: ' + __dirname + "index.html");  
    res.sendFile(path.join(wwwDir, index.html));
    res.sendFile(path.join(__dirname, index.html));
});

io.on('connection', function(socket){
  socket.on('chat message', function(msg){
    io.emit('chat message', msg)
  });

  amqp.connect('amqp://localhost', function(err, conn) {
    console.log('index.js: connected to amqp');
    conn.createChannel(function(err, ch) {
      var q = 'traces';
      console.log('index.js: traces channel created');
    
      ch.assertQueue(q, {durable: false});
      console.log(" [*] Waiting for messages in %s. To exit press CTRL+C", q);
      ch.consume(q, function(msg) {
        //console.log(" [x] Received %s", msg.content.toString());
        io.emit('trace item', msg.content.toString());
      }, {noAck: true});
    });

    conn.createChannel(function(err, ch) {
      var q = 'registry';
      console.log('index.js: registry channel created');
    
      ch.assertQueue(q, {durable: false});
      console.log(" [*] Waiting for messages in %s. To exit press CTRL+C", q);
      ch.consume(q, function(msg) {
        //console.log(" [-] Received %s", msg.content.toString());
        io.emit('registry item', msg.content.toString());
      }, {noAck: true});
    });
  });
});

var port = 4200
if(process.argv.length > 2){
  port = parseInt(process.argv[2]);
  console.log("requesting on port *: " + port);
}


server.listen(port, function(){
    console.log('listening on port*: ' + port);
  });