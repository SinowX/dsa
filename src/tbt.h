//
// Created by Sinow on 2022/3/9.
//

#ifndef DSA_TBT_H
#define DSA_TBT_H

#include "bintree.h"

// 线索树
class ThreadTree: public BinTree
{
private:

    void GetPred(NodePtrShared cur)
    {
        if(cur->parent != nullptr && cur->parent->lthread)
        {
            cur->lthread = true;
            cur->lchild = cur->parent->lchild;
            return;
        } else {
            cur->lthread = false;
            return;
        }
    }

    void GetSucc(NodePtrShared cur)
    {
        if(cur->parent != nullptr && cur->parent->rthread)
        {
            cur->rthread = true;
            cur->rchild = cur->parent->rchild;
            return;
        } else {
            cur->rthread = false;
            return;
        }
    }

public:
    // 前驱
    void Thread()
    {
        std::queue<NodePtrShared> qu;
        qu.push(_root);
        while(!qu.empty())
        {
            auto tmp = qu.front();
            if(tmp->lchild != nullptr) qu.push(tmp->lchild);
            if(tmp->rchild != nullptr) qu.push(tmp->rchild);
            GetPred(tmp);
            GetSucc(tmp);
            qu.pop();
        }
    }

    void UnThread()
    {
        std::queue<NodePtrShared> qu;
        qu.push(_root);
        while(!qu.empty())
        {
            auto tmp = qu.front();
            if(tmp->lchild != nullptr) qu.push(tmp->lchild);
            if(tmp->rchild != nullptr) qu.push(tmp->rchild);

            if(tmp->lthread)
            {
                tmp->lthread = false;
                tmp->lchild = nullptr;
            }
            if(tmp->rthread)
            {
                tmp->rthread = false;
                tmp->rchild = nullptr;
            }
            qu.pop();
        }
    }
};

#endif //DSA_TBT_H
