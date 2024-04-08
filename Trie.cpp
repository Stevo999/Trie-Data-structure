#include "Trie.h"

#include <iostream>
// TrieNode constructor
TrieNode::TrieNode() {
    for (int i = 0; i < 26; ++i) {
        children[i] = nullptr;
    }
    isEndOfWord = false;
}
// TrieNode destructor
TrieNode::~TrieNode() {
    for (int i = 0; i < 26; ++i) {
        delete children[i];
    }
}
// Trie constructor
Trie::Trie() {
    root = new TrieNode();
}
// Trie destructor
Trie::~Trie() {
    destroyTrie(root);
}
// Helper function to destroy trie recursively
void Trie::destroyTrie(TrieNode* node) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < 26; ++i) {
        destroyTrie(node->children[i]);
    }

    delete node;
}

// Function to insert a word into the trie
bool Trie::insert(const std::string& word) {
    TrieNode* current = root;
    for (char c : word) {
        int index = c - 'a';
        if (!current->children[index]) {
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    if (current->isEndOfWord) {
        return false; // Word already exists
    }
    current->isEndOfWord = true;
    return true; // Word inserted successfully
}
// Function to count the number of words in the trie
int Trie::count() {
    return countHelper(root);
}
// Helper function to count words recursively
int Trie::countHelper(TrieNode* node) {
    if (!node) {
        return 0;
    }
    int count = node->isEndOfWord ? 1 : 0;
    for (int i = 0; i < 26; ++i) {
        count += countHelper(node->children[i]);
    }
    return count;
}
// Function to calculate the total number of nodes in the trie
int Trie::getSize() {
    return getSizeHelper(root);
}
// Helper function to calculate size recursively
int Trie::getSizeHelper(TrieNode* node) {
    if (!node) {
        return 0;
    }
    int size = 1;
    for (int i = 0; i < 26; ++i) {
        size += getSizeHelper(node->children[i]);
    }
    return size;
}
// Function to check if a word exists in the trie
bool Trie::find(const std::string& word) {
    TrieNode* current = root;
    for (char c : word) {
        int index = c - 'a';
        if (!current->children[index]) {
            return false; // Word not found
        }
        current = current->children[index];
    }
    return current && current->isEndOfWord;
}
// Function to count the number of words in the trie that match a given prefix
int Trie::completeCount(const std::string& prefix) {
    TrieNode* current = root;
    for (char c : prefix) {
        int index = c - 'a';
        if (!current->children[index]) {
            return 0; // Prefix not found
        }
        current = current->children[index];
    }
    return countHelper(current); // Count words starting from the prefix node
}

std::vector<std::string> Trie::complete(const std::string& prefix) {
    std::vector<std::string> completions;
    TrieNode* current = root;
    for (char c : prefix) {
        int index = c - 'a';
        if (!current->children[index]) {
            return completions; // Prefix not found, return empty vector
        }
        current = current->children[index];
    }
    completeHelper(current, prefix, completions); // Find completions starting from the prefix node
    return completions;
}
// Helper function to find completions recursively
void Trie::completeHelper(TrieNode* node, const std::string& prefix, std::vector<std::string>& completions) {
    if (!node) {
        return;
    }
    if (node->isEndOfWord) {
        completions.push_back(prefix); // Add word to completions if it's the end of a word
    }
    for (int i = 0; i < 26; ++i) {
        char c = 'a' + i;
        completeHelper(node->children[i], prefix + c, completions); // Recursively find completions
    }
}
// Overloaded assignment operator to copy a trie
Trie& Trie::operator=(const Trie& other) {
    if (this == &other) {
        return *this; // Self-assignment check
    }
    // Destroy current trie
    destroyTrie(root);
    // Copy other trie
    root = new TrieNode();
    copyTrie(other.root, root);
    return *this;
}
// Helper function to copy a trie recursively
void Trie::copyTrie(TrieNode* source, TrieNode*& dest) {
    if (!source) {
        dest = nullptr;
        return;
    }
    dest = new TrieNode();
    dest->isEndOfWord = source->isEndOfWord;
    for (int i = 0; i < 26; ++i) {
        copyTrie(source->children[i], dest->children[i]);
    }
}
