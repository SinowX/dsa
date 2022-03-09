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

    virtual std::shared_ptr<List> copy() override
    {
        auto tmp_list = std::make_shared<List_Duel>(*this);
        return std::dynamic_pointer_cast<List>(tmp_list);
    }

    // insert data next to pos
    void insert(NodePtrWeak pos, const int& data) override
    {
        auto tmp = data;
        insert(pos , std::move(tmp));
    }
    void insert(NodePtrWeak pos, int&& data) override
    {
        auto tmp_node = std::make_shared<Node>(data);
        tmp_node->next = pos.lock()->next;
        pos.lock()->next->prev = tmp_node;
        tmp_node->prev = pos.lock();
        pos.lock()->next = tmp_node;
        _size++;
    }

    virtual void insert(NodePtrWeak pos, List& list)
    {
        return insert(pos, List_Duel(dynamic_cast<List_Duel&>(list)));
    }
    virtual void insert(NodePtrWeak pos, List_Duel&& list)
    {
        auto pos_ptr = pos.lock();
        decltype(pos_ptr) tmp_ptr;

        if(!pos_ptr) return;

        list._head->prev->next = pos_ptr->next;
        pos_ptr->next->prev = list._head->prev;
        pos_ptr->next = list._head->next;
        list._head->next->prev = pos_ptr;

        list._head = nullptr;
    }

    void append(const int& data) override
    {
        auto tmp_node = std::make_shared<Node>(data);
        tmp_node->prev = _head->prev;
        _head->prev->next = tmp_node;
        tmp_node->next = _head;
        _head->prev = tmp_node;
        _size++;
    }
    void append(int&& data) override
    {
        append(data);
    }
    void remove(const int& data) override
    {
        auto tmp_ptr = find(data).lock();

        if(tmp_ptr != nullptr && tmp_ptr != _head)
        {
            tmp_ptr->prev->next = tmp_ptr->next;
            tmp_ptr->next->prev = tmp_ptr->prev;
        }
    }
    NodePtrWeak find(const int& data) override
    {
        NodePtrShared tmp_ptr = _head->next;

        while(tmp_ptr != _head)
        {
            if(tmp_ptr->data == data)
                break;
            tmp_ptr = tmp_ptr->next;
        }

        return tmp_ptr;
    }
    void sort() override
    {
        NodePtrShared list1{_head->next};
        NodePtrShared cur{_head->next};
        cur = list1;
        for(std::size_t i=0; i <_size/2; i++) cur = cur->next;
        mergesort(list1, _size/2, cur, _size - _size/2);
    }

private:
    NodePtrShared merge(NodePtrShared list1, std::size_t size_1,
               NodePtrShared list2, std::size_t size_2)
    {
        std::size_t i{0}, j{0};
        NodePtrShared cur{nullptr}, res{nullptr};
        auto pos_1 = list1;
        auto pos_2 = list2;
        while (i<size_1 || j<size_2)
        {
            if(cur == nullptr)
            {
                if(i<size_1 && pos_1->data < pos_2->data)
                {
                    cur = pos_1;
                    pos_1=pos_1->next;
                    i++;
                } else {
                    cur = pos_2;
                    pos_2 = pos_2->next;
                    j++;
                }
                res = cur;
                continue;
            }
            if(i<size_1 && pos_1->data < pos_2->data)
            {
                cur->next = pos_1;
                pos_1->prev = cur;

                cur = pos_1;
                pos_1 = pos_1->next;
                i++;
            } else {
                cur->next = pos_2;
                pos_2->prev = cur;

                cur = pos_2;
                pos_2 = pos_2->next;
                j++;
            }
        }

        return res;
    }
    void mergesort(NodePtrShared list1, std::size_t size_1,
                   NodePtrShared list2, std::size_t size_2)
    {
        if(list1 == list2) return;

        NodePtrShared cur{_head};

        cur = list1;
        for(std::size_t i=0; i <size_1/2; i++) cur = cur->next;
        mergesort(list1, size_1/2, cur, size_1 - size_1/2);

        cur = list2;
        for(std::size_t i=0; i <size_2/2; i++) cur = cur->next;
        mergesort(list1, size_2/2, cur, size_1 - size_2/2);

        merge(list1, size_1, list2, size_2);
    }


// big five
public:
	List_Duel()
	{
		_head->next = _head;
		_head->prev = _head;
	}

	explicit List_Duel(const List_Duel& list)
	{
        auto tmp = List_Duel();
        NodePtrShared tmp_ptr= tmp._head, ptr = list._head;
        do
        {
            tmp_ptr->next = std::make_shared<Node>(ptr->next->data);
            tmp_ptr->next->prev = tmp_ptr;
            tmp_ptr = tmp_ptr->next;
            ptr = ptr->next;
        } while( ptr->next != list._head);
        tmp_ptr->next = _head;
        tmp_ptr->next->prev = tmp_ptr;
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
