#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std;

void task1(int id){
    cout<<"Printing task "<<id<<"\n";
    for(int i=0;i<5;i++){
        cout<<i<<endl;
    }
}


void task2(int id){
    cout<<"Printing task "<<id<<"\n";
    for(int i=0;i<5;i++){
        cout<<i<<endl;
    }
}


int main(){
 
    thread t1(task1,1);
    thread t2(task2,2);

    t1.join();
    t2.join();

    cout<<"Both task completed\n";
}

