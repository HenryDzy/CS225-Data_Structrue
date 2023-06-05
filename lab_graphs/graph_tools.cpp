/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include <limits.h>
#include "graph_tools.h"
#include <iostream>
#include <stack>

using std::queue;
using std::vector;
using std::sort;

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph &graph)
{
    int minWeight = INT_MAX;   // current minimum weight
    Vertex source, dest; // the vertexs at two sides of min-weight edge
    queue<Vertex> q;     // stack used for BFS
    vector<Vertex> adjacent;
    Vertex curr = graph.getStartingVertex();
    q.push(curr);

    // Initialize edge's label as "UNEXPLORED"
    vector<Edge> Edge_list = graph.getEdges();
    for (size_t i = 0; i < Edge_list.size(); i++)
    {
        graph.setEdgeLabel(Edge_list[i].source, Edge_list[i].dest, "UNEXPLORED");
    }
    // Initialize vertices as "UNEXPLORED"
    vector<Vertex> Vertex_list = graph.getVertices();
    for (size_t i = 0; i < Vertex_list.size(); i++)
    {
        graph.setVertexLabel(Vertex_list[i], "UNEXPLORED");
    }
    graph.setVertexLabel(curr, "VISITED");

    while (!q.empty())
    {
        curr = q.front();
        q.pop();
        adjacent = graph.getAdjacent(curr);

        for (size_t i = 0; i < adjacent.size(); i++)
        {
            Edge curr_edge = graph.getEdge(curr, adjacent[i]);

            if (graph.getVertexLabel(adjacent[i]) == "UNEXPLORED")
            {
                if (curr_edge.weight < minWeight)
                {
                    minWeight = curr_edge.weight;
                    source = curr_edge.source;
                    dest = curr_edge.dest;
                }
                graph.setVertexLabel(adjacent[i], "VISITED");
                graph.setEdgeLabel(curr, adjacent[i], "DISCOVERY");
                q.push(adjacent[i]);
            }
            else if (curr_edge.label == "UNEXPLORED"){
                if (curr_edge.weight < minWeight)
                {
                    minWeight = curr_edge.weight;
                    source = curr_edge.source;
                    dest = curr_edge.dest;
                }
                graph.setEdgeLabel(curr, adjacent[i], "CROSS");
            }
        }
    }
    graph.setEdgeLabel(source, dest, "MIN");
    return minWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph &graph, Vertex start, Vertex end)
{
    if(start == end){
        return 0;
    }
    map<Vertex, Vertex> parents;
    map<Vertex, int> distances;
    vector<Vertex> vertices = graph.getVertices();
    // vector<Edge> edges = graph.getEdges();
    // initialization
    for(size_t i=0; i<vertices.size(); i++){
        pair<Vertex, Vertex> par_pair(vertices[i], NULL);
        parents.insert(par_pair);
        pair<Vertex, int> dis_pair(vertices[i], INT_MAX);
        distances.insert(dis_pair);
        graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }
    // for(size_t i=0; i<edges.size(); i++){
    //     graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    // }
    Vertex curr = start; // get starting point
    vector<Vertex> adjacent;
    queue<Vertex> q; // queue used for traversal
    q.push(curr);
    graph.setVertexLabel(curr, "VISITED");
    distances[curr] = 0;
    
   while(!q.empty()){
        curr = q.front();
        q.pop();
        adjacent = graph.getAdjacent(curr);
        for(size_t i=0; i<adjacent.size(); i++){
            if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED"){
                graph.setVertexLabel(adjacent[i], "VISITED");
                distances[adjacent[i]] = distances[curr] + 1;
                parents[adjacent[i]] = curr;
                q.push(adjacent[i]);
            }
            else if(distances[adjacent[i]] > distances[curr] + 1){
                distances[adjacent[i]] = distances[curr] + 1;
                parents[adjacent[i]] = curr;
            }
        }
    }
    
    for(Vertex v = end; v != start; v = parents[v]){
        graph.setEdgeLabel(v, parents[v], "MINPATH");
    }
    return distances[end];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph &graph)
{
    vector<Edge> minEdges = graph.getEdges();
    sort(minEdges.begin(), minEdges.end());
    map<Vertex, int> map_vi;
    DisjointSets forest;
    vector<Vertex> vertices = graph.getVertices();
    Edge e;
    Vertex s, d;
    forest.addelements(vertices.size());

    for(size_t i=0; i<vertices.size(); i++){
        map_vi[vertices[i]] = i;
    }
    
    for(size_t i=0; i<minEdges.size(); i++){
        e = minEdges[i];
        s = e.source;
        d = e.dest;

        if (forest.find(map_vi[s]) != forest.find(map_vi[d])) {
            forest.setunion(map_vi[s], map_vi[d]);
            graph.setEdgeLabel(s, d, "MST");
        }
    }

    return;
}