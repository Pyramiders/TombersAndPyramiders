#pragma once
#include <queue>
#include <mutex>
#include <iostream>

template <typename T>
class ThreadQueue
{
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
public:

	void push(T const &data)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(data);
		lock.unlock();
	}

	bool isEmpty()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.empty();
	}

	bool pop(T &popped_value)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_queue.empty())
		{
			return false;
		}
		else
		{
			popped_value = m_queue.front();
			m_queue.pop();
			return true;
		}
	}
};