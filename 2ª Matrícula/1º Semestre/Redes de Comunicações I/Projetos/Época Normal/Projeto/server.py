import socket
import threading

# Dicionário para armazenar informações sobre os clientes
clients_info = {}
lock = threading.Lock()

def handle_client(client_socket, addr):
    global clients_info

    print(f"Conexão recebida de {addr}")

    with lock:
        # Adiciona informações do cliente ao dicionário
        clients_info[addr] = clients_info.get(addr, 0) + 1

    while True:
        # Aguarda mensagem do cliente
        data = client_socket.recv(1024)
        if not data:
            break

        message = data.decode("utf-8")
        print(f"Recebido de {addr}: {message}")

        # Envia a mensagem para todos os clientes conectados
        with lock:
            for client_addr, _ in clients_info.items():
                if client_addr != addr:
                    try:
                        client_socket.sendto(f"{addr}: {message}".encode("utf-8"), client_addr)
                    except Exception as e:
                        print(f"Erro ao enviar para {client_addr}: {e}")
                        continue

    # Remove informações do cliente ao desconectar
    with lock:
        del clients_info[addr]

    print(f"Conexão fechada por {addr}")
    client_socket.close()

def main():
    host = '0.0.0.0'
    port = 9999

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)

    print(f"Servidor escutando em {host}:{port}")

    while True:
        client_socket, addr = server.accept()
        client_handler = threading.Thread(target=handle_client, args=(client_socket, addr))
        client_handler.start()

if __name__ == "__main__":
    main()
