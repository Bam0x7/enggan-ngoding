from bs4 import BeautifulSoup
import requests as req

html_text = req.get('https://www.timesjobs.com/candidate/job-search.html?searchType=personalizedSearch&from=submit&searchTextSrc=ft&searchTextText=&txtKeywords=python&txtLocation=')
soup = BeautifulSoup(html_text.text,'lxml')
jobs = soup.find_all('li', class_='clearfix job-bx wht-shd-bx')

for job in jobs:
    published = job.find('span',class_='sim-posted').span.text
    if "few" in published:
        company_name = job.find('h3',class_='joblist-comp-name').text.replace(' ','')
        skills = job.find('span',class_='srp-skills').text.replace(' ','')
        more_info = job.header.h2.a["href"]
        print(f"company: {company_name.strip()}")
        print(f"skill: {skills.strip()}")
        print(f"published date: {published}")
        print(f"more info: {more_info}")
        print('')
