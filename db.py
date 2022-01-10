from bs4 import BeautifulSoup
import sqlite3
import requests

class Db():
    def __init__(self):
        self.con = sqlite3.connect('databases/exploitsdb.db')
        self.url = "https://raw.githubusercontent.com/offensive-security/exploitdb/master/files_exploits.csv"
        self.res = requests.get(self.url)
        self.cur = self.con.cursor()
        self.req_create_entries = '''CREATE TABLE IF NOT EXISTS entries (
            id real,
            file text,
            description text,
            date text,
            author text,
            type text ,
            platform text,
            port text
        )
        '''
        self.req_create_nb_lines = '''CREATE TABLE IF NOT EXISTS row_count(
            last_count integer
        )'''
        self.cur.execute(self.req_create_entries)
        self.cur.execute(self.req_create_nb_lines)
        if self.res.ok :
            soup = BeautifulSoup(self.res.text, 'html.parser')
            with open ("lines.txt", "w+") as f:
                if len(f.readlines()) == 0 :
                    f.write(self.res.text)
    
    def count_entrie_row(self):
        req = "SELECT COUNT(*) FROM entries"
        self.cur.execute(req)
        ligne_db = self.cur.fetchone()[0]
        return ligne_db
    
    def insert_entries(self, iterable):
        req = "INSERT INTO entries VALUES (?,?,?,?,?,?,?,?)"
        self.cur.execute(req, (iterable))
        self.con.commit()

    def update_row_count(self, count):
        req = "UPDATE row_count SET last_count = ? WHERE id = ?"
        self.cur.execute(req, (count, 0))
        self.con.commit()

    def check_directories(self):
        req = "SELECT id, file FROM entries"
        self.cur.execute(req)
        return self.cur.fetchall()