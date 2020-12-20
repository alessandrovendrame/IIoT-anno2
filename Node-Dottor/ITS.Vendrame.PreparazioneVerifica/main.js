"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
exports.__esModule = true;
var fastify = require("fastify");
var bcrypt = require("bcrypt");
var jwt = require("fastify-jwt");
var mysql = require("mysql");
var saltRounds = 10;
var connection = mysql.createPool({
    connectionLimit: 10,
    host: 'localhost',
    user: 'root',
    password: 'Vmware1!',
    database: 'dbaccomodation'
});
var app = fastify({ logger: true });
//Registrazione token jwt
app.register(jwt, {
    secret: 'supersecret'
});
//POST - /api/accomodation/register
//post per registrare una struttura
//
app.post('/api/accomodation/register', function (request, reply) {
    var accomodation = request.body;
    accomodation.Password = bcrypt.hashSync(accomodation.Password, saltRounds);
    connection.query("insert into tblAccomodation set ?", accomodation, function (error, results, fields) {
        if (error) {
            reply.status(500).send({ error: error.message });
            return;
        }
        reply.status(200).send();
    });
});
//POST - /api/Token
//post per ottenere JwtToken
//
app.post('/api/token', function (request, reply) {
    var accomodation = request.body;
    var passwordHash = bcrypt.hashSync(accomodation.Password, saltRounds);
    console.log('passwordHash: ' + passwordHash);
    connection.query("select * from tblAccomodation where Username= ?", accomodation.Username, function (error, results, fields) {
        if (error) {
            reply.status(500).send({ error: error.message });
            return;
        }
        else if (results.length > 0) {
            bcrypt.compare(accomodation.Password, results[0].Password, function (err, result) {
                if (result) {
                    var accomodation = {
                        Username: results[0].Username,
                        IdAccomodation: results[0].IdAccomodation
                    };
                    console.log("L'id è: " + results[0].IdAccomodation);
                    var token = app.jwt.sign({ payload: accomodation });
                    reply.send({ token: token });
                }
                else {
                    reply.status(401).send({
                        statusCode: 401,
                        error: "Unauthorized",
                        message: "Inavalid  password."
                    });
                }
            });
        }
        else {
            reply.status(401).send({
                statusCode: 401,
                error: "Unauthorized",
                message: "Inavalid  Username."
            });
        }
        ;
    });
});
//funzione che controlla il token e permette di chiamare le altre funzioni nel caso in cui il token fosse valido
app.register(function (x, opts) {
    return __awaiter(this, void 0, void 0, function () {
        var _this = this;
        return __generator(this, function (_a) {
            x.addHook("onRequest", function (request, reply) { return __awaiter(_this, void 0, void 0, function () {
                var err_1;
                return __generator(this, function (_a) {
                    switch (_a.label) {
                        case 0:
                            _a.trys.push([0, 2, , 3]);
                            return [4 /*yield*/, request.jwtVerify()];
                        case 1:
                            _a.sent();
                            return [3 /*break*/, 3];
                        case 2:
                            err_1 = _a.sent();
                            reply.send(err_1);
                            return [3 /*break*/, 3];
                        case 3: return [2 /*return*/];
                    }
                });
            }); });
            //GET - /api/:accomodationId/booking
            //lettura di tutte le prenotaioni di una struttura
            //
            x.get("/api/:accomodationId/booking", {
                schema: {
                    params: {
                        accomodationId: { type: 'number' }
                    }
                }
            }, function (request, reply) {
                connection.query("select * from tblbooking where AccomodationId = ?", request.params.accomodationId, function (error, results, fields) {
                    if (error) {
                        reply.status(500).send({ error: error.message });
                        return;
                    }
                    reply.send(results);
                });
            });
            //GET - /api/:accomodationId/booking/:bookingId
            //lettura di una prenotazione
            //
            x.get("/api/:accomodationId/booking/:bookingId", {
                schema: {
                    params: {
                        accomodationId: { type: 'number' },
                        bookingId: { type: 'number' }
                    }
                }
            }, function (request, reply) {
                connection.query("select * from tblbooking where AccomodationId = ? and IdBooking = ?", [request.params.accomodationId, request.params.bookingId], function (error, results, fields) {
                    if (error) {
                        reply.status(500).send({ error: error.message });
                        return;
                    }
                    reply.send(results);
                });
            });
            //POST - /api/:accomodationId/booking
            //inserimento di una prenotazione
            //
            x.post("/api/:accomodationId/booking", {
                schema: {
                    params: {
                        accomodationId: { type: 'number' }
                    }
                }
            }, function (request, reply) {
                var booking = request.body;
                booking.AccomodationId = request.params.accomodationId;
                connection.query("insert into tblbooking set ?", booking, function (error, results, fields) {
                    if (error) {
                        reply.status(500).send({ error: error.message });
                        return;
                    }
                    reply.send(results);
                });
            });
            //PUT - api/:accomodationId/booking/:bookingId
            //modifica di una prenotazione
            //
            x.put("/api/:accomodationId/booking/:bookingId", {
                schema: {
                    params: {
                        accomodationId: { type: 'number' },
                        bookingId: { type: 'number' }
                    }
                }
            }, function (request, reply) {
                var booking = request.body;
                booking.AccomodationId = request.params.accomodationId;
                booking.IdBooking = request.params.bookingId;
                connection.query("UPDATE tblbooking SET ? WHERE IdBooking = ?", [booking, booking.IdBooking], function (error, results, fields) {
                    if (error) {
                        reply.status(500).send({ error: error.message });
                        return;
                    }
                    reply.send(results);
                });
            });
            //DELETE - /api/:accomodationId/booking/:id
            //Cancellazione di una prenotazione
            //
            x["delete"]("/api/:accomodationId/booking/:bookingId", {
                schema: {
                    params: {
                        accomodationId: { type: 'number' },
                        bookingId: { type: 'number' }
                    }
                }
            }, function (request, reply) {
                var booking = request.body;
                booking.AccomodationId = request.params.accomodationId;
                booking.IdBooking = request.params.bookingId;
                connection.query("DELETE FROM tblBooking WHERE IdBooking = ?", [booking.IdBooking], function (error, results, fields) {
                    if (error) {
                        reply.status(500).send({ error: error.message });
                        return;
                    }
                    reply.send(results);
                });
            });
            return [2 /*return*/];
        });
    });
});
//apertura porte di ascolto
app.listen(3000, function (err, address) {
    if (err)
        throw err;
    app.log.info('Server listening on: ' + address);
});
//----Classi per la comunicazione con il DB----
var Accomodation = /** @class */ (function () {
    function Accomodation(IdAccomodation, Name, Address, Username, Password) {
        this.IdAccomodation = IdAccomodation;
        this.Name = Name;
        this.Address = Address;
        this.Username = Username;
        this.Password = Password;
    }
    return Accomodation;
}());
var Booking = /** @class */ (function () {
    function Booking(IdBooking, AccomodationId, StartDate, EndDate, Reference, RoomNumber) {
        this.IdBooking = IdBooking;
        this.AccomodationId = AccomodationId;
        this.StartDate = StartDate;
        this.EndDate = EndDate;
        this.Reference = Reference;
        this.RoomNumber = RoomNumber;
    }
    return Booking;
}());
