// Variables
var serialPortName = "COM7";							// Arduino Serial Port Name
var serial;												// Serial Port Object
var sensor1, sensor2, sensor3;      					// Values for US_sensor1, US_sensor 2 and US_sensor 3
var instrument11, instrument12, instrument13;			// Values for instrument1 Note 1, Note 2 and Note 3
var instrument21, instrument22, instrument23;			// Values for instrument2 Note 1, Note 2 and Note 3
var instrument31, instrument32, instrument33;			// Values for instrument3 Note 1, Note 2 and Note 3


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
		// Ultrasonic Sensor
		sensor1 = JSON.parse(rawData).us1;
		sensor2 = JSON.parse(rawData).us2;
		sensor3 = JSON.parse(rawData).us3;
		// Instrument 1
		instrument11 = JSON.parse(rawData).instrument1_Note1;
		instrument12 = JSON.parse(rawData).instrument1_Note2;
		instrument13 = JSON.parse(rawData).instrument1_Note3;
		// Instrument 2
		instrument21 = JSON.parse(rawData).instrument2_Note1;
		instrument22 = JSON.parse(rawData).instrument2_Note2;
		instrument23 = JSON.parse(rawData).instrument2_Note3;
		// Instrument 3
		instrument31 = JSON.parse(rawData).instrument3_Note1;
		instrument32 = JSON.parse(rawData).instrument3_Note2;
		instrument33 = JSON.parse(rawData).instrument3_Note3;
    }
}

function ardCon() {
	console.log("connected to the arduino!! Listen UP");
}


