import logo from './logo.svg';
import './App.css';
import { Button } from 'react-bootstrap';
import { useState, useEffect } from 'react';
import { func } from 'prop-types';
import axios from 'axios';
import io from 'socket.io-client';
// socket connection from env
const socket = io("http://203.161.63.57:6969");
function App() {

  const [message, setMessage] = useState('');
  const [receivedMessage, setReceivedMessage] = useState('');

  // Listen for messages from the server
  useEffect(() => {
    socket.on('messageToDevices', (message) => {
      setReceivedMessage(message);
    });

    return () => {
      socket.off('messageToDevices');
    };
  }, []);

  const sendMessage = () => {
    // Send the message to the server
    socket.emit('messageFromWebApp', message);
  };

  return (
    <div className="App">
      <header className="App-header">
        <div>
        <h1>
          IoT Digital Clock {receivedMessage}
        </h1>
        <input onChange={
          (event) => {
            setMessage(event.target.value);
          }
        } className='Nogger' type="text" placeholder="Write your message" />
        <Button onClick={
          (e) => {
            sendMessage();
          }
        } className="kosOmak">Send</Button>
        </div>
      </header>
    </div>
  );
}

export default App;
