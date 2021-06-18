const fs = require('fs');
const jsonData = require('./data.json');

class DatiRegioni{
    constructor(codiceRegione, denominazioneRegione, totaleCasi) {
        this.codiceRegione = codiceRegione;
        this.denominazioneRegione = denominazioneRegione;
        this.totaleCasi = totaleCasi;
      }
}

var array = []

jsonData.forEach(element => {
    var dato = new DatiRegioni(element.codice_regione, element.denominazione_regione, element.totale_casi)

    if(!checkIfPresent(dato)){
        array.push(dato);
    }
    
});

console.log(array);

var stringa = JSON.stringify(array);

fs.writeFile('./output.json', stringa, err => {
    if (err) {
      console.error(err)
      return
    }
    //file written successfully
  })

function checkIfPresent(x){
    var pr = false;
    array.forEach(element => {
        if(element.codiceRegione == x.codiceRegione){
            element.totaleCasi += x.totaleCasi;
            pr = true;
        }
    });

    return pr;
}

