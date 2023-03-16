import socket


def main():
    tcp_s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Ligar ao servidor
    tcp_s.connect(("127.0.0.1", 1234))

    while 1:
        str_data = input("Mensagem: ")
        b_data = str_data.encode("utf-8")
        tcp_s.send(b_data)

        b_data = tcp_s.recv(4096)
        str_data = b_data.decode("utf-8")
        print(str_data)

    tcp_s.close()


if __name__ == '__main__':
    main()
