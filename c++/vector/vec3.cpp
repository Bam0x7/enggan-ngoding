#include<iostream>
#include<vector>

int main()
{
    std::vector<int> arr = {10,20,30};
    arr.insert(arr.begin()+3,40);
    arr.pop_back();

    for(int i : arr){
        std::cout<<i <<'\n';
    }
    std::cout<<'\n';
    arr.insert(arr.begin()+3,40);
    for(int i : arr){
        std::cout<<i <<'\n';
    }

    return 0;
}