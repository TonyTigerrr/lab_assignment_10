#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Define the trie node structure
typedef struct Trie {
    int flag;
    struct Trie *children[ALPHABET_SIZE];
} Trie;

// Initialize a new trie node
struct Trie *newTrieNode() {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->flag = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

// Insert a new word into the trie
void insert(struct Trie **ppTrie, char *word) {
    // Start from the root of the trie
    struct Trie *node = *ppTrie;
    if (node == NULL) {
        *ppTrie = newTrieNode();
        node = *ppTrie;
    }
    // Traverse the trie for each character in the word
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL)
            node->children[index] = newTrieNode();
        node = node->children[index];
    }
    // Mark the end of the word and increase the count
    node->flag++;
}

// Count the number of occurrences of a word in the trie
int numberOfOccurances(struct Trie *pTrie, char *word) {
    // Start from the root of the trie
    struct Trie *node = pTrie;
    if (node == NULL)
        return 0;
    // Traverse the trie for each character in the word
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL)
            return 0;
        node = node->children[index];
    }
    // Return the count at the end of the word
    return node->flag;
}

// Deallocate the trie nodes
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            deallocateTrie(pTrie->children[i]);
        free(pTrie);
    }
    return NULL;
}

int main(void) {
    // Initialize the trie
    struct Trie *trie = NULL;

    // Read the number of words in the dictionary
    int n;
    scanf("%d", &n);

    // Parse each line and insert the word into the trie
    char word[100];
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insert(&trie, word);
    }

    // Test the trie with some sample words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
        printf("%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));

    // Deallocate the trie and check for errors
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}