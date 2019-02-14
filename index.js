var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
const screenshot = require('screenshot-desktop')

app.get('', function(req, res){
    console.log("testasdasdasd")
    //res.send("test")
    res.sendFile(__dirname + '/index.html');
  });

io.on('connection', function(socket){
    console.log('a user connected');
    socket.on('disconnect', function(){
      console.log('user disconnected');
    });
});

http.listen(80, '0.0.0.0', function(){
  console.log('listening on *:80');
});

var async = require("async");

var delay = (1/30)*1000;

async.forever(

    function(next) {
        screenshot().then((img) => {
            io.emit('chat message', img.toString('base64'))
            setTimeout(function() {
                next();
            }, delay)
        }).catch((err) => { })
    },
    function(err) {
        console.error(err);
    }
);
