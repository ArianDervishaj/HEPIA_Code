import socket
import threading
import random

def generate_rand():
    return random.getrandbits(128)

def calculate_sres(rand, key):
    pass

def a5_encrypt(message, session_key):
    pass

def handle_client(client_socket, client_address, secret_key):
    print(f"Connexion acceptée de {client_address}")

    try:
        rand = generate_rand()
        client_socket.send(str(rand).encode())

        sres_server = calculate_sres(rand, secret_key)
        sres_client = client_socket.recv(1024).decode()
        
        if sres_server == sres_client:
            print("Authentification réussie !")
            
            session_key = "your_session_key_here"
            client_socket.send(session_key.encode())

            while True:
                
                encrypted_message = client_socket.recv(1024).decode()
                if encrypted_message:
                    print(f"Message reçu de {client_address}: {encrypted_message}")
                
                response = input("Entrez votre réponse : ")
                encrypted_response = a5_encrypt(response, session_key)
                client_socket.send(encrypted_response.encode())
        else:
            print("Erreur d'authentification, SRES ne correspondent pas.")
            client_socket.close()

    except:
        print(f"Connexion fermée avec {client_address}")
        client_socket.close()

def server_program():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 9999))
    server_socket.listen(5)
    
    print("Serveur en écoute...")

    secret_key = "your_secret_key_here"  

    while True:
        client_socket, client_address = server_socket.accept()
        client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address, secret_key))
        client_thread.start()

if __name__ == "__main__":
    server_program()
