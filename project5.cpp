#include "Trie.h"
#include <iostream>
#include <fstream>
// Function to load words from a file into the trie
void loadDictionary(Trie& trie, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        trie.insert(word);
    }

    file.close();
}
// Function to display completions for a given prefix
void displayCompletions(Trie& trie, const std::string& prefix) {
    std::vector<std::string> completions = trie.complete(prefix);
    std::cout << "Completions for prefix '" << prefix << "':" << std::endl;
    for (const std::string& word : completions) {
        std::cout << word << std::endl;
    }
}
// Main function
int main() {
    Trie trie;
// Load dictionary into the trie
    loadDictionary(trie, "wordlist_windows.txt");

    std::string prefix;
    while (true) {
        std::cout << "Please enter a word prefix (or press enter to exit): ";
        std::getline(std::cin, prefix);

        if (prefix.empty()) {
            break;
        }

        int count = trie.completeCount(prefix);
        std::cout << "There are " << count << " completions for the prefix '" << prefix << "'. Show completions? ";
        std::string response;
        std::getline(std::cin, response);
        if (response == "Yes" || response == "yes" || response == "y" || response == "Y") {
            displayCompletions(trie, prefix);
        }
    }

    return 0;
}
