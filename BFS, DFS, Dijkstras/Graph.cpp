#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.hpp"
#include "GraphNode.hpp"
#include <queue>

// TODO: Implement all other methods defined in Graph.hpp here

template <typename T>
Graph<T>::Graph(const std::vector<std::pair<T,T>> &edges){
    for (const auto&edge : edges){
        addVertex(edge.first);
        addVertex(edge.second);
        addEdge(edge.first, edge.second);
    }
}

template <typename T>
Graph<T>::Graph(const std::map<T, std::set<T>> &adjList){
    for (const auto &entry : adjList) {
        addVertex(entry.first);
        for (const auto &neighbor : entry.second) {
            addVertex(neighbor);
            addEdge(entry.first, neighbor);
        }
    }
}

template <typename T>
int Graph<T>::size() const{
    return _adjList.size();
}

template <typename T>
void Graph<T>::addVertex(T vertex){
    if(_adjList.find(vertex) == _adjList.end()){
        _adjList[vertex] = std::set<T>();
    }

    if (_vertices.find(vertex) == _vertices.end()){
        _vertices[vertex] = GraphNode<T>(vertex);
    }
}

template <typename T>
void Graph<T>::addEdge(T from, T to){
    addVertex(from);
    addVertex(to);
    _adjList[from].insert(to);
}

template <typename T>
bool Graph<T>::hasEdge(T from, T to) const{
    auto fromcurr = _adjList.find(from);
    if (fromcurr != _adjList.end()){

        auto tocurr = fromcurr->second.find(to);
        if (tocurr != fromcurr->second.end()) {

            return true;
        }
    }
    return false;
}

template <typename T>
std::optional<std::set<T>> Graph<T>::getNeighbors(T vertex) const{
    auto it = _adjList.find(vertex);

    if (it != _adjList.end()) {
        return it->second;
    }
    else{
        return std::nullopt;
    }
}

template <typename T>
std::vector<T> Graph<T>::BFS(T start){
    //Each node colored white and distance set to -1
    for(auto& vertex: _vertices){
        vertex.second.color = White;
        vertex.second.distance = -1;
        vertex.second.predecessor = std::nullopt;
    }
    //at the root/ start, color it gray;
    _vertices[start].color = Gray;
    _vertices[start].distance = 0;
    _vertices[start].predecessor = std::nullopt;

    std::queue<T> q;
    q.push(start);

    std::vector<T> result;

    while (!q.empty()){
        T u = q.front();
        q.pop();
        result.push_back(u);

        for (const T& v : _adjList[u]){
            if(_vertices[v].color == White){
                _vertices[v].color = Gray;
                _vertices[v].distance = _vertices[u].distance + 1;
                _vertices[v].predecessor = u;
                q.push(v);
            }
        }

        _vertices[u].color = Black;
    }

    return result;

}

template <typename T>
int Graph<T>::shortestPath(T start, T end){
    BFS(start);
    
    //check if the a path exists
    if(_vertices[end].distance == -1){
        return -1;
    }

    std::vector<T> path;
    T currVertex = end;
    while (currVertex != start){
        path.push_back(currVertex);
        currVertex = _vertices[currVertex].predecessor.value();
    }

    path.push_back(start);

    std::reverse(path.begin(), path.end());

    return _vertices[end].distance;

}

/*
//see book:
template <typename T>
std::list<T> Graph<T>::DFS(){
    /*
    //store result
    std::list<T> result;

    //color all vertices white
    for(auto& vertex : _vertices){
        vertex.second.color = White;
        vertex.second.predecessor = std::nullopt;
    }
    int time = 0;

    loop through each and check if white
    for(auto& vertex : _vertices){
        if (vertex[vertex].color == White){

            T u = pair.first;

            //DFS visit:
            time = time + 1;
            vertex.second.color = Gray;
            for(const T& v : _adjList[u]){
                if (_vertices[v].color == White){
                    _vertices[v].preddecessor = vertices
                }
            }
        }
    }
}
*/
template <typename T>
std::list<T> Graph<T>::DFS() {
    std::list<T> result;
    int time = 0;      
    
      
    // Nested function for DFS visit
    std::function<void(const T &)> DFS_visit = [&](const T &u) {
        // Mark the current vertex as visited
        _vertices[u].color = Gray;
        _vertices[u].discovery_time = ++time;

        // Visit all neighbors of the current vertex
        for (const T &v : _adjList[u]) {
            if (_vertices[v].color == White) {
                // If the neighbor is not visited, recursively visit it
                _vertices[v].predecessor = u;
                DFS_visit(v);
            }
        }

        // Mark the current vertex as fully visited (Black)
        _vertices[u].color = Black;
        _vertices[u].finish_time = ++time;

        // Add the current vertex to the result list in reverse order
        result.push_front(u);
    };




    // Mark all vertices as not visited
    for (auto& pair : _vertices) {
        pair.second.color = White;
        pair.second.predecessor = std::nullopt;
    }

    for (const auto& pair : _vertices) {
        if (pair.second.color == White) {
            DFS_visit(pair.first);
        }
    }

    return result;
}
#endif // GRAPH_CPP
