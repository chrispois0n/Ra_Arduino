const express = require('express');
const socketIo = require('socket.io');
const http = require('http');

const app = express();
const server = http.createServer(app);
const io = socketIo.listen(server);

const SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;
const parser = new Readline();

app.get('/',(rew,res,next) => {
    res.sendFile(__dirname + '/index.html');
});

const mySerial = new SerialPort('COM3', {
    boudRate:9600
});

mySerial.on('open',function() {
    console.log('open serial port puerto abierto');
});


mySerial.on('data',function (data){
    data =  data.toString()
    data = data.split(',')

    console.log(data);
    io.emit('arduino:data', {
        value:{temp:data[0],hum:data[1],luz:data[2],humt:data[3]},             
    });

    io.on('connection',function (socket){
        console.log('a new socket connected');
    });

});

mySerial.on('err', function(){
    console.log(err.message);
});

server.listen(3000, () =>{
    console.log('server on port: ', 3000);
});