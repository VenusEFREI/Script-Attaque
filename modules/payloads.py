import os
from db import Db
import requests
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

class Payload():
    def __init__(self) -> None:
        self.db = Db()
        self.url = "https://www.exploit-db.com/exploits/"

    def recup_payload(self, path, file, id):
        options = webdriver.ChromeOptions()
        options.add_argument("headless")
        driver = webdriver.Chrome(executable_path=r'/home/barry/Téléchargements/chromedriver_linux64/chromedriver', chrome_options=options)
        driver.get(self.url + str(id))
        html = driver.page_source
        if "code" in html:
            element = driver.find_element_by_tag_name("code")
            if os.path.exists(path):
                pass
            else:
                os.makedirs(path)
            if os.path.exists(file):
                pass
            else:
                with open (file, "w") as f:
                    f.write(element.text)
                    f.close()
        driver.quit()

    def create_directory(self):
        datas = self.db.check_directories()
        for data in datas:
            if data[0] != 'id':
                new = data[1].split('/')
                del new[-1]
                path = new[0] + "/" + new[1] + "/" + new[2]
                self.recup_payload(path, data[1], int(data[0]))


payload = Payload()
payload.create_directory() 