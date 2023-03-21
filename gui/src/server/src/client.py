import socket
import threading

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('127.0.0.1', 5050))

def receive():
    while True:
        try:
            message = client.recv(1024).decode('ascii')
            print(message)
        except:
            print("An error has occured in the client")
            client.close()
            break

receive__thread = threading.Thread(target=receive)
receive__thread.start()

