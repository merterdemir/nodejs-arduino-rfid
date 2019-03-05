var EventEmitter = require('events');
var app = require('express')();
var http = require('http').Server(app);
var http2 = require('http').Server(app);
var sio = require('socket.io');
var io = sio(http);
var adio = sio(http2);
var events = new EventEmitter();

app.get('/', function(req, res) {
	res.sendFile(__dirname + '/socket_test.html');
});

io.on('connection', function(socket) {
	console.log('a user connected:', socket.id);
    socket.emit('data_response', {'welcome': socket.id});
	events.on('data', function(data) {
        console.log("Sending: " + data);
        socket.emit('data', data);
    });
	socket.on('disconnect', function() {
		console.log('user disconnected');
	});
});

adio.on('connection', function(socket) {
	console.log('Arduino is connected');

	socket.on('data', function(data) {
		console.log("--------");
        console.log("Label: " + data.label);
        console.log("RFID: " + data.rfid);
		events.emit('data', data);
	});
});

http.listen(3000, function() {
	console.log('listening on *:3000');
});

http2.listen(3030, function() {
	console.log('listening for Arduino server on *:3030');
});
