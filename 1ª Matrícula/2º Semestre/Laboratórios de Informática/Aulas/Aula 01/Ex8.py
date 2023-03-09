import os
import sys
import hashlib
from Crypto.Cipher import AES

BLOCK_SIZE = 16 # Definir a dimensão da chave

def generate_key(key):
    if len(key) < BLOCK_SIZE:
        # Gerar uma síntese de chave com SHA-256
        key = hashlib.sha256(key[:BLOCK_SIZE].encode('utf-8')).digest()
    else:
        # Usar apenas os primeiros 256 octetos
        key = key[:BLOCK_SIZE].encode('utf-8')

    return key


# Caso o ficheiro seja pequeno a função pad_data() adiciona o resto do tamanho necessário

def pad_data(data):
    pad_len = BLOCK_SIZE - (len(data) % BLOCK_SIZE)
    padding = bytes([pad_len] * pad_len)
    return data + padding


def encrypt_file(file_path, key, output_path):
    with open(file_path, 'rb') as file: # lê o ficheiro em modo de leitura binário
        data = file.read()

    # Adicionar padding
    data = pad_data(data)

    # Gerar excipiente (nonce)
    cipher = AES.new(generate_key(key), AES.MODE_EAX)
    nonce = cipher.nonce

    # Criptografar arquivo
    ciphertext = cipher.encrypt(data)

    # Escrever arquivo cifrado
    with open(output_path, 'wb') as output_file:
        output_file.write(nonce)
        output_file.write(ciphertext)

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print('Usage: python3 encrypt_file.py input_file key output_file', file=sys.stderr)
        sys.exit(1)

    file_path = sys.argv[1]
    key = sys.argv[2]
    output_path = sys.argv[3]

    encrypt_file(file_path, key, output_path)
