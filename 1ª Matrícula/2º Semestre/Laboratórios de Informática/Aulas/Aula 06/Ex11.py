import sqlite3 as sql
import sys


def main(argv):
    count = 0
    db = sql.connect('database.db')

    result = db.execute('SELECT FirstName FROM Contacts')

    rows = result.fetchall()

    for row in rows:
        count += 1
        print(row[0])

    print("Number of contacts: " + str(count))

    db.close()


if __name__ == "__main__":
    main(sys.argv)
