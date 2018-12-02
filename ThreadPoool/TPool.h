#ifndef _threadpool_h_
#define _threadpool_h_

#include<functional>
#include<future>
#include<mutex>
#include<queue>
#include<vector>
#include<thread>
#include "mQueue.h"

#define MAXTHREAD 10

typedef std::function<void()> TaskFunc;
class ThreadPool{
	private://variables
		bool mShutDown;
		int numThreads;
		mQueue<TaskFunc> mTaskQueue;
		std::vector<std::thread> mWorkers;
		std::mutex mQueueMutex;
		std::condition_variable mLock;
		//functions
		ThreadPool();
		ThreadPool(const int);
		void init();
		ThreadPool(const ThreadPool&) = delete;
		ThreadPool(ThreadPool&&)=delete;
		ThreadPool& operator=(const ThreadPool&) = delete;
		ThreadPool& operator=(ThreadPool&&) = delete;
		
	public:
		static ThreadPool* getInstance();
		~ThreadPool();
		void shutDown();

		template<typename F, typename...Args>
		auto submit(F&& f, Args&&...args)->std::future<decltype(f(args...))> ;
};
ThreadPool::ThreadPool():numThreads(std::thread::hardware_concurrency()),mWorkers(std::vector<std::thread>(numThreads)),mShutDown(false){
	//numThreads =  std::thread::hardware_concurrency();
	init();
}
ThreadPool::ThreadPool(const int n):numThreads(n),mWorkers(std::vector<std::thread>(n)),mShutDown(false){
}
template<typename F,typename... Args>
auto ThreadPool::submit(F&& f,Args&& ...args)-> std::future<decltype(f(args...))>{
	std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f),std::forward<Args>(args)...);
	auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
	TaskFunc wrapper_func = [task_ptr](){
		(*task_ptr)();
	};
	mTaskQueue.push(wrapper_func);
	mLock.notify_one();
	return task_ptr->get_future();
}
void ThreadPool::init(){
        for(int i=0;i<numThreads;i++){
                mWorkers[i] = std::thread([this](){
                TaskFunc mTask;
                bool TaskAssign;
                  while(this->mShutDown==false){
		  {
		  std::unique_lock<std::mutex> lock(this->mQueueMutex);
                        if(this->mTaskQueue.empty()){
                                mLock.wait(lock);
                        }
                        TaskAssign =this-> mTaskQueue.pull(mTask);
		  } 
		  if(TaskAssign){
			  mTask();
		 }
		 }
                });
        }
}
ThreadPool* ThreadPool::getInstance(){
        static ThreadPool mPool;
        return &mPool;
}
ThreadPool::~ThreadPool(){
        if(mShutDown==false){
                shutDown();
        }
}
void ThreadPool::shutDown(){
        mShutDown = true;
        mLock.notify_all();
        for(int i=0;i<numThreads;i++){
                if(mWorkers[i].joinable()){
                        mWorkers[i].join();
                }
        }
}



#endif
