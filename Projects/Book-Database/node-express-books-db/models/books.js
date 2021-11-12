const mongoose = require('mongoose');

let Schema = mongoose.Schema;

let BookSchema = new Schema( {
    title: String,
    description: String,
    year: Number,
    author: String,
    hardCover: Boolean,
    price: Number
});

module.exports = mongoose.model('Book', BookSchema);
// const mongoose = require('mongoose');
//
// let Schema = mongoose.Schema;
//
// let StudentSchema = new Schema({
//     firstName: String,
//     lastName: String,
//     gpa: Number,
//     credits: Number,
//     major: String
// });
//
// module.exports = mongoose.model('Student', StudentSchema);