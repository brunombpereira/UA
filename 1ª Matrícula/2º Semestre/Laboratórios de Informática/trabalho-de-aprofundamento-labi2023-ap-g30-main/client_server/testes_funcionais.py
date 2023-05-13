import base64
import os
import unittest
import socket

from Crypto.Hash import SHA256

from client_server.client import decrypt_intvalue, encrypt_intvalue
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


class TestesFuncionais(unittest.TestCase):
    def setUp(self) -> None:
        # Open a TCP connection to the server
        self.client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_address = (socket.gethostbyname(socket.gethostname()), 2134)
        self.client_sock.connect(server_address)

    def test_start_operation_with_cipher(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        # Send a message to the server
        message = {"op": "START", "client_id": "client1", "cipher": cipherkey}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "START")
        self.assertEqual(response["status"], True)

        # Close the TCP connection
        self.client_sock.close()

    def test_start_operation_without_cipher(self):
        # Send a message to the server
        message = {"op": "START", "client_id": "client2"}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "START")
        self.assertEqual(response["status"], True)

        # Close the TCP connection
        self.client_sock.close()

    def test_start_operation_with_invalid_client_id(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        # Send a message to the server
        message = {"op": "START", "cipher": cipherkey}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "START")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.FAIL}Missing client_id{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_start_operation_with_invalid_client_id2(self):
        # Send a message to the server
        message = {"op": "START"}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "START")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.FAIL}Missing client_id{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_start_operation_with_existing_client_id(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        # Send a message to the server
        message = {"op": "START", "client_id": "client1", "cipher": cipherkey}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "START")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.WARNING}Client already exists{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_quit_operation(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        # Send a message to the server
        msg = {"op": "START", "client_id": "client3", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        # Send a message to the server
        message = {"op": "QUIT"}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "QUIT")
        self.assertEqual(response["status"], True)

        # Close the TCP connection
        self.client_sock.close()

    def test_quit_operation_with_invalid_client_id(self):
        # Send a message to the server
        message = {"op": "QUIT"}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "QUIT")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.FAIL}Unknown client{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_number_operation(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        msg = {"op": "START", "client_id": "client4", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        # Send a message to the server
        message = {"op": "NUMBER", "number": encrypt_intvalue(cipherkey, 10)}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "NUMBER")
        self.assertEqual(response["status"], True)

        # Close the TCP connection
        self.client_sock.close()

    def test_number_operation_with_invalid_number(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        msg = {"op": "START", "client_id": "client5", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        # Send a message to the server
        message = {"op": "NUMBER"}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "NUMBER")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.WARNING}Missing number{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_number_operation_with_invalid_client_id(self):
        # Send a message to the server
        message = {"op": "NUMBER", "number": 10}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "NUMBER")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.FAIL}Client does not exist{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_stop_operation(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        msg = {"op": "START", "client_id": "client6", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        msgs = {"op": "NUMBER", "number": encrypt_intvalue(cipherkey, 10)}
        send_dict(self.client_sock, msgs)
        recv_dict(self.client_sock)

        hash_sha256 = SHA256.new()
        hash_sha256.update(bytes(str(10), "utf-8"))

        # Send a message to the server
        message = {"op": "STOP", "shasum": hash_sha256.hexdigest()}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "STOP")
        self.assertEqual(response["status"], True)
        self.assertEqual(decrypt_intvalue(cipherkey, response["result"]), 10)

        # Close the TCP connection
        self.client_sock.close()

    def test_stopt_operation_with_invalid_client_id(self):
        hash_sha256 = SHA256.new()
        hash_sha256.update(bytes(str(10), "utf-8"))

        # Send a message to the server
        message = {"op": "STOP", "shasum": hash_sha256.hexdigest()}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "STOP")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.FAIL}Client does not exist{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_stopt_operation_with_invalid_shasum(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        msg = {"op": "START", "client_id": "client7", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        # Send a message to the server
        message = {"op": "STOP"}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "STOP")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.WARNING}Missing shasum{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_stop_operation_without_number_operation(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        msg = {"op": "START", "client_id": "client8", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        hash_sha256 = SHA256.new()
        hash_sha256.update(bytes(str(10), "utf-8"))

        # Send a message to the server
        message = {"op": "STOP", "shasum": hash_sha256.hexdigest()}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "STOP")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.WARNING}Client has no numbers{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_stop_operation_without_correct_shasum(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        msg = {"op": "START", "client_id": "client9", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        msgs = {"op": "NUMBER", "number": encrypt_intvalue(cipherkey, 10)}
        send_dict(self.client_sock, msgs)
        recv_dict(self.client_sock)

        hash_sha256 = SHA256.new()
        hash_sha256.update(bytes(str(9), "utf-8"))

        # Send a message to the server
        message = {"op": "STOP", "shasum": hash_sha256.hexdigest()}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "STOP")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.FAIL}Inconsistent shasum{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_guess_operation(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        msg = {"op": "START", "client_id": "client10", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        msgs = {"op": "NUMBER", "number": encrypt_intvalue(cipherkey, 10)}
        send_dict(self.client_sock, msgs)
        recv_dict(self.client_sock)

        hash_sha256 = SHA256.new()
        hash_sha256.update(bytes(str(10), "utf-8"))

        messages = {"op": "STOP", "shasum": hash_sha256.hexdigest()}
        send_dict(self.client_sock, messages)
        recv_dict(self.client_sock)

        # Send a message to the server
        message = {"op": "GUESS", "choice": ["first"]}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "GUESS")
        self.assertEqual(response["status"], True)
        self.assertIsNotNone(response["result"])

        # Close the TCP connection
        self.client_sock.close()

    def test_guess_operation_with_invalid_choice(self):
        # Generate a random cipher key
        cipherkey = base64.b64encode(os.urandom(16)).decode()

        msg = {"op": "START", "client_id": "client11", "cipher": cipherkey}
        send_dict(self.client_sock, msg)
        recv_dict(self.client_sock)

        msgs = {"op": "NUMBER", "number": encrypt_intvalue(cipherkey, 10)}
        send_dict(self.client_sock, msgs)
        recv_dict(self.client_sock)

        hash_sha256 = SHA256.new()
        hash_sha256.update(bytes(str(10), 'utf-8'))

        messa = {"op": "STOP", "shasum": hash_sha256.hexdigest()}
        send_dict(self.client_sock, messa)
        recv_dict(self.client_sock)

        # Send a message to the server
        message = {"op": "GUESS"}
        send_dict(self.client_sock, message)
        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "GUESS")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.WARNING}Missing choice{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()

    def test_guess_operation_with_invalid_client_id(self):
        # Send a message to the server
        message = {"op": "GUESS", "choice": "first"}
        send_dict(self.client_sock, message)

        response = recv_dict(self.client_sock)

        self.assertEqual(response["op"], "GUESS")
        self.assertEqual(response["status"], False)
        self.assertEqual(response["error"], f"{Tcolors.BOLD}{Tcolors.FAIL}Client does not exist{Tcolors.ENDC}")

        # Close the TCP connection
        self.client_sock.close()


if __name__ == '__main__':
    unittest.main()