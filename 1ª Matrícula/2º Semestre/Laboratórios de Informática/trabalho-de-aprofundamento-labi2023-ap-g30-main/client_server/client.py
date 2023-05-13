import base64
import re
import socket
import sys
import os

from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from common_comm import send_dict, recv_dict

numbers = []


class Tcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def encrypt_intvalue(cipherkey, data_arg):
    if data_arg:
        # Creating the cipher
        cipher = AES.new(base64.b64decode(cipherkey), AES.MODE_ECB)

        # Encrypting the data
        data = cipher.encrypt(bytes("%16d" % data_arg, 'utf-8'))

        # Encoding the encrypted value
        encoded_encrypted_value = base64.b64encode(data)

        # Returning the encrypted value
        return str(encoded_encrypted_value, "utf-8")
    else:
        return f"{Tcolors.BOLD}{Tcolors.WARNING}No data received{Tcolors.ENDC}"


# Function to decrypt the value received from the server
def decrypt_intvalue(cipherkey, data_arg):
    # Verifying if the data_arg is not None
    if data_arg:
        # Creating the cipher
        cipher = AES.new(base64.b64decode(cipherkey), AES.MODE_ECB)

        # Decoding the data_arg
        data = base64.b64decode(data_arg)

        # Decrypting the data
        data = cipher.decrypt(data)

        # Returning the decrypted data
        return int(str(data, 'utf-8'))
    else:
        return f"{Tcolors.BOLD}{Tcolors.WARNING}No data received{Tcolors.ENDC}"


# Function to validate the response received from the server
def validate_response(client_sock, response):
    # Verifying if the response is valid
    if not response["status"]:
        print(response["error"])
        client_sock.close()
        sys.exit(3)


# Function to execute the QUIT action
def quit_action(client_sock):
    # Sending the QUIT message to the server
    message = {"op": "QUIT"}
    send_dict(client_sock, message)

    # Receiving the response from the server
    response = recv_dict(client_sock)

    # Validating the response
    validate_response(client_sock, response)

    print(f"{Tcolors.BOLD}{Tcolors.OKGREEN}Quit successfully{Tcolors.ENDC}")

    # Closing the socket
    client_sock.close()
    sys.exit(0)


