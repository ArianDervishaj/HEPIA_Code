import socket
import threading

def calculate_sres(rand, key):
    pass

def a5_encrypt(message, session_key):
    pass

def receive_messages(client_socket, session_key):
    while True:
        try:
            encrypted_message = client_socket.recv(1024).decode()
            if encrypted_message:
                print(f"Message du serveur: {encrypted_message}")
        except:
            print("Connexion fermée par le serveur")
            client_socket.close()
            break

def client_program():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 9999))

    secret_key = "your_secret_key_here"

    try:

        rand = int(client_socket.recv(1024).decode())


        sres_client = calculate_sres(rand, secret_key)
        

        client_socket.send(sres_client.encode())


        session_key = client_socket.recv(1024).decode()

        if session_key:
            print("Authentification réussie, envoi de messages...")

    
            receive_thread = threading.Thread(target=receive_messages, args=(client_socket, session_key))
            receive_thread.start()

            while True:
        
                message = input("Entrez votre message : ")
                encrypted_message = a5_encrypt(message, session_key)
                client_socket.send(encrypted_message.encode())
    except:
        print("Connexion fermée")
        client_socket.close()

if __name__ == "__main__":
    client_program()
