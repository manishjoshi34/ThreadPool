#include<iostream>
#include<thread>
using namespace std;

typedef void (*functionName)(int ,int*);

void threadFn(functionName f1,int count,int* array)
{	
	cout<<"In thread.."<<endl;
	cout<<this_thread::get_id()<<endl;
	f1(count,array);
}

void function1(int arg,int*argA){
	cout<<this_thread::get_id()<<endl;
	for(int i=0;i<arg;i++){
		cout<<argA[i]<<endl;
	}
}

int main(){
	int i=6;
	int array[]={1,2,3,4,5,6};
	thread t1(function1,i,array);
	thread t2([](){
		cout<<"In second thread.."<<endl;
		cout<<this_thread::get_id()<<endl;
		int i=1000;
		while(i>0){i--;}	
			});
	t1.join();
	t2.join();
	cout<<"Existing main thread.."<<endl;
	return 0;
}
