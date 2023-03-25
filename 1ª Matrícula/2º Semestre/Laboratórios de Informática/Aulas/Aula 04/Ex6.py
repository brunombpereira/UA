import json


def main():
    with open("data.json", "r") as f:
        data = json.load(f)
        for item in data:
            print("time:", item["time"])
            print("name:", item["name"])
            print("value:", item["value"])
            print()


main()
