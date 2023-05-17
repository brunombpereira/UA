import sqlite3 as sql
import sys


def main(argv):
    db = sql.connect('database.db')

    result = db.execute('SELECT * FROM Companies')

    rows = result.fetchall()

    for row in rows:
        print(f"{row[0]} | {row[1]} | {row[2]} | {row[3]}")

    db.close()


if __name__ == "__main__":
    main(sys.argv)
