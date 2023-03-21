import threading
import socket
import serial
import datetime
import time

#SERVER = socket.gethostbyname(socket.gethostname()) #local host
SERVER = '127.0.0.1';
PORT = 5050;
ADDR = (SERVER, PORT);

SERIAL_PORT = 'COM3';
DATA_AMOUNT = 20; # taking 20 datapoints in

ser = serial.Serial(SERIAL_PORT)
ser.flushInput()


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(ADDR) #bind to local host:port
server.listen() #litsen for new connections

clients = [] #current clients


# read serial data
def readData()-> str:
    ser.flushInput()
    ser_bytes = ser.readline()
    return str(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))



def broadcast(message):
    for client in clients:
        client.send(message)


def handle(client):
    while True:
        try:
            message = client.recv(1024)
            if message == '0':
                timestamp = datetime.datetime.now().strftime("%I:%M:%S %P")
                client.send(timestamp)
                time.sleep(2)
            broadcast(message)
        except:
            index = clients.index(client)
            clients.remove(client)
            client.close()
            broadcast(f'{client} left the chat'.encode('ascii'))
            break

def receive():
    import time
    print("test")
    while True:
        client, address = server.accept()
        print(f"Connected with {str(address)}")
        clients.append(client)
        client.send('Connected to the server!'.encode('ascii'))
        broadcast(f'Someone joined the chat!'.encode('ascii'))
        #broadcast(readData().encode('ascii'))
        thread = threading.Thread(target=handle, args=(client,))
        thread.start()
        while True:
            client.send(readData().encode('ascii'))
        

print("Client Connected")
receive()
