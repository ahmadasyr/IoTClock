require('dotenv').config();
const express = require('express');
const http = require('http');
const { Server } = require('socket.io'); // Corrected this line
const cors = require('cors'); // Add this line
const app = express();
app.use(express.json());
app.use(cors()); // Enable CORS for all routes
app.use(express.static('public'));
const server = http.createServer(app);
const io = new Server(server, {
  cors: {
    origin: 'http://localhost:3000', // Replace with the actual origin of your React app
    methods: ['GET', 'POST'],
  },
});

// Socket.io connection handling
io.on('connection', (socket) => {
  console.log('A user connected');

  // Listen for messages from the web app
  socket.on('messageFromWebApp', (message) => {
    console.log('Message from web app:', message);

    // Broadcast the message to all connected devices
    io.emit('messageToDevices', message);
  });

  // Handle disconnection
  socket.on('disconnect', () => {
    console.log('User disconnected');
  });
});

// Start the server
const PORT = process.env.PORT || 6969;
server.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
