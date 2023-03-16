import socket


def main():
    udp_s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_s.bind(("127.0.0.1", 1234))

    while True:
        b_data, addr = udp_s.recvfrom(4096)
        print(f"Received from {addr}: {b_data.decode('utf-8')}")

        if b_data.decode("utf-8") == "stop":
            break

        print(f"Sending to {addr}: {b_data.upper()}")
        udp_s.sendto(b_data.upper(), addr)

    udp_s.close()


if __name__ == "__main__":
    main()
