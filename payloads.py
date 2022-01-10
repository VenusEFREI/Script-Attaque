import os
from db import Db
import requests
from bs4 import BeautifulSoup

class Payload():
    def __init__(self) -> None:
        self.db = Db()
        self.url = "https://www.exploit-db.com/exploits/"
        self.headers = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.45 Safari/537.36'}

    def recup_payload(self, path, file, id):
        if os.path.exists(path):
            pass
        else:
            os.makedirs(path)
        if os.path.exists(file):
            pass
        else:
            content = requests.get(url=self.url + str(id), headers=self.headers)
            soup = BeautifulSoup(content.text, 'html.parser')
            code = soup.find("pre").find('code').get_text()
            if code:
                with open (file, "w") as f:
                    f.write(code)
                    f.close()
            else:
                with open("errors.txt", "a") as f:
                    f.write("Pas de code pour l'exploit qui porte l'id: " + str(id) + "\n")

    def create_directory(self):
        datas = self.db.check_directories()
        for data in datas:
            if data[0] != 'id':
                new = data[1].split('/')
                del new[-1]
                path = new[0] + "/" + new[1] + "/" + new[2]
                self.recup_payload(path, data[1], int(data[0]))