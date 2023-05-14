import sqlite3 as sql
import sys


def main(argv):
    count = 0
    db = sql.connect('database.db')

    name = str(input("Full Name: "))
    name = name.split(" ")

    result = db.execute('SELECT * FROM Contacts WHERE FirstName LIKE ? OR MidleName LIKE ? OR LastName LIKE ?;', (name[0], name[1], name[2]))

    rows = result.fetchall()

    for row in rows:
        print(f"{row[0]} | {row[1]} | {row[2]} | {row[3]} | {row[4]} | {row[5]} | {row[6]}")

    db.close()


if __name__ == "__main__":
    main(sys.argv)
