#ifndef BINTREE_H
#define BINTREE_H

#include <memory>
#include <functional>
// 暂时使用标准库，stack.h queue.h完成后替换
#include <stack>
#include <queue>

using Node = struct Node;
using NodePtrShared = std::shared_ptr<Node>;
using NodePtrWeak = std::weak_ptr<Node>;

struct Node
{
    std::shared_ptr<Node> lchild{nullptr};
    std::shared_ptr<Node> rchild{nullptr};
    std::shared_ptr<Node> parent{nullptr};
    int data;
    bool lthread{false};
    bool rthread{false};
};

class BinTree
{
protected:
    NodePtrShared _root;
private:
    void PrevTravRecur(NodePtrShared node, std::function<void (int&)> func)
    {
        if(node == nullptr) return;
        func(node->data);
        PrevTravRecur(node->lchild, func);
        PrevTravRecur(node->rchild, func);
    }
    void PrevTrav(std::function<void (int&)> func)
    {
        std::stack<NodePtrShared> ss;
        ss.push(_root);
        while(!ss.empty())
        {
            auto tmp = ss.top();
            func(tmp->data);
            if(tmp->lchild!= nullptr)
                ss.push(tmp->lchild);
            else if(tmp->rchild != nullptr)
                ss.push(tmp->rchild);
        }
    }
    void InTravRecur(NodePtrShared node, std::function<void (int&)> func)
    {
        if(node == nullptr) return;
        PrevTravRecur(node->lchild, func);
        func(node->data);
        PrevTravRecur(node->rchild, func);
    }

    void GoToMostLeft(std::stack<NodePtrShared>& ss, NodePtrShared node)
    {
        auto l = node;
        ss.push(l);
        while(l->lchild != nullptr)
        {
            l = l->lchild;
            ss.push(l);
        }
    }

    // not complete
    void InTrav(std::function<void (int&)> func)
    {
        std::stack<NodePtrShared> ss;

        GoToMostLeft(ss, _root);
        do {
            auto tmp = ss.top();
            func(tmp->data);
            if(tmp->rchild!= nullptr)
            {
                GoToMostLeft(ss, tmp->rchild);
            }
            ss.pop();
        } while(!ss.empty());
    }
    void PostTravRecur(NodePtrShared node, std::function<void (int&)> func)
    {
        if(node == nullptr) return;
        PrevTravRecur(node->lchild, func);
        PrevTravRecur(node->rchild, func);
        func(node->data);
    }
    void PostTrav(std::function<void (int&)> func)
    {
        std::stack<NodePtrShared> ss;
        NodePtrShared LastVisited{nullptr};
        GoToMostLeft(ss, _root);
        while(!ss.empty())
        {
            auto tmp = ss.top();
            if(tmp->rchild!= nullptr && tmp->rchild != LastVisited)
            {
                GoToMostLeft(ss, tmp->rchild);
            } else {
                tmp = ss.top();
                func(tmp->data);
                LastVisited = tmp;
                ss.pop();
            }
        }
    }

public:
    void PrevTraverse(std::function<void (int &)> func)
    {
        PrevTrav(func);
    }
    void InTraverse(std::function<void (int &)> func)
    {
        InTrav(func);
    }
    void PostTraverse(std::function<void (int &)> func)
    {
        PostTrav(func);
    }

    void LevelTrav(std::function<void (int&)> func)
    {
        std::queue<NodePtrShared> qu;
        qu.push(_root);

        while(!qu.empty())
        {
            auto tmp = qu.front();
            if(tmp->lchild != nullptr) qu.push(tmp->lchild);
            if(tmp->rchild != nullptr) qu.push(tmp->rchild);
            func(tmp->data);
            qu.pop();
        }
    }

    // big five
public:
    BinTree()=default;

    explicit BinTree(const BinTree& tree)
    {
        std::queue<NodePtrShared> this_qu;
        std::queue<NodePtrShared> tree_qu;

        this_qu.push(_root);
        tree_qu.push(tree._root);

        while(!tree_qu.empty())
        {
            if(tree_qu.front()->lchild != nullptr)
            {
                this_qu.front()->lchild = std::make_shared<Node>();
            }
            if(tree_qu.front()->rchild != nullptr)
            {
                this_qu.front()->rchild = std::make_shared<Node>();
            }
            this_qu.front()->data = tree_qu.front()->data;
            this_qu.pop();
            tree_qu.pop();
        }
    }

    explicit BinTree(BinTree&& tree)
    {
        *this = std::move(tree);
    }

    BinTree& operator=(const BinTree& tree)
    {
        auto tmp = BinTree(tree);
        *this = std::move(tmp);
        return *this;
    }

    BinTree& operator=(BinTree&& tree) noexcept
    {
        this->_root = tree._root;
        tree._root = nullptr;
        return *this;
    }
    virtual ~BinTree()=default;
};



#endif
