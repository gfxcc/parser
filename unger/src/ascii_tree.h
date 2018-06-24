//
// Created by Yong Cao at Dec/26/2017
//

#include <string>
#include <vector>
#include <memory>
#include <stack>

namespace AsciiTree {

using std::shared_ptr;
using std::string;
using std::vector;
using std::stack;
using std::shared_ptr;
using std::make_shared;

class Node {
public:
    Node(const string& data) : data(data) {}
    Node() {}
    string data;
    vector<shared_ptr<Node>> children;
};


class Tree {
public:

    Tree();

    Node* get_root();

    // class Node {
    //     string data;
    //     Node* left, * right
    // }; 
    //
    //
    template <typename T>
    void load_binary_tree(T* root) {
        stack<T*> st_sample;
        stack<Node*> st_internal;

        root_ = make_shared<Node>(root->data);

        st_sample.push(root);
        st_internal.push(root_.get());

        // build internal tree by pre-order traversal
        while (st_sample.size()) {
            auto cur_sample = st_sample.top();
            auto cur_internal = st_internal.top();
            st_sample.pop();
            st_internal.pop();

            if (cur_sample->right) {
                // create right node
                cur_internal->children.push_back(make_shared<Node>(cur_sample->right->data));
                st_sample.push(cur_sample->right);
                st_internal.push(cur_internal->children.back().get());
            }
            if (cur_sample->left) {
                // create left node
                cur_internal->children.push_back(make_shared<Node>(cur_sample->left->data));
                st_sample.push(cur_sample->left);
                st_internal.push(cur_internal->children.back().get());
            }
        }
    }
    
    //
    // class Node {
    //     string data;
    //     vector<Node*> children;
    // }
    // 
    template <typename T>
    void load_tree(T* root) {

        stack<T*> st_sample;
        stack<Node*> st_internal;

        root_ = make_shared<Node>(root->data);

        st_sample.push(root);
        st_internal.push(root_.get());

        // build internal tree by pre-order traversal
        while (st_sample.size()) {
            auto cur_sample = st_sample.top();
            auto cur_internal = st_internal.top();
            st_sample.pop();
            st_internal.pop();

            for (auto& child : cur_sample->children) {
                cur_internal->children.push_back(make_shared<Node>(child->data));
                st_sample.push(child);
                st_internal.push(cur_internal->children.back().get());
            }
        }

    }

    void print_tree(bool vertical = true);

    void set_root(const string& data) {
        root_->data = data;
    }

    void reset() {
        root_ = std::make_shared<Node>();
        prefix.clear();
    }

private:

    void pre_order(Node* node);
    void push_level(char c);
    void pop_level();

    shared_ptr<Node> root_;
    string prefix;
};

} // namespace As
