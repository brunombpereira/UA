import requests

url = "http://www.ua.pt"
response = requests.get(url)

print("Status Code:", response.status_code)

# Print all headers
print("Headers:")
for header, value in response.headers.items():
    print(f"{header}: {value}")

# Print content type
content_type = response.headers.get("Content-Type")
print("Content-Type:", content_type)

# Check if content type is HTML
if "text/html" in content_type and "charset=utf-8" in content_type:
    print("Content is HTML encoded in utf-8.")
else:
    print("Content is not HTML or not encoded in utf-8.")
