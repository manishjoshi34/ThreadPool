#include<iostream>
#include"mString.h"

using namespace std;

mString::mString(void){
	className = new char[100];
	className =const_cast<char*>( "stringClass");
	maxSize = 100;
}
int mString::getMaxSize(void){
	return maxSize;
}

int main(int argi,char** arg){
	if(*arg!=NULL){
		int i=0;
		cout<<*arg;
		cout<<endl;
	}
	mString myStr;
	cout<<myStr.getMaxSize()<<endl;
	return 0;
}
