// Variables
var serialPortName = "COM7";									// Arduino Serial Port Name
var serial;														// Serial Port Object
var US_instrument1, US_instrument2, US_instrument3;      		// Values for US_sensor1, US_sensor 2 and US_sensor 3
var instrument11, instrument12, instrument13;					// Values for instrument1 Note 1 Key, Note 2 Key ,and Note 3 Key
var instrument21, instrument22, instrument23;					// Values for instrument2 Note 1 Key, Note 2 Key ,and Note 3 Key
var instrument31, instrument32, instrument33;					// Values for instrument3 Note 1 Key, Note 2 Key ,and Note 3 Key
var instrument1Note1, instrument1Note2, instrument1Note3;		// Audios for instrument1 Note 1 Key, Note 2 Key ,and Note 3 Key
var instrument2Note1, instrument2Note2, instrument2Note3;		// Audios for instrument2 Note 1 Key, Note 2 Key ,and Note 3 Key
var instrument3Note1, instrument3Note2, instrument3Note3;		// Audios for instrument3 Note 1 Key, Note 2 Key ,and Note 3 Key
var beat;														// Audio for beats
var volume11, volume12, volume13;								// Volumes for instrument1 Note 1 Key, Note 2 Key ,and Note 3 Key
var volume21, volume22, volume23;								// Volumes for instrument1 Note 1 Key, Note 2 Key ,and Note 3 Key
var volume31, volume32, volume33;								// Volumes for instrument1 Note 1 Key, Note 2 Key ,and Note 3 Key
var volume;														// Volume for beats

function preload() {
	// Preload audios
    instrument1Note1 = loadSound('audio/guitarA.mp3');
    instrument1Note2 = loadSound('audio/guitarB.mp3');
    instrument1Note3 = loadSound('audio/guitarC.mp3');
	
    instrument2Note1 = loadSound('audio/pianoC.mp3');
    instrument2Note2 = loadSound('audio/pianoD.mp3');
    instrument2Note3 = loadSound('audio/pianoG.mp3');
	
    instrument3Note1 = loadSound('audio/bassA.mp3');
    instrument3Note2 = loadSound('audio/bassC.mp3');
    instrument3Note3 = loadSound('audio/bassE.mp3');
	
    beat = loadSound('audio/beat.mp3');
}

function setup() {
	// Background
	createCanvas(windowWidth, windowHeight);
    background(0, 0, 0);
	
	// Setting up the serial port
	serial = new p5.SerialPort();     // Create the serial port object
	serial.open(serialPortName);		// Open the arduino serial port 
	serial.on('open',ardCon);         // Open the socket connection and execute the ardCon callback
	serial.on('data',dataReceived);   // When data is received, execute the dataReceived function
}

