#include "RedBlackTree.h"

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