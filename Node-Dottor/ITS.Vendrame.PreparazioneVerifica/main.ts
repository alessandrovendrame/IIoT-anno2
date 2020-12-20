import * as fastify from 'fastify';
import * as bcrypt from 'bcrypt';
import * as jwt from 'fastify-jwt';
import * as mysql from 'mysql';

var saltRounds = 10;

var connection = mysql.createPool({
    connectionLimit: 10,
    host: 'localhost',
    user: 'root',
    password: 'Vmware1!',
    database: 'dbaccomodation',
});

var app = fastify({ logger: true });

//Registrazione token jwt
app.register(jwt, {
    secret: 'supersecret'
});

//POST - /api/accomodation/register
//post per registrare una struttura
//
app.post('/api/accomodation/register', (request, reply) => {
    let accomodation = request.body as Accomodation;
    accomodation.Password = bcrypt.hashSync(accomodation.Password, saltRounds);
    connection.query("insert into tblAccomodation set ?", accomodation, (error, results, fields) => {
        if (error) {
            reply.status(500).send({ error: error.message });
            return;
        }
        reply.status(200).send();
    })
});

//POST - /api/Token
//post per ottenere JwtToken
//
app.post('/api/token', (request, reply) => {
    
    let accomodation = request.body as Accomodation;

    let passwordHash = bcrypt.hashSync(accomodation.Password, saltRounds);
    console.log('passwordHash: ' + passwordHash);
    connection.query("select * from tblAccomodation where Username= ?", accomodation.Username, (error, results, fields) => {
        if (error) {
            reply.status(500).send({ error: error.message });
            return;
        }
        else if (results.length > 0) {
            bcrypt.compare(accomodation.Password, results[0].Password, (err, result) => {
                if (result) {
                    var accomodation = {

                        Username: results[0].Username,
                        IdAccomodation: results[0].IdAccomodation
            
                    };
                    console.log("L'id è: " + results[0].IdAccomodation);
                    const token = app.jwt.sign({ payload: accomodation });
                    reply.send({ token });

                }
                else {
                    reply.status(401).send({
                        statusCode: 401,
                        error: "Unauthorized",
                        message: "Inavalid  password."
                    });
                }
            })
        }
        else {
            reply.status(401).send({
                statusCode: 401,
                error: "Unauthorized",
                message: "Inavalid  Username."
            })
        };
    });
});

//funzione che controlla il token e permette di chiamare le altre funzioni nel caso in cui il token fosse valido
app.register(async function (x, opts) {

    x.addHook("onRequest", async (request, reply) => {
        try {
            await request.jwtVerify()
        } catch (err) {
            reply.send(err)
        }
    });

    //GET - /api/:accomodationId/booking
    //lettura di tutte le prenotaioni di una struttura
    //
    x.get("/api/:accomodationId/booking", {
        schema: {
            params: {
                accomodationId: { type: 'number'}
            }
        }
    },
    (request, reply) => {
        connection.query("select * from tblbooking where AccomodationId = ?", request.params.accomodationId, (error, results, fields) => {
            if (error) {
                reply.status(500).send({ error: error.message });
                return;
            }
            reply.send(results);
        })
    });

    //GET - /api/:accomodationId/booking/:bookingId
    //lettura di una prenotazione
    //
    x.get("/api/:accomodationId/booking/:bookingId", {
        schema: {
            params: {
                accomodationId: { type: 'number'},
                bookingId: { type: 'number'}
            }
        }
    },
    (request, reply) => {
        connection.query("select * from tblbooking where AccomodationId = ? and IdBooking = ?", [request.params.accomodationId,request.params.bookingId], (error, results, fields) => {
            if (error) {
                reply.status(500).send({ error: error.message });
                return;
            }
            reply.send(results);
        })
    });

    //POST - /api/:accomodationId/booking
    //inserimento di una prenotazione
    //
    x.post("/api/:accomodationId/booking", {
        schema: {
            params: {
                accomodationId: { type: 'number'}
            }
        }
    },
    (request, reply) => {
        let booking = request.body as Booking;
        booking.AccomodationId = request.params.accomodationId;

        connection.query("insert into tblbooking set ?", booking, (error, results, fields) => {
            if (error) {
                reply.status(500).send({ error: error.message });
                return;
            }
            reply.send(results);
        })
    });

    //PUT - api/:accomodationId/booking/:bookingId
    //modifica di una prenotazione
    //
    x.put("/api/:accomodationId/booking/:bookingId", {
        schema: {
            params: {
                accomodationId: { type: 'number'},
                bookingId: { type: 'number'}
            }
        }
    },
    (request, reply) => {
        let booking = request.body as Booking;
        booking.AccomodationId = request.params.accomodationId;
        booking.IdBooking = request.params.bookingId;

        connection.query("UPDATE tblbooking SET ? WHERE IdBooking = ?", [booking,booking.IdBooking], (error, results, fields) => {
            if (error) {
                reply.status(500).send({ error: error.message });
                return;
            }
            reply.send(results);
        })
    });

    //DELETE - /api/:accomodationId/booking/:id
    //Cancellazione di una prenotazione
    //
    x.delete("/api/:accomodationId/booking/:bookingId", {
        schema: {
            params: {
                accomodationId: { type: 'number'},
                bookingId: { type: 'number'}
            }
        }
    },
    (request, reply) => {
        let booking = request.body as Booking;
        booking.AccomodationId = request.params.accomodationId;
        booking.IdBooking = request.params.bookingId;

        connection.query("DELETE FROM tblBooking WHERE IdBooking = ?", [booking.IdBooking], (error, results, fields) => {
            if (error) {
                reply.status(500).send({ error: error.message });
                return;
            }
            reply.send(results);
        })
    });
});

//apertura porte di ascolto
app.listen(3000, (err, address) => {
    if (err) throw err
    app.log.info('Server listening on: ' + address)
});


//----Classi per la comunicazione con il DB----
class Accomodation{
    constructor(
        public IdAccomodation : number,
        public Name : string,
        public Address : string,
        public Username : string,
        public Password : string
    ){}
}

class Booking{
    constructor(
        public IdBooking : number,
        public AccomodationId : number,
        public StartDate : Date,
        public EndDate : Date,
        public Reference : string,
        public RoomNumber : number
    ){}
}