# Function to run the client
def run_client(client_sock, clientId):
    # Variable to store the cipherkey
    cipherkey = None
    hasStarted = False
    hasStoped = False

    # Loop to run the client
    while True:
        try:
            # Printing the options
            print("\n===================================\nChoose an option:\n1 - START\n2 - QUIT\n3 - NUMBER\n4 - STOP\n5 - GUESS\n===================================")
            choice = int(input(f"\n{Tcolors.BOLD}Option: {Tcolors.ENDC}"))

            # Verifying the choice
            if choice == 1:
                if hasStarted:
                    print(f"\n{Tcolors.BOLD}{Tcolors.WARNING}You have already started the game{Tcolors.ENDC}")
                else:
                    while True:
                        # Asking the user if he wants to encrypt the communication
                        print(f"\n{Tcolors.UNDERLINE}Do you wish to encrypt your data (Yes/No): {Tcolors.ENDC}")
                        cifra = input(f"{Tcolors.BOLD}> {Tcolors.ENDC}")

                        try:
                            if cifra.upper() == "Y" or cifra.upper() == "YES":
                                # Generating the cipherkey
                                cipherkey = base64.b64encode(os.urandom(16)).decode()

                                # Sending the START message to the server
                                message = {"op": "START", "client_id": clientId, "cipher": cipherkey}
                                send_dict(client_sock, message)

                                # Receiving the response from the server
                                response = recv_dict(client_sock)

                                # Validating the response
                                validate_response(client_sock, response)

                                hasStarted = True

                                print(f"\n{Tcolors.BOLD}{Tcolors.OKGREEN}Client added successfully{Tcolors.ENDC}")
                                break
                            elif cifra.upper() == "N" or cifra.upper() == "NO":
                                # Sending the START message to the server
                                message = {"op": "START", "client_id": clientId}
                                send_dict(client_sock, message)

                                # Receiving the response from the server
                                response = recv_dict(client_sock)

                                # Validating the response
                                validate_response(client_sock, response)

                                hasStarted = True

                                print(f"\n{Tcolors.BOLD}{Tcolors.OKGREEN}Client added successfully{Tcolors.ENDC}")
                                break
                            else:
                                print(f"\n{Tcolors.BOLD}{Tcolors.WARNING}Invalid value{Tcolors.ENDC}")
                        except ValueError:
                            print(f"\n{Tcolors.BOLD}{Tcolors.WARNING}Invalid value{Tcolors.ENDC}")
            elif choice == 2:
                # Calling the quit_action function
                quit_action(client_sock)
                break
            elif choice == 3:
                try:
                    if cipherkey is not None:
                        # Sending the NUMBER message to the server
                        print(f"\n{Tcolors.UNDERLINE}Number:{Tcolors.ENDC}")
                        number = int(input(f"{Tcolors.BOLD}> {Tcolors.ENDC}"))
                        encrypted_number = encrypt_intvalue(cipherkey, number)
                        numbers.append(number)
                        message = {"op": "NUMBER", "number": encrypted_number}
                        send_dict(client_sock, message)

                        # Receiving the response from the server
                        response = recv_dict(client_sock)

                        # Validating the response
                        validate_response(client_sock, response)
                        print(f"{Tcolors.BOLD}{Tcolors.OKGREEN}Number added successfully{Tcolors.ENDC}")
                    else:
                        # Sending the NUMBER message to the server
                        print(f"\n{Tcolors.UNDERLINE}Number:{Tcolors.ENDC}")
                        number = int(input(f"{Tcolors.BOLD}> {Tcolors.ENDC}"))
                        numbers.append(number)
                        message = {"op": "NUMBER", "number": number}
                        send_dict(client_sock, message)

                        # Receiving the response from the server
                        response = recv_dict(client_sock)

                        # Validating the response
                        validate_response(client_sock, response)
                        print(f"{Tcolors.BOLD}{Tcolors.OKGREEN}Number added successfully{Tcolors.ENDC}")
                except ValueError:
                    print(f"{Tcolors.BOLD}{Tcolors.WARNING}\nInvalid value{Tcolors.ENDC}")
            elif choice == 4:
                if len(numbers) != 0:
                    hash_sha256 = SHA256.new()

                    for number in numbers:
                        hash_sha256.update(bytes(str(number), 'utf-8'))

                    # Sending the STOP message to the server
                    message = {"op": "STOP", "shasum": hash_sha256.hexdigest()}
                    send_dict(client_sock, message)

                    # Receiving the response from the server
                    response = recv_dict(client_sock)

                    # Validating the response
                    validate_response(client_sock, response)

                    if cipherkey is None:
                        print(f"\n{Tcolors.UNDERLINE}List: {numbers}\nResult: {response['result']}{Tcolors.ENDC}")
                        hasStoped = True
                    else:
                        # Decrypting the value received from the server
                        decrypted_value = decrypt_intvalue(cipherkey, response["result"])

                        print(f"\n{Tcolors.UNDERLINE}List: {numbers}\nResult: {str(decrypted_value)}{Tcolors.ENDC}")
                        hasStoped = True
                else:
                    print(f"\n{Tcolors.BOLD}{Tcolors.WARNING}No numbers added{Tcolors.ENDC}")
            elif choice == 5:
                if hasStoped:
                    # GUESS
                    guess = []
                    while True:
                        try:
                            # Printing the options
                            print("\n===================================\nChoose an option:\n1 - first\n2 - last\n3 - min\n4 - max\n5 - median\n6 - min, first\n7 - "
                                  "max, first\n8 - min, last\n9 - max, last\n10 - median, first\n11 - median, last\n12 - first, "
                                  "last, min, max, median\n===================================")
                            choice = int(input(f"{Tcolors.BOLD}Option: {Tcolors.ENDC}"))

                            # Verifying the choice
                            if choice == 1:
                                guess = ["first"]
                                break
                            elif choice == 2:
                                guess = ["last"]
                                break
                            elif choice == 3:
                                guess = ["min"]
                                break
                            elif choice == 4:
                                guess = ["max"]
                                break
                            elif choice == 5:
                                guess = ["median"]
                                break
                            elif choice == 6:
                                guess = ["min", "first"]
                                break
                            elif choice == 7:
                                guess = ["max", "first"]
                                break
                            elif choice == 8:
                                guess = ["min", "last"]
                                break
                            elif choice == 9:
                                guess = ["max", "last"]
                                break
                            elif choice == 10:
                                guess = ["median", "first"]
                                break
                            elif choice == 11:
                                guess = ["median", "last"]
                                break
                            elif choice == 12:
                                guess = ["first", "last", "min", "max", "median"]
                                break
                            else:
                                print(f"{Tcolors.BOLD}{Tcolors.WARNING}Invalid option{Tcolors.ENDC}")
                        except ValueError:
                            print(f"{Tcolors.BOLD}{Tcolors.FAIL}Invalid option{Tcolors.ENDC}")

                    # Sending the GUESS message to the server
                    message = {"op": "GUESS", "choice": guess}
                    send_dict(client_sock, message)

                    # Receiving the response from the server
                    response = recv_dict(client_sock)

                    # Validating the response
                    validate_response(client_sock, response)

                    # Verifying if the guess was correct
                    if response["result"]:
                        print(f"{Tcolors.BOLD}{Tcolors.OKGREEN}Got it right{Tcolors.ENDC}")
                        break
                    else:
                        print(f"{Tcolors.BOLD}{Tcolors.FAIL}Got it wrong{Tcolors.ENDC}")
                else:
                    print(f"{Tcolors.BOLD}{Tcolors.WARNING}You must stop the game first{Tcolors.ENDC}")
            else:
                print(f"{Tcolors.BOLD}{Tcolors.WARNING}Invalid option{Tcolors.ENDC}")
        except ValueError:
            print(f"{Tcolors.BOLD}{Tcolors.FAIL}Invalid option{Tcolors.ENDC}")


