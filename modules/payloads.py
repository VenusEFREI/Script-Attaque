import os
from db import Db
import requests
from bs4 import BeautifulSoup
# from selenium import webdriver
# from selenium.webdriver.common.keys import Keys

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
            # options = webdriver.ChromeOptions()
            # options.add_argument("headless")
            # driver = webdriver.Chrome(executable_path=r'/home/barry/Téléchargements/chromedriver_linux64/chromedriver', chrome_options=options)
            self.url = self.url + str(id)
            content = requests.get(url=self.url, headers=self.headers)
            soup = BeautifulSoup(content.text, 'html.parser')
            code = soup.find("pre").find('code').get_text()
            # driver.get(self.url + str(id))
            # html = driver.page_source
            # if "code" in html:
            if code:
                # element = driver.find_element_by_tag_name("code")
                with open (file, "w") as f:
                    f.write(code)
                    f.close()
            # driver.quit()

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