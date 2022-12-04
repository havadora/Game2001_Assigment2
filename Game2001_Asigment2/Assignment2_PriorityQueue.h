#pragma once
#include <cassert>

template <class T> class LinkIterator;
template <class T> class LinkedList;

template <class T>
class LinkNode
{
public:
	friend class LinkIterator<T>;
	friend class LinkedList<T>;
private:
	T m_data;
	LinkNode* m_next;	
	LinkNode* m_previous;
};
template <class T>
class LinkIterator
{
public:
	friend class LinkedList<T>;

	LinkIterator()
	{
		m_node = nullptr;
	}
	~LinkIterator() {}
	
	void operator=(LinkNode<T>* node)
	{
		m_node = node;
	}
	T& operator*()
	{
		assert(m_node != nullptr);
		return m_node->m_data;
	}
	void operator++(int) // Postfix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_next;
	}
	void operator--(int)	// Postfix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_previous;
	}
	bool operator!=(LinkNode<T>* node)
	{
		return (m_node != node);
	}
	bool operator==(LinkNode<T>* node)
	{
		return (m_node == node);
	}
	bool isValid()
	{
		return (m_node != NULL);
	}

private:
	LinkNode<T>* m_node;	// Pointer to a node in the linked list
};
template <class T>
class LinkedList
{
public:
	
	
	LinkedList() : m_size(0), m_root(nullptr), m_lastNode(nullptr) {}
	~LinkedList()
	{
		while (m_root)
		{
			Pop();
		}
	}
	
	LinkNode<T>* Begin()
	{
		assert(m_root != nullptr);
		return m_root;
	}
	LinkNode<T>* End()
	{
		return nullptr;
	}
	LinkNode<T>* Last()
	{
		assert(m_lastNode != nullptr);
		return m_lastNode;
	}
	
	void Insert(LinkIterator<T>& it, T newData)
	{
		assert(it.m_node != nullptr);
		LinkNode<T>* node = new LinkNode<T>;
		assert(node != nullptr);

		node->m_data = newData;
		node->m_next = it.m_node;
		node->m_previous = it.m_node->m_previous;

		if (node->m_previous != nullptr)
		{
			
			node->m_previous->m_next = node;
		}

		it.m_node->m_previous = node;

		
		if (it.m_node == m_root)
		{
			m_root = node;
		}

		m_size++;
	}	
	void Pop()
	{
		assert(m_root != nullptr);
		LinkNode<T>* temp = m_root;
		m_root = m_root->m_next;

		if (m_root != nullptr)
		{
			m_root->m_previous = nullptr;
		}
		else
		{
			m_lastNode = nullptr;
		}

		delete temp;
		temp = nullptr;

		m_size = (m_size == 0 ? m_size : m_size - 1);
	}
	void Push(T newData)
	{
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != nullptr);
		node->m_data = newData;
		node->m_next = nullptr;
		node->m_previous = nullptr;
		if (m_lastNode != nullptr) 
		{
			m_lastNode->m_next = node;
			node->m_previous = m_lastNode;
		}
		else 
		{
			m_root = node;
		}

		m_lastNode = node;

		m_size++;
	}
	
	int GetSize()
	{
		return m_size;
	}
private:
	int m_size;					
	LinkNode<T>* m_root;		
	LinkNode<T>* m_lastNode;	
};
template<class T, class CMP>
class PriorityQueue
{
public:
	PriorityQueue(int size)
	{
		assert(size > 0);
		m_size = size;
	}
	~PriorityQueue() {}
	void push(T val)
	{
		assert(m_elements.GetSize() < m_size);

		if (m_elements.GetSize() == 0)
		{
			m_elements.Push(val);
		}
		else
		{
			LinkIterator<T> it;
			it = m_elements.Begin();

			CMP cmp;

			while (it.isValid())
			{
				if (cmp(val, *it))
				{
					break;	
				}

				it++;
			}

			if (it.isValid())
			{
				m_elements.Insert(it, val);
			}
			else
			{
				m_elements.Push(val);
			}
		}
	}

	void pop()
	{
		m_elements.Pop();
	}

	T& front()
	{
		LinkIterator<T> it;
		it = m_elements.Begin();

		return *it;
	}
	T& back()
	{
		LinkIterator<T> it;
		it = m_elements.Last();

		return *it;
	}
	int GetSize()
	{
		return m_elements.GetSize();
	}
	int GetMaxSize()
	{
		return m_size;
	}
	bool isEmpty()
	{
		return (m_elements.GetSize() == 0);
	}
	void Resize(int size)
	{
		assert(size > 0);
		m_size = size;
	}
private:
	LinkedList<T> m_elements;
	int m_size;
};