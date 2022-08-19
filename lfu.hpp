#ifndef LFU_HPP
#define LFU_HPP
#include <unordered_map>
using namespace std;

class List;

//Node representing key - value pair
class Node {
public:
    int key;
    int value;
    class Node *prev;
    class Node *next;
    List *list;
    int freq;
    Node (int k, int v) : key(k), value(v), freq(0), prev(nullptr), next(nullptr) {}
    Node () : key(0), value(0), freq(0), prev(nullptr), next(nullptr) {}
};

//Doubly Linked List
class List {
public:
    Node *head;
    Node *tail;
    int len;
    List() {
        head = new Node();
        tail = new Node();
        len = 0;
        head->next = tail;
        tail->prev = head;
    }
    void Add (Node* node) {
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
        len++;
    }
    void Del (Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        len--;
    }
    void Pop () {
        if (len)
            Del(tail->prev);
    }
    void Update (Node* node) {
        Del(node);
        Add(node);
    }
    Node *Last() {
        return tail->prev;
    }
    int Size () {
        return len;
    }
};

class LFUCache {
    unordered_map<int, Node*> mp;
    map<int, List*> cache;
    int cap;
    int total;

    //Function to increase frequence of Node
    void FreqIncrease (Node *node) {
        List *preList = node->list;
        int freq = node->freq;
        preList->Del(node);
        if (!preList->Size()) {
            cache.erase(freq);
        }
        freq++;
        if (!cache.count(freq))
            cache[freq] = new List();
        List *curList = cache[freq];
        node->freq = freq;
        node->list = curList;
        cache[freq]->Add(node);
    }

public:
    //Constructor
    LFUCache(int capacity) {
        cap = capacity;
        total = 0;
    }

    //Function to get value of the key if it exists in cache memory
    int get(int key) {
        if (!cap)
            return -1;

        if (!mp.count(key))
            return -1;
        Node *node = mp[key];
        FreqIncrease(node);
        return node->value;
    }
    
    //Function to add key value pair to the cache memory
    void add(int key, int value) {
        if (!cap)
            return;

        if (mp.count(key)) {
            Node *node = mp[key];
            node->value = value;
            FreqIncrease(node);
            return;
        }

        if (cap == total) {
            List *list = cache.begin()->second;
            int freq = cache.begin()->first;
            Node *last = list->Last();
            mp.erase(last->key);
            list->Pop();
            if (!list->Size()) {
                cache.erase(freq);
            }
            total--;
        }
        if (!cache.count(1))
            cache[1] = new List();

        Node *node = new Node(key, value);
        node->freq = 1;        
        node->list = cache[1];
        mp[key] = node;
        node->list->Add(node);

        total++;
    }
};
#endif