// Variables
var serialPortName = "COM7";		// Arduino Serial Port Name
var serial;							// Serial Port Object
var sensor1, sensor2, sensor3;      // Values for sensor1, sensor 2 and sensor 3

function setup() {
	createCanvas(500,500);
	
	// Setting up the serial port
	serial = new p5.SerialPort();     // Create the serial port object
	serial.open(serialPortName);		// Open the arduino serial port 
	serial.on('open',ardCon);         // Open the socket connection and execute the ardCon callback
	serial.on('data',dataReceived);   // When data is received, execute the dataReceived function
}

function draw() {
	background(255);
	stroke(0);
	
	/*
	if(sensor1 == 0){
		fill(255,0,0);
	} else {
		fill(0,255,0);
    }
	
	if(sensor2 == 0){
		fill(255,0,0);
	} else {
		fill(0,255,0);
    }
	
	if(sensor3 == 0){
		fill(255,0,0);
	} else {
		fill(0,255,0);
    }*/
}


function dataReceived() {
	var rawData = serial.readStringUntil('\r\n');	// Read the incoming string until it sees a newline
    //console.log(rawData);         
    if( rawData.length > 1){						// If there is something in the string
		sensor1 = JSON.parse(rawData).us1;
		sensor2 = JSON.parse(rawData).us2;
		sensor3 = JSON.parse(rawData).us3;
    }
}

function ardCon() {
	console.log("connected to the arduino!! Listen UP");
}


