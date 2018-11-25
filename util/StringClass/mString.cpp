#include<iostream>

using namespace std;

#ifndef MSTRINGH
#include"mString.h"
#define MSTRINGH
#endif

mString::mString(void){
	className = new char[100];
	className =const_cast<char*>( "stringClass");
	maxSize = 100;
}
int mString::getMaxSize(void){
	return maxSize;
}
char* mString::getClassName(void){
	return className;
}

