import base64
import os
import random
import socket
import unittest

from Crypto.Cipher import AES

from client_server.common_comm import send_dict, recv_dict

users = {}


def find_client_id(client_sock):
    # Iterating over the clients
    for client_id in users:
        # Verifying if the socket is the same
        if users[client_id]["socket"] == client_sock:
            # Returning the client id
            return client_id
    return None


def encrypt_intvalue(client_id, data_arg):
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
        return "No data received"


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
        return "No data received"


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
    except ValueError:
        return None


def send_message(sock, response):
    send_dict(sock, response)


def read_message(sock):
    return recv_dict(sock)


def clean_client(client_sock):
    # Getting the client_id
    client_id = find_client_id(client_sock)

    # Verifying if the client_id is not None
    if client_id is not None:
        del users[client_id]
        print("Client %s removed\n" % client_id)


class TestesUnitarios(unittest.TestCase):
    def setUp(self) -> None:
        # Open a TCP connection to the server
        self.client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def test_find_client_id(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        users["client1"] = {"socket": self.client_sock, "cipher": cipherkey, "numbers": []}

        find_clientId = find_client_id(self.client_sock)

        self.assertEqual(find_clientId, "client1")

        self.client_sock.close()

    def test_find_client_id_with_rong_client_sock(self):
        # Open a TCP connection to the server
        client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        users["client2"] = {"socket": client_sock, "cipher": cipherkey, "numbers": []}

        find_clientId = find_client_id(self.client_sock)

        self.assertEqual(find_clientId, None)

        client_sock.close()

    def test_encrypt_decrypt_intvalue(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        users["client3"] = {"socket": self.client_sock, "cipher": cipherkey, "numbers": [5]}

        encrypted_value = encrypt_intvalue(find_client_id(self.client_sock), 5)

        self.assertEqual(decrypt_intvalue(cipherkey, encrypted_value), 5)

        self.client_sock.close()

    def test_encrypt_intvalue_with_no_data(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        users["client4"] = {"socket": self.client_sock, "cipher": cipherkey, "numbers": []}

        encrypted_value = encrypt_intvalue(find_client_id(self.client_sock), None)

        self.assertEqual(encrypted_value, "No data received")

        self.client_sock.close()

    def test_decrypt_intvalue_with_no_data(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        self.assertEqual(decrypt_intvalue(cipherkey, None), "No data received")

    def test_generate_result(self):
        value, response = generate_result([1])

        self.assertEqual(value, 1)
        self.assertIsNotNone(response)

    def test_generate_result_without_numList(self):
        with self.assertRaises(TypeError):
            value, response = generate_result([])

    def test_clean_client(self):
        users["client5"] = {"socket": self.client_sock, "numbers": []}

        clean_client(self.client_sock)

        self.assertEquals(find_client_id(self.client_sock), None)

    def test_clean_client_without_removing(self):
        users["client5"] = {"socket": self.client_sock, "numbers": []}

        self.assertEquals(find_client_id(self.client_sock), "client5")
