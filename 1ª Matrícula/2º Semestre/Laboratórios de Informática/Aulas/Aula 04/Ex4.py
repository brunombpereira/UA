import json


def main():
    data = [
        {"time": 1394984189, "name": "cpu", "value": 12},
        {"time": 1394984190, "name": "cpu", "value": 19}
    ]

    with open("data.json", "w") as f:
        json.dump(data, f, indent=4)


main()
