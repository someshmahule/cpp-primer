#include<iostream>
#include<thread>

using namespace std;

void t_func(){
    for(int i=0;i<15;i++)
        cout<<"Hey"<<endl;
}

void a_func(){
    for(int i=0;i<15;i++)
        cout<<"Hi"<<endl;
}

int main(){
    std::thread t1(t_func);
    std::thread t2(a_func);
    t1.join();
    t2.join();
}