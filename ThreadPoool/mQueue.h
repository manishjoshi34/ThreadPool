#ifndef _safequeue_h
#define _safequeue_h

#include<queue>
#include<mutex>

template<typename T>
class mQueue{
	private:

	std::queue<T> Queue;
	std::mutex Mutex;

	public:

	mQueue();
	~mQueue();
	bool empty();
	int size();
	void push(T&);
	bool pull(T&);
};
template<typename T>
mQueue<T>::mQueue(){}

template<typename T>
mQueue<T>::~mQueue(){}

template<typename T>
bool mQueue<T>::empty(){
	std::lock_guard<std::mutex> lock(Mutex);
	return Queue.empty();
}

template<typename T>
int mQueue<T>::size(){
	std::lock_guard<std::mutex> lock(Mutex);
	return Queue.size();
}

template<typename T>
void mQueue<T>::push(T& obj){
	std::lock_guard<std::mutex> lock(Mutex);
	Queue.push(obj);
}

template<typename T>
bool mQueue<T>::pull(T& obj){
	std::lock_guard<std::mutex> lock(Mutex);
	if(Queue.empty())return false;
	obj = std::move(Queue.front());
	Queue.pop();
	return true;
}

#endif
