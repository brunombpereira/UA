from Crypto.Hash import SHA256
import sys
import io

# Obtem os nomes dos ficheiros a partir dos argumentos da linha de comando
arquivos = sys.argv[1:]

# Itera sobre os ficheiros e calcula o hash SHA-1 de cada um
for arquivo in arquivos:
    try:
        f = open(arquivo, 'rb') # 'rb' é o modo de leitura binário, sendo que estamos a utilizar a função de síntese SHA-1, uma função de hash que opera em blocos de bytes, deve-se ler no modo 'rb' para nenhum caracter ser mal interpretado sha1 = hashlib.sha1()
        hash_sha256 = SHA256.new()

        while (True):
            data = f.read(io.DEFAULT_BUFFER_SIZE)
            
            if not data: # quando já não há mais nada no ficheiro para ler o ciclo acaba    
                break

            hash_sha256.update(data) # Adiciona os dados

        print(f"O hash SHA-1 do arquivo {arquivo} é: {hash_sha256.hexdigest()}")
    except IOError as e:
        print(f'Error: {arquivo} {e.strerror}')