def main():
    # Variables to store the arguments
    server_address = None
    port = None
    client_id = None

    # Check if the number of arguments is valid
    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print(f"{Tcolors.BOLD}{Tcolors.FAIL}Error: You must provide 2 or 3 arguments.\nUsage: python3 client.py <client_id> <port> [<server_address>]{Tcolors.ENDC}")
        sys.exit(1)
    else:
        # Check if the port is valid
        try:
            if len(sys.argv) == 4:
                if re.match(r'^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$', sys.argv[3]):
                    if all(0 <= int(x) <= 255 for x in sys.argv[3].split('.')):
                        server_address = str(sys.argv[3])
                        port = int(sys.argv[2])
                        client_id = sys.argv[1]
                    else:
                        print(f"{Tcolors.BOLD}{Tcolors.FAIL}Error: The last argument must be in format X.X.X.X, where X epresents an integer value between 0 and 255{Tcolors.ENDC}")
                else:
                    print(f"{Tcolors.BOLD}{Tcolors.FAIL}Error: The last argument must be in format X.X.X.X, where X epresents an integer value between 0 and 255{Tcolors.ENDC}")
            elif len(sys.argv) == 3:
                server_address = socket.gethostbyname(socket.gethostname())
                port = int(sys.argv[2])
                client_id = sys.argv[1]
                print(f"{Tcolors.BOLD}{Tcolors.OKGREEN}Connecting to {server_address} in port {port}{Tcolors.ENDC}")
        except ValueError:
            print(f"{Tcolors.BOLD}{Tcolors.FAIL}-------------Error-------------\nUsage: python3 client.py <client_id> <port> [<server_address>]{Tcolors.ENDC}")
            sys.exit(1)

    # Create a TCP socket
    client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_sock.bind(("0.0.0.0", 0))

    try:
        # Connect the socket to the port where the server is listening
        client_sock.connect((server_address, port))
    except ConnectionRefusedError:
        print(f"{Tcolors.BOLD}{Tcolors.FAIL}Error: The server is not running in the specified port{Tcolors.ENDC}")
        sys.exit(1)

    # Run the client
    run_client(client_sock, client_id)

    # Close the socket
    client_sock.close()


if __name__ == "__main__":
    main()
