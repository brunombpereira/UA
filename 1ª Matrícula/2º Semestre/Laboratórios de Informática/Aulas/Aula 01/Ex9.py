import os
import sys
import hashlib
from Crypto.Cipher import AES

BLOCK_SIZE = 16

def generate_key(key):
    if len(key) < BLOCK_SIZE:
        # Gerar uma síntese de chave com SHA-256
        key = hashlib.sha256(key[:BLOCK_SIZE].encode('utf-8')).digest()
    else:
        # Usar apenas os primeiros 256 octetos
        key = key[:BLOCK_SIZE].encode('utf-8')
    return key

def pad_data(data):
    pad_len = BLOCK_SIZE - (len(data) % BLOCK_SIZE)
    padding = bytes([pad_len] * pad_len)
    return data + padding

def unpad_data(data):
    pad_len = data[-1]
    return data[:-pad_len]

def decrypt_file(file_path, key, output_path):
    with open(file_path, 'rb') as file:
        data = file.read()

    # Remover excipiente (nonce)
    nonce = data[:16]
    ciphertext = data[16:]

    # Descriptografar arquivo
    cipher = AES.new(generate_key(key), AES.MODE_EAX, nonce=nonce)
    plaintext = cipher.decrypt(ciphertext)

    # Remover padding
    plaintext = unpad_data(plaintext)

    # Escrever arquivo decifrado
    with open(output_path, 'wb') as output_file:
        output_file.write(plaintext)

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print('Usage: python3 decrypt_file.py file key output_file', file=sys.stderr)
        sys.exit(1)

    file_path = sys.argv[1]
    key = sys.argv[2]
    output_path = sys.argv[3]

    # Verificar tamanho do arquivo
    file_size = os.path.getsize(file_path)
    if file_size % BLOCK_SIZE != 0:
        print('Error: File size is not aligned with the cipher block size')
        sys.exit(1)

    decrypt_file(file_path, key, output_path)
