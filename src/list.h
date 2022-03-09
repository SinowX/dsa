#ifndef LIST_H
#define LIST_H

#include <memory>

using Node = struct Node;
using NodePtrShared = std::shared_ptr<Node>;
using NodePtrWeak = std::weak_ptr<Node>;
class List
{
public:
	virtual ~List()=0;
	virtual bool empty() const = 0;
	virtual std::size_t size() const = 0;
    virtual std::shared_ptr<List> copy()=0;
	virtual void insert(NodePtrWeak pos, const int& data)=0;
	virtual void insert(NodePtrWeak pos, int&& data)=0;
	virtual void append(const int& data)=0;
    virtual void append(int&& data)=0;
	virtual void remove(const int& data)=0;
	virtual NodePtrWeak find(const int& data)=0;
//	virtual void merge(NodePtrWeak pos, List&& list)=0;
	virtual void sort()=0;
};


#endif
