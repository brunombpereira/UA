import sqlite3 as sql
import sys


def main(argv):
    count = 0
    db = sql.connect('database.db')

    result = db.execute('SELECT Contacts.* FROM Contacts,Companies WHERE Contacts.CompanyID = Companies.ID')

    rows = result.fetchall()

    for row in rows:
        print(f"{row[0]} | {row[1]} | {row[2]} | {row[3]} | {row[4]} | {row[5]} | {row[6]}")

    db.close()


if __name__ == "__main__":
    main(sys.argv)
