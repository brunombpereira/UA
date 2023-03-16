import socket


def main():
    tcp_s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_s.bind(("127.0.0.1", 1234))
    tcp_s.listen(5)

    while True:
        client_socket, client_address = tcp_s.accept()
        print(f"Connection from {client_address}")
        while True:
            data = client_socket.recv(4096)
            if not data:
                break
            client_socket.send(data.upper())
        client_socket.close()

    tcp_S.close()


if __name__ == '__main__':
    main()
