#!/usr/bin/python3

import base64
import csv
import glob
import os
import random
import select
import socket
import sys

from Crypto.Cipher import AES
from Crypto.Hash import SHA256

from common_comm import send_dict, recv_dict


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


# Dicionário com a informação relativa aos clientes
users = {}


# Function to find the client id
def find_client_id(client_sock):
    # Iterating over the clients
    for client_id in users:
        # Verifying if the socket is the same
        if users[client_id]["socket"] == client_sock:
            # Returning the client id
            return client_id
    return None


# Function to encrypt the value to send to the client
def encrypt_intvalue(client_id, data_arg):
    try:
        if data_arg:
            # Getting the cipherkey
            cipherkey = users[client_id]["cipher"]

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
    except TypeError:
        return f"{Tcolors.BOLD}{Tcolors.WARNING}The value must be an integer{Tcolors.ENDC}"


def decrypt_intvalue(client_id, data_arg):
    try:
        # Verifying if the data_arg is not None
        if data_arg:
            # Getting the cipherkey
            cipherkey = users[client_id]["cipher"]

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
    except TypeError as e:
        return f"{Tcolors.BOLD}{Tcolors.WARNING}{e}{Tcolors.ENDC}"


# Function to generate the result
def generate_result(list_values):
    # Verifying if the list_values is odd or even
    if len(list_values) % 2 == 1:
        test = 4
    else:
        test = 3

    try:
        # Getting the minimal and maximal values
        minimal = min(list_values)
        maximal = max(list_values)
        first = list_values[0]
        last = list_values[-1]

        # Generating the number
        choice = random.randint(0, test)

        # Verifying the choice
        if choice == 0:
            if minimal == first:
                return first, ["min", "first"]
            elif maximal == first:
                return first, ["max", "first"]
            else:
                return first, ["first"]
        elif choice == 1:
            if minimal == last:
                return last, ["min", "last"]
            elif maximal == last:
                return last, ["max", "last"]
            else:
                return last, ["last"]
        elif choice == 2:
            if minimal == first:
                return first, ["min", "first"]
            elif minimal == last:
                return last, ["min", "last"]
            else:
                return minimal, ["min"]
        elif choice == 3:
            if maximal == first:
                return first, ["max", "first"]
            elif maximal == last:
                return last, ["max", "last"]
            else:
                return maximal, ["max"]
        elif choice == 4:
            list_values.sort()
            median = list_values[len(list_values) // 2]
            if median == first:
                return first, ["median", "first"]
            elif median == last:
                return last, ["median", "last"]
            else:
                return median, ["median"]
        else:
            return None
    except TypeError:
        return None, None


# Function to register the new client
def new_client(client_sock, request):
    # Verifying if the client_id is in the request
    if "client_id" not in request:
        # Returning the error
        return {"op": "START", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.FAIL}Missing client_id{Tcolors.ENDC}"}
    else:
        # Getting the client_id
        client_id = request["client_id"]

        # Verifying if the client_id is in the users
        if client_id in users:
            # Returning the error
            return {"op": "START", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.WARNING}Client already exists{Tcolors.ENDC}"}
        else:
            # Verifying if the cipher is in the request
            if "cipher" not in request:
                # Adding the client to the users
                users[client_id] = {"socket": client_sock, "numbers": []}

                # Returning the response
                print(f"\n{Tcolors.BOLD}{Tcolors.UNDERLINE}Client %s added{Tcolors.ENDC}" % client_id)
                return {"op": "START", "status": True}
            else:
                # Getting the cipher
                cipher = request["cipher"]

                # Adding the client to the users
                users[client_id] = {"socket": client_sock, "cipher": cipher, "numbers": []}

                # Returning the response
                print(f"\n{Tcolors.BOLD}{Tcolors.UNDERLINE}Client %s added{Tcolors.ENDC}" % client_id)
                return {"op": "START", "status": True}


# Function to remove the client
def quit_client(client_sock):
    # Getting the client_id
    client_id = find_client_id(client_sock)

    # Verifying if the client_id is None
    if client_id is None:
        # Returning the error
        return {"op": "QUIT", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.FAIL}Unknown client{Tcolors.ENDC}"}
    else:
        # Updating the file with the client information
        update_file(client_id, users[client_id]["numbers"], "QUIT")

        # Removing the client from the users
        clean_client(client_sock)

        return {"op": "QUIT", "status": True}


# Function to add new numbers to the client
def number_client(client_sock, request):
    # Getting the client_id
    client_id = find_client_id(client_sock)

    # Verifying if the client_id is None
    if client_id is None:
        # Returning the error
        return {"op": "NUMBER", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.FAIL}Client does not exist{Tcolors.ENDC}"}
    else:
        # Verifying if the client_id is in the users
        if "number" not in request:
            # Returning the error
            return {"op": "NUMBER", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.WARNING}Missing number{Tcolors.ENDC}"}
        else:
            if "cipher" in users[client_id]:
                # Getting the number
                number = request["number"]

                # Adding the number to the client
                users[client_id]["numbers"].append(decrypt_intvalue(client_id, number))

                # Returning the response
                return {"op": "NUMBER", "status": True}
            else:
                # Getting the number
                number = request["number"]

                # Adding the number to the client
                users[client_id]["numbers"].append(number)

                # Returning the response
                return {"op": "NUMBER", "status": True}

# Function to stop the client
def stop_client(client_sock, request):
    # Getting the client_id
    client_id = find_client_id(client_sock)

    # Verifying if the client_id is None
    if client_id is None:
        # Returning the error
        return {"op": "STOP", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.FAIL}Client does not exist{Tcolors.ENDC}"}
    else:
        # Verifying if the request has the shasum
        if "shasum" not in request:
            # Returning the error
            return {"op": "STOP", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.WARNING}Missing shasum{Tcolors.ENDC}"}
        else:
            if len(users[client_id]["numbers"]) < 1:
                # Returning the error
                return {"op": "STOP", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.WARNING}Client has no numbers{Tcolors.ENDC}"}
            else:
                hash_sha256 = SHA256.new()

                for number in users[client_id]["numbers"]:
                    hash_sha256.update(bytes(str(number), 'utf-8'))

                if request["shasum"] == hash_sha256.hexdigest():
                    if "cipher" in users[client_id]:
                        value, result = generate_result(users[client_id]["numbers"])

                        # Updating the client information in the users
                        users[client_id]["result"] = result

                        # Updating the file with the client information
                        update_file(client_id, len(users[client_id]["numbers"]), [value, result])

                        # Returning the response
                        return {"op": "STOP", "status": True, "result": encrypt_intvalue(client_id, value)}
                    else:
                        # Getting the result
                        value, result = generate_result(users[client_id]["numbers"])

                        # Updating the client information in the users
                        users[client_id]["result"] = result

                        # Updating the file with the client information
                        update_file(client_id, len(users[client_id]["numbers"]), [value, result])

                        # Returning the response
                        return {"op": "STOP", "status": True, "result": value}
                else:
                    return {"op": "STOP", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.FAIL}Inconsistent shasum{Tcolors.ENDC}"}


# Function to guess the result
def guess_client(client_sock, request):
    # Getting the client_id
    client_id = find_client_id(client_sock)

    if client_id is None:
        # Returning the error
        return {"op": "GUESS", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.FAIL}Client does not exist{Tcolors.ENDC}"}
    else:
        # Verifying if the request has the choice
        if "choice" not in request:
            # Returning the error
            return {"op": "GUESS", "status": False, "error": f"{Tcolors.BOLD}{Tcolors.WARNING}Missing choice{Tcolors.ENDC}"}
        else:
            # Getting the choice
            choice = request["choice"]

            # Verifying if the choice is equal to the result
            if choice == users[client_id]["result"]:
                # Removing the client from the users
                quit_client(client_sock)

                # Returning the response
                return {"op": "GUESS", "status": True, "result": True}
            else:
                # Returning the response
                return {"op": "GUESS", "status": True, "result": False}


# Function to process the request
def new_msg(client_sock, request):
    # Verifying if the request has the operation
    if "op" not in request:
        # Returning the error
        return {"status": False, "error": f"{Tcolors.BOLD}{Tcolors.WARNING}Missing operation{Tcolors.ENDC}"}
    else:
        # Getting the operation
        operation = request["op"]

        # Verifying the operation
        if operation == "START":
            return new_client(client_sock, request)
        elif operation == "QUIT":
            return quit_client(client_sock)
        elif operation == "NUMBER":
            return number_client(client_sock, request)
        elif operation == "STOP":
            return stop_client(client_sock, request)
        elif operation == "GUESS":
            return guess_client(client_sock, request)
        else:
            return {"status": False, "error": f"{Tcolors.BOLD}{Tcolors.FAIL}Operation not recognized{Tcolors.ENDC}"}




# Function to send the response
def send_message(sock, response):
    send_dict(sock, response)


# Function to read the request
def read_message(sock):
    return recv_dict(sock)


# Function to remove the client from the users
def clean_client(client_sock):
    # Getting the client_id
    client_id = find_client_id(client_sock)

    # Verifying if the client_id is not None
    if client_id is not None:
        del users[client_id]
        print(f"{Tcolors.BOLD}Client %s removed\n{Tcolors.ENDC}" % client_id)


# Function to create a new file
def create_file():
    # Creating the file
    with open("result.csv", "w", newline="") as csvfile:
        # Creating the columns
        columns = ["client_id", "number_of_numbers", "guess"]

        # Writing the columns
        fw = csv.DictWriter(csvfile, delimiter=",", fieldnames=columns)
        fw.writeheader()


# Function to update the file
def update_file(client_id, size, guess):
    # Opening the file
    with open("result.csv", "a", newline="") as csvfile:
        # Creating the columns
        columns = ["client_id", "number_of_numbers", "guess"]

        # Writing the columns
        fw = csv.DictWriter(csvfile, delimiter=",", fieldnames=columns)
        fw.writerow({"client_id": client_id, "number_of_numbers": size, "guess": guess})


def main():
    # Verifying the number of arguments
    if len(sys.argv) != 2:
        print(f"{Tcolors.BOLD}{Tcolors.FAIL}Error: You must provide 2 arguments.\nUsage: python3 server.py <port>{Tcolors.ENDC}")
        sys.exit(1)
    else:
        try:
            port = int(sys.argv[1])
        except ValueError:
            print(f"{Tcolors.BOLD}{Tcolors.FAIL}Error:\nUsage: python3 server.py <port>{Tcolors.ENDC}")
            sys.exit(1)

    try:
        # Creating the server socket
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.bind((socket.gethostbyname(socket.gethostname()), port))
        server_socket.listen()
    except OSError as e:
        print(f"{Tcolors.BOLD}{Tcolors.FAIL}Error: {e}{Tcolors.ENDC}")
        sys.exit(1)

    # Initializing the clients list
    clients = []
    create_file()

    # Main loop
    while True:
        # Select sockets with data to read
        try:
            # Select sockets with data to read
            try:
                available, _, _ = select.select(clients + [server_socket], [], [])
            except KeyboardInterrupt:
                print(f"{Tcolors.BOLD}{Tcolors.FAIL}Quitting server{Tcolors.ENDC}")
                sys.exit(1)
        except Exception as e:
            print(f"{Tcolors.BOLD}{Tcolors.FAIL}Error: {e}{Tcolors.ENDC}")
            sys.exit(1)

        # Iterate over sockets with data
        for sock in available:
            # Accept new connections
            if sock == server_socket:
                # Accept new connection
                client_sock, _ = server_socket.accept()

                # Add new client to list
                clients.append(client_sock)
            # Process requests from existing clients
            else:
                # Read request
                request = read_message(sock)

                # Process request
                if request:
                    response = new_msg(sock, request)
                    send_message(sock, response)
                else:
                    sock.close()
                    clients.remove(sock)

    # Close all sockets
    for sock in clients:
        sock.close()
    server_socket.close()

    # Remove report files
    for filename in glob.glob("result.csv"):
        os.remove(filename)

    # Exit
    sys.exit(0)


if __name__ == "__main__":
    main()
