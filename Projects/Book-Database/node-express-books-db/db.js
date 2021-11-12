// const MongoClient = require('mongodb').MongoClient;
//
// const uri = "mongodb+srv://user-13:m97zcguwhakwp4@cluster0.bzm1t.mongodb.net/Cluster0?retryWrites=true&w=majority";
//
// const client = new MongoClient(uri, { useNewUrlParser: true, useUnifiedTopology: true });
//
// client.connect(err => {
//     const collection = client.db("test").collection("devices");
//     // perform actions on the collection object
//     client.close();
// });
// const mongoose = require('mongoose');
//
// // Where does this come from?
// const mongoDB = process.env.MONGODB_URI || 'mongodb+srv://user-13:m97zcguwhakwp4@cluster0.bzm1t.mongodb.net/Cluster0?retryWrites=true&w=majority';
//
// // What is this syntax about?
// mongoose
//     .connect(mongoDB, {useNewUrlParser: true, useUnifiedTopology: true})
//     .then(() => {
//         console.log('DB Connected!');
//     })
//     .catch(error => {
//         console.log('Connection Error: ${err.message}');
//     });
//
// const db = mongoose.connection;
//
// // Bind the console to errors, to show them on console
// db.on('error', console.error.bind(console, 'MongoDB Connection Error'));
//
// module.exports = db;
//
const mongoose = require('mongoose');

// Where does this come from?
const mongoDB = process.env.MONGODB_URI || 'mongodb+srv://user-13:m97zcguwhakwp4@cluster0.bzm1t.mongodb.net/Cluster0?retryWrites=true&w=majority';

// What is this syntax about?
mongoose
    .connect(mongoDB, {useNewUrlParser: true, useUnifiedTopology: true})
    .then(() => {
        console.log('DB Connected!');
    })
    .catch(error => {
        console.log('Connection Error: ${err.message}');
    });

const db = mongoose.connection;

// Bind the console to errors, to show them on console
db.on('error', console.error.bind(console, 'MongoDB Connection Error'));

module.exports = db;
