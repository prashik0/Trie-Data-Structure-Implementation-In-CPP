#include <bits/stdc++.h>
using namespace std;

struct trie_node{
    trie_node *children[26];
    bool isendofword;
};

trie_node* getnode(){
    trie_node *pnode = new trie_node;
    for(int i = 0; i < 26; ++i) pnode->children[i] = NULL;
    pnode->isendofword = false;
    return pnode;
}

void insert(trie_node *root, string key){
    int n = key.size();
    trie_node *pcrawl = root;
    for(int i = 0; i < n; ++i){
        int idx = key[i] - 'a';
        if(!pcrawl->children[idx]) pcrawl->children[idx] = getnode();
        pcrawl = pcrawl->children[idx];
    }
    pcrawl->isendofword = true;
}
bool search(trie_node *root, string key){
    int n = key.size();
    trie_node *pcrawl = root;
    for(int i = 0; i < n; ++i){
        int idx = key[i] - 'a';
        if(!pcrawl->children[idx]) return false;
        pcrawl = pcrawl->children[idx];
    }
    return pcrawl->isendofword;
}

bool isempty(trie_node *root){
    for(int i = 0; i < 26; ++i) if(root->children[i] != NULL) return false;
    return true;
}

trie_node* remove(trie_node *root, string key, int depth = 0){ // delete
    if(root == NULL) return NULL;

    if(depth == key.size()){
        if(root->isendofword) root->isendofword = false;
        if(isempty(root)){
            delete (root);
            root = NULL;
        }
        return root;
    }

    int idx = key[depth] - 'a';
    root->children[idx] = remove(root->children[idx], key, depth + 1);

    if(isempty(root) && root->isendofword == false){
        delete (root);
        root = NULL;
    }

    return root;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector <string> v {"abcd", "abdc"};
    trie_node *root = getnode();
    int n = v.size();
    for(int i = 0; i < n; ++i) insert(root, v[i]);
    if(search(root, "abcd")) cout<<"Yes"<<'\n';
    else cout<<"No"<<'\n';
    if(search(root, "abdc")) cout<<"Yes"<<'\n';
    else cout<<"No"<<'\n';
    remove(root, "abcd");
    if(search(root, "abcd")) cout<<"Yes"<<'\n';
    else cout<<"No"<<'\n';
    if(search(root, "abdc")) cout<<"Yes"<<'\n';
    else cout<<"No"<<'\n';
    return 0;
}