function draw() {
    // Play the beat depnding on the distance of people
    if ( US_instrument1 <= 150 || US_instrument2 <= 150 || US_instrument3 <= 150 ) {
        if ( beat.isPlaying() ) {
            if ( US_instrument1 <= 100 || US_instrument2 <= 100 || US_instrument3 <= 100 ) {
                volume = 0.5;
            } else if ( US_instrument1 <= 50 || US_instrument2 <= 50 || US_instrument3 <= 50 ) {
                volume = 1.0;
            } else {
                volume = (150 - min(US_instrument1, US_instrument2, US_instrument3))/100;
            }
            beat.setVolume(volume);
        } else {
            if ( US_instrument1 <= 100 || US_instrument2 <= 100 || US_instrument3 <= 100 ) {
                volume = 0.5;
            } else if ( US_instrument1 <= 50 || US_instrument2 <= 50 || US_instrument3 <= 50 ) {
                volume = 1.0;
            } else {
                volume = (150 - min(US_instrument1, US_instrument2, US_instrument3))/100;
            }
            beat.play();
            beat.setVolume(volume);
        }
    }
    
    // Audio and Splash
    //---------------------------------- Instrument 1 ----------------------------------//
    if ( instrument11 == 1 ){
        if ( instrument1Note1.isPlaying() ) {
            if ( volume11 <= 0.7 ){
                volume11 = volume11 + 0.1;
                instrument1Note1.setVolume(volume11);
                
            }
        } else {
            volume11 = 0.1;
            instrument1Note1.play();
            instrument1Note1.setVolume(volume11);
            splash();
        }
    }
    if ( instrument12 == 1 ){
        if ( instrument1Note2.isPlaying() ) {
            if ( volume12 <= 0.7 ){
                volume12 = volume12 + 0.1;
                instrument1Note2.setVolume(volume12);
                
            }
        } else {
            volume12 = 0.1;
            instrument1Note2.play();
            instrument1Note2.setVolume(volume12);
            splash();
        }
    }
    if ( instrument13 == 1 ){
        if ( instrument1Note3.isPlaying() ) {
            if ( volume13 <= 0.7 ){
                volume13 = volume13 + 0.1;
                instrument1Note3.setVolume(volume13);
                
            }
        } else {
            volume13 = 0.1;
            instrument1Note3.play();
            instrument1Note3.setVolume(volume13);
            splash();
        }
    }
    //---------------------------------- Instrument 2 ----------------------------------//
    if ( instrument21 == 1 ){
        if ( instrument2Note1.isPlaying() ) {
            if ( volume21 <= 0.9 ){
                volume21 = volume21 + 0.1;
                instrument2Note1.setVolume(volume21);
                
            }
        } else {
            volume21 = 0.1;
            instrument2Note1.play();
            instrument2Note1.setVolume(volume21);
            splash();
        }
    }
    if ( instrument22 == 1 ){
        if ( instrument2Note2.isPlaying() ) {
            if ( volume22 <= 0.9 ){
                volume22 = volume22 + 0.1;
                instrument2Note2.setVolume(volume22);
                
            }
        } else {
            volume22 = 0.1;
            instrument2Note2.play();
            instrument2Note2.setVolume(volume22);
            splash();
        }
    }
    if ( instrument23 == 1 ){
        if ( instrument2Note3.isPlaying() ) {
            if ( volume23 <= 0.9 ){
                volume23 = volume23 + 0.1;
                instrument2Note3.setVolume(volume23);
                
            }
        } else {
            volume23 = 0.1;
            instrument2Note3.play();
            instrument2Note3.setVolume(volume23);
            splash();
        }
    }
    //---------------------------------- Instrument 3 ----------------------------------//
    if ( instrument31 == 1 ){
        if ( instrument3Note1.isPlaying() ) {
            if ( volume31 <= 0.9 ){
                volume31 = volume31 + 0.1;
                instrument3Note1.setVolume(volume31);
                
            }
        } else {
            volume31 = 0.1;
            instrument3Note1.play();
            instrument3Note1.setVolume(volume31);
            splash();
        }
    }
    if ( instrument32 == 1 ){
        if ( instrument3Note2.isPlaying() ) {
            if ( volume32 <= 0.9 ){
                volume32 = volume32 + 0.1;
                instrument3Note2.setVolume(volume32);
                
            }
        } else {
            volume32 = 0.1;
            instrument3Note2.play();
            instrument3Note2.setVolume(volume32);
			splash();
        }
    }
    if ( instrument33 == 1 ){
        if ( instrument3Note3.isPlaying() ) {
            if ( volume33 <= 0.9 ){
                volume33 = volume33 + 0.1;
                instrument3Note3.setVolume(volume33);
                
            }
        } else {
            volume33 = 0.1;
            instrument3Note3.play();
            instrument3Note3.setVolume(volume33);
            splash();
        }
    }
}

function splash() {
    var size, xPosition, yPosition;
    var offsetX, offsetY, plusOrMinus;
    
    // Choose colour based on the instrument
    fill(getColor());
    
    // Draw the main drop
    noStroke();
    xPosition = random(windowWidth);
    yPosition = random(windowHeight);
    size = random(10,200);
    ellipse(xPosition, yPosition, size, size);
    
    for(var i = 0; i < 10; i++){
        plusOrMinus = Math.random() < 0.5 ? -1 : 1;
        offsetX = (random(size)) * plusOrMinus;
        plusOrMinus = Math.random() < 0.5 ? -1 : 1;
        offsetY = (random(size)) * plusOrMinus;
        ellipse(xPosition+offsetX, yPosition+offsetY, random(size)/2, random(size)/2);
    }
}

function getColor(){
  var rRed, rBlue, rGreen;
    
    // Instrument 1 is Red
    if ( instrument11 == 1 || instrument12 == 1 || instrument13 == 1 ){
        rRed = 255;
        rBlue = 0;
        rGreen = 0;
    } 
    // Instrument 2 is Green
    else if ( instrument21 == 1 || instrument22 == 1 || instrument23 == 1 ){
        rRed = 0;
        rBlue = 0;
        rGreen = 255;        
    } 
    // Instrument 3 is Blue
    else if ( instrument31 == 1 || instrument32 == 1 || instrument33 == 1 ){
        rRed = 0;
        rBlue = 255;
        rGreen = 0;
    } 
    // Keep colour same as background when an instrument is not chosen
    else {
        rRed = 0;
        rBlue = 0;
        rGreen = 0;        
    }
    
  return color(rRed, rBlue, rGreen);
}

function windowResized() {
	resizeCanvas(windowWidth, windowHeight);
    background(0, 0, 0);
}


// Data coming from Arduino
function dataReceived() {	
	var rawData = serial.readStringUntil('\r\n');					// Read the incoming string until it sees a newline       
    if( rawData.length > 1){										// If there is something in the string
		//console.log(rawData);  
		
		// Ultrasonic Sensor
		US_instrument1 = JSON.parse(rawData).us1;
		US_instrument2 = JSON.parse(rawData).us2;
		US_instrument3 = JSON.parse(rawData).us3;
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