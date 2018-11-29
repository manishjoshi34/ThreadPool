#ifndef _mQueue_h
#define _mQueue_h

#include<queue>
#include<iostream>
#include<mutex>

using namespace std;
template<typename T>
class mQueue{
	private:
	queue<T> _queue;
	mutex _mutex;
	public:
	mQueue(){}
	~mQueue(){}
	bool isEmpty(){
		lock_guard<std::mutex> lock(_mutex);
		return _queue.empty();
	}
	int size(){
		lock_guard<std::mutex> lock(_mutex);
		return _queue.size();
	}
	void push(T& obj){
		lock_guard<std::mutex> lock(_mutex);
		_queue.push(obj);
	}
	bool getTask(T& obj){
		lock_guard<std::mutex> lock(_mutex);
		if(_queue.empty()) return false;
		obj = _queue.front();
		_queue.pop();
		return false;
	}
};

#endif
