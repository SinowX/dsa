#ifndef LIST_DUEL_H
#define LIST_DUEL_H

#include "list.h"

struct Node
{
	int data;
	std::shared_ptr<Node> prev;
	std::shared_ptr<Node> next;
    Node(int d=0):data{d}{};
};

class List_Duel : public List
{
private:

	std::shared_ptr<Node> _head {std::make_shared<Node>()};
	std::size_t _size{0};

public:
	bool empty() const override { return !_size; }
    std::size_t size() const override { return _size; }

    void insert(NodePtrWeak pos, int& data) override;
    void insert(NodePtrWeak pos, int&& data) override;
    void append(int& data) override;
    void remove(int& data) override;
    NodePtrWeak find(int& data) override;
    void merge(NodePtrWeak pos, List&& list) override;
    void sort() override;


// big five
public:
	List_Duel()
	{
		_head->next = _head;
		_head->prev = _head;
	}

    // 未完成，只实现了单链表的情形
	explicit List_Duel(const List_Duel& list)
	{
        auto tmp = List_Duel();
        NodePtrShared tmp_ptr= tmp._head, ptr = list._head;
        do
        {
            tmp_ptr->next = std::make_shared<Node>(ptr->next->data);
            tmp_ptr = tmp_ptr->next;
        } while( ptr->next != list._head);
        tmp_ptr->next = _head;
        *this = std::move(tmp);
	}
	explicit List_Duel(List_Duel&& list)
	{
        *this = std::move(list);
	}

	List_Duel& operator=(List_Duel& list) noexcept
	{
        List_Duel tmp(list);
        *this = std::move(tmp);
        return *this;
	}

	List_Duel& operator=(List_Duel&& list) noexcept
	{
        this->_head = list._head;
        this->_size = list._size;
        list._head = nullptr;
        list._size = 0;
        return *this;
	}
	~List_Duel()=default;
};

#endif
