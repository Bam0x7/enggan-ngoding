#include<iostream>
#include<cmath>

using namespace std;

constexpr float PI = 3.14159;

class Circle{
    public:
        float radius;
        float area;
};

class Rectangle{
    public:
    float length;
    float width;
    float area;
};

void display(Circle);
void display(Rectangle);

int main()
{
    Circle myCircle;
    Rectangle myRect;
    Rectangle Mysquare;

    myCircle.radius = 5.0;
    myCircle.area = PI * pow(myCircle.radius,2.0);

    myRect.width = 2.0;
    myRect.length = 4.0;
    myRect.area = myRect.width * myRect.length;

    display(myCircle);
    display(myRect);

    return 0;
}

void display(Circle c)
{
    cout<<"Circle with radius: " <<c.radius <<" has an area of ";
    cout<<c.area <<endl;
}

void display(Rectangle r)
{
   cout << "Rectangle with length " << r.length << " and width "; 
   cout << r.width << " has an area of " << r.area << endl; 
}