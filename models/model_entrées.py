import requests
from bs4 import BeautifulSoup

url = "https://www.exploit-db.com/exploits/5"
headers = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.45 Safari/537.36'}

content = requests.get(url=url, headers=headers)
soup = BeautifulSoup(content.text, 'html.parser')
code = soup.find("pre").find('code').get_text()
with open("test.c", "w") as f:
    f.write(code)
