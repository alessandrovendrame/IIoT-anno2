import * as mysql from 'mysql';
import * as fastify from 'fastify';
import * as swagger from 'fastify-swagger';

var connection = mysql.createPool({
    connectionLimit: 10,
    host: 'localhost',
    user: 'root',
    password: 'Vmware1!',
    database: 'esame_libri',
});

var app = fastify({ logger: true });

app.register(swagger, {
    routePrefix: '/documentation',
    swagger: {
        info: {
            title: 'Test swagger',
            description: 'testing the fastify swagger api',
            version: '0.1.0'
        },
        externalDocs: {
            url: 'https://swagger.io',
            description: 'Find more info here'
        },
        host: 'localhost:3000',
        schemes: ['http'],
        consumes: ['application/json'],
        produces: ['application/json']
    },
    exposeRoute: true
})

//GET - /api/books
//visualizza tutti i libri presenti nel DB
//
app.get('/api/books', (request, reply) => {

    connection.query("SELECT * FROM books", (error, results, fields) => {
        if (error) {
            reply.status(500).send({ error: error.message });
            return;
        }
        reply.send(results);
    })
});

//GET - /api/books/:id
//visualizza i dati di un singolo libro
//
app.get("/api/books/:id", {
    schema: {
        params: {
            id: { type: 'number' }
        }
    }
},
    (request, reply) => {
        connection.query("SELECT * FROM books WHERE id = ?", [request.params.id], (error, results, fields) => {
            if (error) {
                reply.status(500).send({ error: error.message });
                return;
            }
            reply.send(results);
        })
});

//POST - /api/books
//Inserimento di un libro
//

const bodyItemJsonSchema = {
    type:'object',
    required: ['name','author','price'],
    properties:{
        name: { type: 'string', value: "Harry"},
        author: { type: 'string'},
        price: { type: 'number'},
        imageUrl: { type: 'string'},
        url: { type: 'string'} 
    },
    example: {
        name: "Harry",
        author: "autore",
        price: 25.1,
        imageUrl: "imageUrl",
        url: "url"
    }
}

app.post('/api/books', { schema: { body : bodyItemJsonSchema} } ,(request, reply) => {
    let book = request.body as Book;

    connection.query("INSERT INTO books SET ?", book, (error, results, fields) => {
        if (error) {
            reply.status(500).send({ error: error.message });
            return;
        }
        reply.status(201).send();
    })
});

//PUT - /api/books/:id
//modifica i dati di un libro
//
app.put("/api/books/:id", {
    schema: {
        params: {
            id: { type: 'number' }
        },
        body: bodyItemJsonSchema
    }
},
    (request, reply) => {
        let book = request.body as Book;
        book.Id = request.params.id;

        connection.query("UPDATE books SET ? WHERE id = ?", [book, request.params.id], (error, results, fields) => {
            if (error) {
                reply.status(500).send({ error: error.message });
                return;
            }
            reply.status(200).send();
        })
    });

//DELETE - /api/books/:id
//cancellazione di un libro
//
app.delete("/api/books/:id", {
    schema: {
        params: {
            id: { type: 'number' }
        }
    }
},
    (request, reply) => {
        connection.query("DELETE FROM books WHERE id = ?", [request.params.id], (error, results, fields) => {
            if (error) {
                reply.status(500).send({ error: error.message });
                return;
            }
            reply.status(200).send();
        })
    });

//apertura porte di ascolto
app.listen(3000, (err, address) => {
    if (err) throw err
    app.log.info('Server listening on: ' + address)
});

//----Classi per la comunicazione con il DB----
//
class Book {
    constructor(
        public Id: number,
        public Name: string,
        public Author: string,
        public Price: number,
        public ImageUrl: string,
        public Url: string
    ) { }
}