#include "MyGraph.hpp"

#include "GC.hpp"

void MyGraph::addObject(garbageCollectedObject* object) {
//     Check if the object already exists in the graph
    if (adjList.find(object) != adjList.end()) {
        return; // Object already exists, no need to add it again
    }

    objects.emplace_back(object);
    adjList[object] = vector<garbageCollectedObject*>();
    
    if(charNum == (int) 'Z'){
        charNum = (int) 'a';
    }
    
    charMap[object] = (char) charNum;
    charNum++;
}

void MyGraph::addEdge(garbageCollectedObject* src, garbageCollectedObject* dest) {
    if (std::find(adjList[src].begin(), adjList[src].end(), dest) != adjList[src].end() ||
        std::find(adjList[dest].begin(), adjList[dest].end(), src) != adjList[dest].end()) {
//        std::cout << "Edge already exists." << std::endl;
    }
    else{
        adjList[src].emplace_back(dest);
    }
}

void MyGraph::removeEdge(garbageCollectedObject* src, garbageCollectedObject* dest) {
    adjList[src].erase(remove(adjList[src].begin(), adjList[src].end(), dest), adjList[src].end());
    adjList[dest].erase(remove(adjList[dest].begin(), adjList[dest].end(), src), adjList[dest].end());
    
    // Remove nodes from the root nodes vector if they are no longer connected
    if (adjList[src].empty()) {
        objects.erase(remove(objects.begin(), objects.end(), src), objects.end());
    }
    if (adjList[dest].empty()) {
        objects.erase(remove(objects.begin(), objects.end(), dest), objects.end());
    }
}

vector<garbageCollectedObject*> MyGraph::getRootNodes() const {
    std::vector<garbageCollectedObject*> rootNodes;

    for (const auto& entry : adjList) {
        garbageCollectedObject* vertex = entry.first;
        bool isNotRoot = vertex->createdWithinObject; // Check the createdWithinObject flag

        if (!isNotRoot) {
            rootNodes.emplace_back(vertex);
        }
    }
    return rootNodes;
}

void MyGraph::printConnections(){
    for(garbageCollectedObject* root : this->getRootNodes()){
        vector<garbageCollectedObject*> connectedObjs;
        this->findConnectedObjects(root, connectedObjs);
        cout << "\nNodes connected to root " << this->getChar(root) << ":" << endl;
        
        connectedObjs.erase(connectedObjs.begin()); // Remove the first object because the first node is the same as the current root node whose connected nodes you're trying to find
        
        for(garbageCollectedObject* connectedObj : connectedObjs){
            cout << this->getChar(connectedObj) << endl;
        }
    }
}

void MyGraph::printRoots(){
    cout << "\nRoots:" << endl;
    for(const auto& ptr : this->getRootNodes()){
        cout << this->getChar(ptr) << endl;
    }
}


void MyGraph::printGraph(){
    for (const auto& entry : adjList) {
        garbageCollectedObject* vertex = entry.first;

        // Check if the vertex is a root node or has neighbours
        if (!vertex->createdWithinObject || !entry.second.empty()) {
            cout << charMap[vertex] << " (" << vertex << ", isReachable = " << vertex->isReachable() << "): " << flush;

            // Print neighbours if they exist
            for (const auto& neighbour : entry.second) {
                cout << charMap[neighbour] << " (" << neighbour << ", isReachable = " << neighbour->isReachable() << ") " << flush;
            }

            cout << endl;
        }
    }
}

void MyGraph::removeObject(garbageCollectedObject* obj) {
    // Check if the object is a root node
    vector<garbageCollectedObject*> rootNodes = getRootNodes();
    if (std::find(rootNodes.begin(), rootNodes.end(), obj) != rootNodes.end()) {
        // If it's a root node, remove all objects connected to it
        removeConnectedObjects(obj);
    }

    // Remove the object from the vector
    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end()) {
        objects.erase(it);
    }

    // Remove the object from the adjacency list
    auto adjListIt = adjList.find(obj);
    if (adjListIt != adjList.end()) {
        // Iterate over the adjacency list of the object
        for (auto& adjObj : adjListIt->second) {
            // Remove the object from the adjacency list of its neighbours
            auto neighbourIt = adjList.find(adjObj);
            if (neighbourIt != adjList.end()) {
                neighbourIt->second.erase(
                    remove(neighbourIt->second.begin(), neighbourIt->second.end(), obj),
                    neighbourIt->second.end()
                );
            }
        }
        // Remove the object's entry from the adjacency list
        adjList.erase(adjListIt);
    }

    // Clear the objects vector if it becomes empty
    if (objects.empty()) {
        adjList.clear();
    }
    GC::getInstance()->getHeap()->deallocate((byte*) obj, obj->getSize());
}

