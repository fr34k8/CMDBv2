#pragma once
#include <pthread.h>

typedef void* (*ThreadFunc)(void *);
class CThread
{
public:
	CThread(ThreadFunc pFun, void* pData);
	~CThread(void);

	int Wait();
protected:
	pthread_t m_hThread;
	bool m_bIsCreated;
};
