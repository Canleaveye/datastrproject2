#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H


#include <iostream>
#include <map>
#include <string>
#include <thread> // 模拟延时
#include <chrono> // 模拟延时
#include <set>    
#include <vector>  // 添加 vector 头文件

using namespace std;

// 基于STL设计红黑树类
template <typename key, typename value>
class RedBlackTree {
private:
    // 基于STL的map实现红黑树
    std::map<key, value> rb_tree;

public:
    // 插入数据
    bool insert(const key& k, const value& v);

    // 删除数据
    bool remove(const key& k);

    // 查找数据
    value* find(const key& k);

    // 修改数据
    bool modify(const key& k, const value& v);

    // 获取红黑树大小
    int size() const;

    // 打印红黑树内容
    void display() const;

    // 获取所有键值对
    std::vector<std::pair<key, value>> getAll() const {
        std::vector<std::pair<key, value>> result;
        result.reserve(rb_tree.size());

        for (const auto& item : rb_tree) {
            result.emplace_back(item.first, item.second);
        }

        return result;
    }
};

// 获取红黑树大小
template <typename key, typename value>
int RedBlackTree<key, value>::size() const {
    return rb_tree.size();
}

// 插入数据
template <typename key, typename value>
bool RedBlackTree<key, value>::insert(const key& k, const value& v) {
    auto res = rb_tree.insert({ k, v });
    if (res.second) {
        return true;
    }
    else {
        cout << "插入失败：键已存在" << endl;
        return false;
    }
}

// 删除数据
template <typename key, typename value>
bool RedBlackTree<key, value>::remove(const key& k) {
    auto res = rb_tree.erase(k);
    if (res) {
        return true;
    }
    else {
        cout << "删除失败：键不存在" << endl;
        return false;
    }
}

// 查找数据
template <typename key, typename value>
value* RedBlackTree<key, value>::find(const key& k) {
    auto res = rb_tree.find(k);
    if (res != rb_tree.end()) {
        return &(res->second);
    }
    else {
        cout << "查找失败：键不存在" << endl;
        return nullptr;
    }
}

// 修改数据
template <typename key, typename value>
bool RedBlackTree<key, value>::modify(const key& k, const value& v) {
    auto res = rb_tree.find(k);
    if (res != rb_tree.end()) {
        res->second = v;
        return true;
    }
    else {
        cout << "修改失败：键不存在" << endl;
        return false;
    }
}

// 展示红黑树
template <typename key, typename value>
void RedBlackTree<key, value>::display() const {
    for (const auto& item : rb_tree) {
        cout << item.first << ": " << item.second << endl;
    }
}

#endif // REDBLACKTREE_H