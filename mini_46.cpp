#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;


struct Node {
    string terminal;
    int invalidation_counter;
    unordered_map<char, Node *> prefix_go;
    unordered_map<char, Node *> suffix_go;
    Node *parent;
    Node *sufflink;
    char from_parent;
    vector<string> all_patterns; // only for root

    Node(int total_patterns, Node *p, char fp) {
        terminal = "";
        invalidation_counter = total_patterns;
        from_parent = fp;
        parent = p;
        sufflink = nullptr;
        prefix_go = unordered_map<char, Node *>();
        suffix_go = unordered_map<char, Node *>();
        all_patterns = vector<string>();
    }
};

Node *suf(Node *v, Node *root);
Node *next(Node *v, char c, Node *root);

void invalidate_node(Node *v, int total_patterns) {
    if (v->invalidation_counter < total_patterns) {
        v->invalidation_counter = total_patterns;
        v->suffix_go.clear();
        v->sufflink = nullptr;
    }
}

Node *suf(Node *v, Node *root) {
    invalidate_node(v, root->invalidation_counter);

    if (v->sufflink == nullptr) {
        if (v == root || v->parent == root)
            v->sufflink = root;
        else
            v->sufflink = next(suf(v->parent, root), v->from_parent, root);
    }
    return v->sufflink;
}

Node *next(Node *v, char c, Node *root) {
    invalidate_node(v, root->invalidation_counter);

    if (v->prefix_go.contains(c))
        return v->prefix_go[c];

    if (v == root)
        return root;

    if (v->suffix_go.contains(c))
        return v->suffix_go[c];

    v->suffix_go[c] = next(suf(v, root), c, root);
    return v->suffix_go[c];
}


void add_new_pattern(Node *root, string pattern) {
    invalidate_node(root, root->invalidation_counter + 1);

    Node *current_node = root;
    for (auto c : pattern) {
        if (!current_node->prefix_go.contains(c))
            current_node->prefix_go[c] = new Node(root->invalidation_counter, current_node, c);
        current_node = current_node->prefix_go[c];
    }

    if (current_node->terminal.size() > 0) {
        throw runtime_error("Found 2 exact similar patterns");
    }

    current_node->terminal = pattern;
    root->all_patterns.push_back(pattern);
}


void count_sufflink(Node *current_node, Node *root, unordered_map<string, int> &counter) {

    while (current_node != root) {
        if (current_node->terminal.size() > 0)
            counter[current_node->terminal]++;

        current_node = suf(current_node, root);
    }
}


void findall(Node *root, string str) {

    unordered_map<string, int> counter;
    for (auto &s : root->all_patterns) {
        counter[s] = 0;
    }

    Node *current_node = root;
    for (auto c : str) {
        current_node = next(current_node, c, root);
        count_sufflink(current_node, root, counter);
    }

    for (auto &pair : counter)
        cout << pair.first << ": " << pair.second << '\n';
}


signed main() {

    Node *root = new Node(0, nullptr, 0);

    add_new_pattern(root, "aab");
    add_new_pattern(root, "abba");
    add_new_pattern(root, "bbbab");


    string text = "bbbaabbbbabbbabba";
    findall(root, text);

    cout << "====================\n";
    add_new_pattern(root, "bbab");
    add_new_pattern(root, "bba");
    findall(root, text);

    return 0;
}

