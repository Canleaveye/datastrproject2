
#include <iostream>
#include <map>
#include <string>
#include <thread> // 模拟延时
#include <chrono> // 模拟延时
#include <set>    

using namespace std;


// 基于STL设计红黑树类
template <typename key,typename value>
class RedBlackTree {
private:
    // 基于STL的map实现红黑树
    std::map<key,value> rb_tree; 

public:
    // 插入数据
    bool insert(const key& k,const value& v);

    // 删除数据
    bool remove(const key& k);

    // 查找数据
    value* find(const key& k);

    // 修改数据
    bool modify(const key& k,const value& v);
    
    // 获取红黑树大小
    int size() const;

    // 打印红黑树内容
    void display() const;

    // 获取红黑树第一个元素
    value* getFirst() const;
};


template <typename key,typename value>
// 获取红黑树大小
int RedBlackTree<key,value>::size() const {
    return rb_tree.size();
}

// 插入数据
template <typename key,typename value>
bool RedBlackTree<key,value>::insert(const key& k,const value& v) {
    auto res = rb_tree.insert({k,v});
    if(res.second) {
        return true;
    }
    else {
        cout << "插入失败：键已存在" << endl;
        return false;
    }
}

// 删除数据
template <typename key,typename value>
bool RedBlackTree<key,value>::remove(const key& k) {
    auto res = rb_tree.erase(k);
    if(res) {
        return true;
    }
    else {
        cout << "删除失败：键不存在" << endl;
        return false;
    }
}

// 查找数据
template <typename key,typename value>
value* RedBlackTree<key,value>::find(const key& k) {
    auto res = rb_tree.find(k);
    if(res != rb_tree.end()) {
        return &(res->second);
    }
    else {
        cout << "查找失败：键不存在" << endl;
        return nullptr;
    }
}

// 修改数据
template <typename key,typename value>
bool RedBlackTree<key,value>::modify(const key& k,const value& v) {
    auto res = rb_tree.find(k);
    if(res != rb_tree.end()) {
        res->second = v;
        return true;
    }
    else {
        cout << "修改失败：键不存在" << endl;
        return false;
    }
}

// 展示红黑树
template <typename key,typename value>
void RedBlackTree<key,value>::display() const {
    for(auto& item : rb_tree) {
        cout << item.first << ": " << item.second << endl;
    }
}

// 获取红黑树第一个元素(为调度器设计)
template <typename key,typename value>
value* RedBlackTree<key,value>::getFirst () const {
    if(rb_tree.empty()) {
        return nullptr;
    }
    else {
        return &(rb_tree.begin()->second);
    }
}