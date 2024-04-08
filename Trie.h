#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
// TrieNode class represents a node in the trie data structure
class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode();
    ~TrieNode();
};
// Trie class represents a trie data structure
class Trie {
private:
    TrieNode* root;

    void destroyTrie(TrieNode* node);
    int countHelper(TrieNode* node);
    int getSizeHelper(TrieNode* node);
    void completeHelper(TrieNode* node, const std::string& prefix, std::vector<std::string>& completions);
    void copyTrie(TrieNode* source, TrieNode*& dest);

public:
    Trie();
    ~Trie();

    bool insert(const std::string& word);
    int count();
    int getSize();
    bool find(const std::string& word);
    int completeCount(const std::string& prefix);
    std::vector<std::string> complete(const std::string& prefix);
    Trie& operator=(const Trie& other);
};

#endif // TRIE_H
