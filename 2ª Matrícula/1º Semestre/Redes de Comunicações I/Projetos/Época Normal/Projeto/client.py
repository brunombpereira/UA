import socket
import threading

def receive_messages(client_socket):
    while True:
        data = client_socket.recv(1024)
        if not data:
            break
        print(data.decode("utf-8"))

def main():
    host = '208.186.10.2'
    port = 9999

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((host, port))

    # Inicia uma thread para receber mensagens do servidor
    receive_thread = threading.Thread(target=receive_messages, args=(client,))
    receive_thread.start()

    while True:
        message = input("Digite a mensagem: ")
        client.send(message.encode("utf-8"))

    client.close()

if __name__ == "__main__":
    main()

