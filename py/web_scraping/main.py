from bs4 import BeautifulSoup

with open('web.html', 'r') as html_file:
    content = html_file.read()
    soup = BeautifulSoup(content,'lxml')
    tags = soup.find_all('h3')
    for course in tags:
        print(course)
    