#include<iostream>
#include<thread>
#include<future>
using namespace std;

int myfunc(){
	int i=1000;
	while(i>0){i--;}
	return 10;

}
void ThreadFunc(promise<int> &prom){
	prom.set_value(100);
}
int main(){
	future<int> f1 = async(launch::async, myfunc);
	if(f1.valid())
	cout<<f1.get();
	promise<int> mypromise;
	future<int> myfuture  =mypromise.get_future();
	thread t1(ThreadFunc,ref(mypromise));
	cout<<myfuture.get()<<endl;
	t1.join();
	return 0;
}


