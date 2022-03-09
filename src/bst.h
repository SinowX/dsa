#ifndef BST_H
#define BST_H

#include "bintree.h"

class BSTree: public BinTree
{
private:
    bool _root_value_setted{false};
    NodePtrShared GetInsertPosition(int value, NodePtrShared start)
    {
        if(value<start->data)
        {
            if(start->lchild == nullptr)
            {
                auto node = std::make_shared<Node>();
                node->parent = start;
                start->lchild = node;
                return node;
            }
            return GetInsertPosition(value, start->lchild);
        } else if(value>start->data) {
            if(start->rchild == nullptr)
            {
                auto node = std::make_shared<Node>();
                node->parent=start;
                start->rchild = node;
                return node;
            }
            return GetInsertPosition(value, start->rchild);
        } else return nullptr; // duplicated
    }

    virtual NodePtrShared Find(int value, NodePtrShared start)
    {
        if(start == nullptr) return nullptr;
        if(value<start->data)
        {
            return Find(value, start->lchild);
        } else if(value>start->data) {
            return Find(value, start->rchild);
        } else {
            return start;
        }
    }

public:
    // not allow random generate this tree
    // BSTree need attach node to its right place
    void RandomGenerate()=delete;
    // not allow duplication
    virtual void AddNode(int value)
    {
        if(!_root_value_setted)
        {
            _root->data = value;
            return;
        }
        auto posi = GetInsertPosition(value, _root);
        if(posi == nullptr)
            return;
        posi->data = value;
    }

    virtual void DelNode(int value)
    {
        if(!_root_value_setted) return;
        auto posi = GetInsertPosition(value, _root);
        if(posi == nullptr) return;

        if(posi->parent->lchild == posi)
            posi->parent->lchild = nullptr;
        else
            posi->parent->rchild = nullptr;
    }

    // nullptr if not found
    virtual NodePtrShared Find(int value)
    {
        if(!_root_value_setted) return nullptr;
        return Find(value, _root);
    }

};


#endif