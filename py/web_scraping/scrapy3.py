from bs4 import BeautifulSoup
import requests

url = "https://www.tokopedia.com/search?q=laptop+gaming&source=universe&st=product&navsource=home&srp_component_id=02.02.02.01"
html_get = requests.get(url)
soup = BeautifulSoup(html_get.text,'lxml')
produk_list = soup.find_all('div',class_='css-jzalfo')

for produk in produk_list:
    print(produk)