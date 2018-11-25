#include<iostream>
#include"/home/manish/gitDataServer/localRepo/util/StringClass/mString.h"
#define MSTRINGH

int main(int argc,char** arg){
	for(int i=0;i<argc;i++){
		cout<<arg[i]<<endl;
	}
	mString* str= new mString();
	cout<<"Class Name: "<<str->getClassName()<<endl;
	cout<<"MAx Size: "<<str->getMaxSize()<<endl;
	return 0;
}
