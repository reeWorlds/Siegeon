#pragma once

#include <deque>
#include <mutex>
#include <optional>


namespace Core
{
	namespace Containers
	{
		template <typename T>
		class ThreadDeque
		{
		public:

			ThreadDeque();
			~ThreadDeque();

			void push_front(const T& value);
			void push_front(T&& value);

			void push_back(const T& value);
			void push_back(T&& value);

			std::optional<T> front();
			std::optional<T> back();

			std::optional<T> front_and_pop();
			std::optional<T> back_and_pop();

			void pop_front();
			void pop_back();

			uint32_t size();
			bool empty();

			void clear();


		private:

			std::deque<T> _deque;
			std::mutex _m_mutex;

		};


		template <typename T>
		ThreadDeque<T>::ThreadDeque() { }

		template <typename T>
		ThreadDeque<T>::~ThreadDeque()
		{
			clear();
		}

		template <typename T>
		void ThreadDeque<T>::push_front(const T& value)
		{
			std::scoped_lock lock(_m_mutex);

			_deque.push_front(value);
		}

		template <typename T>
		void ThreadDeque<T>::push_front(T&& value)
		{
			std::scoped_lock lock(_m_mutex);

			_deque.push_front(std::move(value));
		}

		template <typename T>
		void ThreadDeque<T>::push_back(const T& value)
		{
			std::scoped_lock lock(_m_mutex);

			_deque.push_back(value);
		}

		template <typename T>
		void ThreadDeque<T>::push_back(T&& value)
		{
			std::scoped_lock lock(_m_mutex);

			_deque.push_back(std::move(value));
		}

		template <typename T>
		std::optional<T> ThreadDeque<T>::front()
		{
			std::scoped_lock lock(_m_mutex);

			if (_deque.empty())
			{
				return std::nullopt;
			}

			return _deque.front();
		}

		template <typename T>
		std::optional<T> ThreadDeque<T>::back()
		{
			std::scoped_lock lock(_m_mutex);

			if (_deque.empty())
			{
				return std::nullopt;
			}

			return _deque.back();
		}

		template <typename T>
		std::optional<T> ThreadDeque<T>::front_and_pop()
		{
			std::scoped_lock lock(_m_mutex);

			if (_deque.empty())
			{
				return std::nullopt;
			}

			T value = _deque.front();
			_deque.pop_front();

			return value;
		}

		template <typename T>
		std::optional<T> ThreadDeque<T>::back_and_pop()
		{
			std::scoped_lock lock(_m_mutex);

			if (_deque.empty())
			{
				return std::nullopt;
			}

			T value = _deque.back();
			_deque.pop_back();

			return value;
		}

		template <typename T>
		void ThreadDeque<T>::pop_front()
		{
			std::scoped_lock lock(_m_mutex);

			if (!_deque.empty())
			{
				_deque.pop_front();
			}
		}

		template <typename T>
		void ThreadDeque<T>::pop_back()
		{
			std::scoped_lock lock(_m_mutex);

			if (!_deque.empty())
			{
				_deque.pop_back();
			}
		}

		template <typename T>
		uint32_t ThreadDeque<T>::size()
		{
			std::scoped_lock lock(_m_mutex);

			return _deque.size();
		}

		template <typename T>
		bool ThreadDeque<T>::empty()
		{
			std::scoped_lock lock(_m_mutex);

			return _deque.empty();
		}

		template <typename T>
		void ThreadDeque<T>::clear()
		{

		}
	}
}
