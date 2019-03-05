var app           = require('express')();
var http          = require('http').Server(app);
var http2         = require('http').Server(app);
var sio           = require('socket.io');
var io            = sio(http);
var adio          = sio(http2);
var EventEmitter  = require('events');
var events        = new EventEmitter();
const SerialPort  = require('serialport')
const Readline    = require('@serialport/parser-readline')
const sqlite3     = require('sqlite3').verbose();
const body_parser = require('body-parser');

const port         = 3000;
const db_file      = '/home/pi/site/rfid.db';
const db_test_path = '/Users/Mert/Desktop/Files/Others/RFID/site/rfid.db';
const arduino_port = "/dev/tty.usbmodem14101";

var sp = new SerialPort(arduino_port, {
	baudRate: 9600
	//parser: serialport.parsers.readline("\n")
});
const parser = new Readline();
sp.pipe(parser);

let users_table_style = `
table {
    font-family: 'Courier New', Courier, monospace;
    border-collapse: collapse;
}

td, th, tr{
    border: 1px solid #dddddd;
    text-align: left;
    padding: 8px;
    font-size: 16px;
    font-family: 'Courier New', Courier, monospace;
}

tr:nth-child(even) {
    background-color: #dddddd;
    font-family: 'Courier New', Courier, monospace;
}

table caption {
    font-size: 20px;
    font-weight: bold;
    border: 1px solid #dddddd;
    border-collapse: collapse;
    font-family: 'Courier New', Courier, monospace;
`;

let db = new sqlite3.Database(db_test_path, (err) => {
  if (err) {
    return console.error(err.message);
  }
  console.log('Connected to the SQlite RFID database.');
});

function redirect_callback(fname, lname, rfid, success_flag, err, res) {
	if (success_flag){
		res.redirect('/success?fname=' + fname + '&lname=' + lname + '&rfid=' + rfid);
	}
	else {
		res.redirect('/fail?err=' + err);
	}
}

function registerUser(fname, lname, rfid, callback, res) {
	var sql = 'INSERT INTO USERS (FNAME, LNAME, RFID)';
	sql += 'VALUES (?, ?, ?);';
	db.run(sql, [fname, lname, rfid], function(error) {
		if (error) {
			console.log("Error: " + error);
			console.log("User couldn't added.");
			console.log('Full name: ' + fname + ' ' + lname);
			console.log('RFID: ' + rfid);
			callback(fname, lname, rfid, 0, error, res);
		} else {
			console.log('New User Added:');
			console.log('Full name: ' + fname + ' ' + lname);
			console.log('RFID: ' + rfid);
			callback(fname, lname, rfid, 1, "", res);
		}
    });
};


function listUsers(res){
	var sql = `SELECT FNAME AS fname,
					  LNAME AS lname,
					  RFID AS rfid
			   FROM USERS
			   ORDER BY fname, lname;`;
	
	page  = '<html>';
	page += 	'<head>';
	page += 		'<title>Sign Up RFID</title>';
	page +=         '<style>' + users_table_style + '</style>';
	page +=     '</head>';
	page +=     '<body>';
	page += 		"<table>";
	page +=             "<caption>Users</caption>";
	page += 			"<tr>";
	page += 				"<th>First Name</th>";
	page += 				"<th>Last Name</th>";
	page += 				"<th>RFID</th>";
	page += 			"</tr>";
	db.all(sql, [], (err, rows) => {
		if (err) {
			page += 		"</table>";
			page +=     '</body>';
			page += '</html>';
		}
		
		if (rows) {
			rows.forEach(function (row) {
				page += "<tr>";
				page += 	"<td>" + row.fname + "</td>";
				page += 	"<td>" + row.lname + "</td>";
				page += 	"<td>" + row.rfid + "</td>";
				page += "</tr>";
			});
		}
		page += 		"</table>";
		page +=      	'<a href="/">Go Back to Sign Up Page</a>';
		page +=     '</body>';
		page += '</html>';
		res.send(page);
	});
};

app.use(body_parser.urlencoded({ extended: true }));

app.post('/', (req, res) => {
	var fname = req.body.fname;
	var lname = req.body.lname;
	var rfid  = req.body.rfid;
	if (rfid === "" || fname === "" || lname === "")
		redirect_callback(fname, lname, rfid, 0, "All inputs should be filled.", res);
	else
		registerUser(fname, lname, rfid, redirect_callback, res);
});

app.post('/all_users', (req, res) => {
	listUsers(res);
});

app.get('/all_users', (req, res) => {
	res.sendFile(__dirname + '/index.html');
});


app.get('/', (req, res) => {
	res.sendFile(__dirname + '/index.html');
});

app.get('/fail', (req, res) => {
	res.set('Content-Type', 'text/html');
	page  = '<html>';
	page += 	'<head>';
    page += 		'<title>Sign Up RFID</title>';
    page += 		'<style>body {font-family: "Courier New", Courier, monospace;} </style>';
	page +=     '</head>';
	page +=     '<body>';
	page += 		"<p>User couldn't be added!</p>";
	page +=         '<p>Error: ' + req.query.err + '</p>';
	page +=      	'<a href="/">Go Back to Sign Up Page</a>';
	page +=     '</body>';
	page += '</html>';
	res.send(page);
});

app.get('/success', (req, res) => {
	var fname = req.query.fname;
	var lname = req.query.lname;
	var rfid = req.query.rfid;
	res.set('Content-Type', 'text/html');
	page  = '<html>';
	page += 	'<head>';
    page += 		'<title>Sign Up RFID</title>';
    page += 		'<style>body {font-family: "Courier New", Courier, monospace;} </style>';
	page +=     '</head>';
	page +=     '<body>';
	page += 		'<p>User is successfully added!</p>';
	page +=         '<p>Full name: ' + fname + ' ' + lname + '</p>';
	page +=         '<p>RFID: ' + rfid + '</p>';
	page +=      	'<a href="/">Go Back to Sign Up Page</a>';
	page +=     '</body>';
	page += '</html>';
	res.send(page);
});

io.on('connection', function(socket) {
	console.log('a user connected:', socket.id);
    socket.emit('data_response', {'welcome': socket.id});
	events.on('data', function(data) {
        console.log("Sending: " + data);
        socket.emit('data', data);
        //parser.write('ROBOT POWER ON\n');
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

parser.on('data', line => events.emit('data', {'label': 'rfid', 'rfid': line}));

http.listen(port, function() {
	console.log('listening on *:3000');
});

http2.listen(3030, function() {
	console.log('listening for Arduino server on *:3030');
});
