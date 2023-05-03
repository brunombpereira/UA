import sys
import requests

# Obter o endereço do argumento de linha de comando
address = sys.argv[1]

# Construir a URL da API do OpenStreetMaps
servurl = "https://nominatim.openstreetmap.org/search.php?format=json&q=%s" % address

# Fazer uma solicitação GET para a API do OpenStreetMaps
r = requests.get(servurl)

# Extrair as coordenadas e outras informações do resultado da solicitação
result = r.json()[0]
lat = result["lat"]
lon = result["lon"]
display_name = result["display_name"]

# Imprimir as coordenadas e outras informações
print(f"Latitude: {lat}")
print(f"Longitude: {lon}")
print(f"Localização: {display_name}")
