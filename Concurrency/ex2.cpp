// passing a function object to run as a background thread

#include<iostream>
#include<thread>

using namespace std;

class background_task{
    public:
        void operator()() const{
            add();
            subtract();
        }
    private:
        void add() const {
            for(int i=0;i<5;i++){
                cout<<i<<endl;
            }
        }
        void subtract() const{
            for(int i=5;i>=0;i--){
            cout<<i<<endl;
        }
    }
};

int main (){
    background_task f;
    //thread t1(f);
    //thread t1((background_task())); // this works the same
    // or this 
    std::thread t1{background_task()};
    t1.join();
    std::cout << "Main thread continues executing..." << std::endl;
}

//output
/*0
1
2
3
4
5
4
3
2
1
0
Main thread continues executing...*/