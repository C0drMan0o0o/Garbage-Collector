#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "garbageCollectedObject.hpp"

using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;
using std::flush;
using std::remove;

class MyGraph {
private:
    vector<garbageCollectedObject*> objects;
    unordered_map<garbageCollectedObject*, vector<garbageCollectedObject*>> adjList;
    unordered_map<garbageCollectedObject*, char> charMap;
    int charNum = (int) 'A';
public:
    void addEdge(garbageCollectedObject*, garbageCollectedObject*);
    void removeEdge(garbageCollectedObject*, garbageCollectedObject*);
    void addObject(garbageCollectedObject*);
    vector<garbageCollectedObject*> getRootNodes() const;
    void removeObject(garbageCollectedObject*);
    void removeObject(garbageCollectedObject*, size_t);
    unordered_map<garbageCollectedObject*, vector<garbageCollectedObject*>> getAdjList() const;
    vector<garbageCollectedObject*> getObjects() const;
    void printConnections();
    void printRoots();
    void printGraph();
    char getChar(garbageCollectedObject*);
    void findConnectedObjects(garbageCollectedObject*, vector<garbageCollectedObject*>&);
    void removeConnectedObjects(garbageCollectedObject*);
    void dfs(garbageCollectedObject*, vector<garbageCollectedObject*>&, vector<garbageCollectedObject*>&);
};

