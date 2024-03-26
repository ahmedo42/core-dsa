#include<vector>
#include<iostream>
#include<string>
#include<cassert>

class TrieNode{
  public:
    std::vector<TrieNode*> children;
    bool is_terminal = false;
    TrieNode(){
        children.resize(26, nullptr);
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    
    void insert(std::string word) {
        TrieNode *curr = root;
        for(char c : word){
            int idx = int(c) - 'a';
            if (curr->children[idx] == nullptr){
                curr->children[idx] = new TrieNode();
            }
            curr = curr->children[idx];
        }
        curr->is_terminal = true;
    }
    
    bool search(std::string word) {
        TrieNode *curr = root;
        for(char c : word){
            int idx = int(c) - 'a';
            if (curr->children[idx] == nullptr){
                return false;
            }
            curr = curr->children[idx];
        }
        return curr->is_terminal;
    }
    
    bool startsWith(std::string prefix) {
        TrieNode *curr = root;
        for(char c : prefix){
            int idx = int(c) - 'a';
            if (curr->children[idx] == nullptr){
                return false;
            }
            curr = curr->children[idx];
        }
        return true;
    }
};

int main(int argc, char const *argv[])
{
    Trie trie =  Trie();
    trie.insert("apple");
    trie.search("apple");   // return True
    trie.search("app");     // return False
    trie.startsWith("app"); // return True
    trie.insert("app");
    trie.search("app");     // return True
    return 0;
}
