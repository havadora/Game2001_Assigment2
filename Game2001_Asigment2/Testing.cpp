#include <iostream>
#include "Assignment2_PriorityQueue.h"
using namespace std;

template<class T>
class less_cmp 
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return lVal < rVal;
	}
};

class NetworkMessage
{
public:
	NetworkMessage() : m_priority(0), m_id(0) {}
	NetworkMessage(int p, int id) : m_priority(p), m_id(id) {}
	~NetworkMessage() {}

	int GetPriority()
	{
		return m_priority;
	}
	int GetID()
	{
		return m_id;
	}

	
	bool operator<(NetworkMessage& m)
	{
		
		if (m_priority < m.GetPriority())
		{
			return true;
		}
		else if (m_id < m.GetID())
		{
			return true;
		}

		return false;
	}
	bool operator>(NetworkMessage& m)
	{
		return !(*this < m);	
	}
private:
	int m_priority;
	int m_id;
};

int main()
{

	const int SIZE = 6;
	PriorityQueue<NetworkMessage, less_cmp<NetworkMessage>> que(SIZE);
	que.push(NetworkMessage(2, 435));
	que.push(NetworkMessage(3, 100));
	que.push(NetworkMessage(2, 286));
	que.push(NetworkMessage(1, 362));
	que.push(NetworkMessage(3, 435));
	que.push(NetworkMessage(1, 1000));
	
	cout << "Priority queue content (Size - " << que.GetSize() << ") : " << endl;

	while (que.isEmpty() == false)
	{
		cout << "  Priority: " << que.front().GetPriority();
		cout << "  ID: " << que.front().GetID();
		cout << endl;

		que.pop();
	}

	cout << endl;

	if (que.isEmpty() == true)
	{
		cout << "The container is empty." << endl;
	}
	else
	{
		cout << "The container is NOT empty." << endl;
	}
	
	
	return 0;
}