void MyGraph::removeObject(garbageCollectedObject* obj, size_t size) {
    // Check if the object is a root node
    vector<garbageCollectedObject*> rootNodes = getRootNodes();
    if (std::find(rootNodes.begin(), rootNodes.end(), obj) != rootNodes.end()) {
        // If it's a root node, remove all objects connected to it
        removeConnectedObjects(obj);
    }

    // Remove the object from the vector
    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end()) {
        objects.erase(it);
    }

    // Remove the object from the adjacency list
    auto adjListIt = adjList.find(obj);
    if (adjListIt != adjList.end()) {
        // Iterate over the adjacency list of the object
        for (auto& adjObj : adjListIt->second) {
            // Remove the object from the adjacency list of its neighbours
            auto neighbourIt = adjList.find(adjObj);
            if (neighbourIt != adjList.end()) {
                neighbourIt->second.erase(
                    remove(neighbourIt->second.begin(), neighbourIt->second.end(), obj),
                    neighbourIt->second.end()
                );
            }
        }
        // Remove the object's entry from the adjacency list
        adjList.erase(adjListIt);
    }

    // Clear the objects vector if it becomes empty
    if (objects.empty()) {
        adjList.clear();
    }
    GC::getInstance()->getHeap()->deallocate((byte*) obj, size);
}

void MyGraph::removeConnectedObjects(garbageCollectedObject* root) {
    // Get all objects connected to the root using a depth-first search
    vector<garbageCollectedObject*> connectedObjects;
    findConnectedObjects(root, connectedObjects);

    // Remove each connected object
    for (garbageCollectedObject* obj : connectedObjects) {
        // Remove the object from the vector
        auto it = std::find(objects.begin(), objects.end(), obj);
        if (it != objects.end()) {
            objects.erase(it);
            GC::getInstance()->getHeap()->deallocate((byte*) obj, obj->getSize());
        }

        // Remove the object from the adjacency list
        auto adjListIt = adjList.find(obj);
        if (adjListIt != adjList.end()) {
            // Iterate over the adjacency list of the object
            for (auto& adjObj : adjListIt->second) {
                // Remove the object from the adjacency list of its neighbours
                auto neighbourIt = adjList.find(adjObj);
                if (neighbourIt != adjList.end()) {
                    neighbourIt->second.erase(
                        remove(neighbourIt->second.begin(), neighbourIt->second.end(), obj),
                        neighbourIt->second.end()
                    );
                }
            }
            // Remove the object's entry from the adjacency list
            adjList.erase(adjListIt);
        }
    }
}

void MyGraph::findConnectedObjects(garbageCollectedObject* root, vector<garbageCollectedObject*>& connectedObjects) {
    // Perform a depth-first search (DFS) to find all connected objects
    vector<garbageCollectedObject*> visited;
    dfs(root, visited, connectedObjects);
}

void MyGraph::dfs(garbageCollectedObject* current, vector<garbageCollectedObject*>& visited, vector<garbageCollectedObject*>& connectedObjects) {
    visited.push_back(current);
    connectedObjects.push_back(current);

    // Recursively visit neighbours
    for (garbageCollectedObject* neighbour : adjList[current]) {
        if (std::find(visited.begin(), visited.end(), neighbour) == visited.end()) {
            dfs(neighbour, visited, connectedObjects);
        }
    }
}

unordered_map<garbageCollectedObject*, vector<garbageCollectedObject*>> MyGraph::getAdjList() const {
    return adjList;
}

vector<garbageCollectedObject*> MyGraph::getObjects() const {
    return objects;
}

char MyGraph::getChar(garbageCollectedObject* ptr){
    return charMap[ptr];
}
