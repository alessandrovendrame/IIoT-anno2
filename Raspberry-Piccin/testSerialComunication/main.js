const { on } = require("events");
const SerialPort = require("serialport")
const ByteLength = require('@serialport/parser-byte-length')

const port = new SerialPort("COM10", { baudRate: 9600 , parity: "none"} );

//con questo parser lavoriamo con 2 byte alla volta
const parser = port.pipe(new ByteLength({length: 1}))
parser.on('data', parseMsg) 

port.on("open", function(){
    console.log("Listening for data...");

    port.on('error', function(err) {
        console.log('Error: ', err.message)
    });

});

function parseMsg(data) {
	console.log(data);

	//per ogni elemento del buffer ricevuto via seriale, estraiamo il valore in binario
	let msgSize = data.length;
	for (let i = 0; i < msgSize; i++) {
		let valore = parseInt(data[i], 10).toString(2);
		//aggiungiamo gli 0 omessi perchè non significanti
		console.log(valore.padStart(8, '0'));
	}
	
	//creiamo due variabili dove inserire il balore binario dei due byte
	let byte0 = parseInt(data[0], 10).toString(2).padStart(8, '0');

    console.log("byte0 = " + byte0)
};