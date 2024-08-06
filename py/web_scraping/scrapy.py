from bs4 import BeautifulSoup

with open('web.html', 'r') as html_file:
    content = html_file.read()
    soup = BeautifulSoup(content,'lxml')
    course_tag = soup.find_all('div',class_='article')
        
    for course in course_tag:
        course_name = course.h3.text
        course_price = course.a.text.split()[-1]  
        print(f"course: {course_name}, costs {course_price}")