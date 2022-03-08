#ifndef LIST_UNIQ_H
#define LIST_UNIQ_H

#include "list.h"

struct Node
{
	int data;
	std::shared_ptr<Node> next;
};
class List_Duel : public List
{
private:

	std::shared_ptr<Node> head {std::make_shared<Node>()};

public:

// big five
public:
	List_Duel()
	{
		head->next = head;
	}

	explicit List_Duel(List_Duel& list)
	{
	}
	explicit List_Duel(List_Duel&& list)
	{
	}

	List_Duel& operator=(List_Duel& list)
	{
	}

	List_Duel& operator=(List_Duel&& list)
	{
	}
	~List_Duel()=default;


};


#endif
