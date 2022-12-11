/*
 *	CSafeQueue.h
 *
 *
 */

#pragma once

#include <queue>
#include <boost/thread.hpp>

template <typename T>
class CSafeQueue
{
public:
	CSafeQueue<T>::CSafeQueue(void) { }
	~CSafeQueue(void) {
		Flush();
	}

public:
	void Push(const T& rItem) {
		boost::mutex::scoped_lock	oLock(m_oMutex);
		m_oDataQueue.push(rItem);
		m_oDataCondition.notify_one();
	}

	int Front(T& rItem) {
		boost::mutex::scoped_lock	oLock(m_oMutex);
		if (m_oDataQueue.empty()) return -1;
		rItem = m_oDataQueue.front();
		return 0;
	}

	int TryPop(T& rItem) {
		boost::mutex::scoped_lock	oLock(m_oMutex);
		if (m_oDataQueue.empty()) return -1;
		rItem = m_oDataQueue.front();
		m_oDataQueue.pop();
		return 0;
	}

	void WaitAndPop(T& rItem) {
		boost::mutex::scoped_lock	oLock(m_oMutex);
		m_oDataCondition.wait(oLock, [this] { return !m_oDataQueue.empty(); });
		rItem = m_oDataQueue.front();
		m_oDataQueue.pop();
	}

	int IsEmpty(void) {
		boost::mutex::scoped_lock	oLock(m_oMutex);
		return m_oDataQueue.empty() ? 1 : 0;
	}

	int Size(void) {
		boost::mutex::scoped_lock	oLock(m_oMutex);
		return static_cast<int>(m_oDataQueue.size());
	}

	void Flush(void) {
		boost::mutex::scoped_lock	oLock(m_oMutex);
		while (!m_oDataQueue.empty())	m_oDataQueue.pop();
	}

private:
	mutable boost::mutex	m_oMutex;
	std::queue<T>			m_oDataQueue;
	boost::condition_variable	m_oDataCondition;

private:
	CSafeQueue(const CSafeQueue&) { }
	void operator = (const CSafeQueue&) { }
};

