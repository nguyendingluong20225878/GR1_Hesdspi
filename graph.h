#ifndef GR1_GRAPH_H
#define GR1_GRAPH_H

#include "node.h"

typedef struct Graph {
    int _numVertex;       // Số đỉnh trong đồ thị
    int _numUniqueEdge;   // Số cạnh trong đồ thị
    node_t *_hash;       // Bảng băm chứa danh sách kề của các đỉnh
} *Graph, Graph_s;

// Khởi tạo đồ thị rỗng
Graph initVanillaGraph();

// Cấp phát bộ nhớ cho bảng băm
void allocateMemoryToHashTable(Graph *graph);

// Đặt bảng băm về NULL
void resetHashTableToNull(Graph *graph);

// Thêm cạnh vào đồ thị
void addEdgeToGraph(Graph *graph, int source, int destination, int position);

// Duyệt đồ thị bằng DFS
void DFS(Graph *graph, int source);

// Duyệt đồ thị bằng BFS
void BFS(Graph *graph, int source);

// BFS đếm số đỉnh, số cạnh trong một thành phần liên thông
void BFSComponent(Graph *graph, int source, int *componentVertexCount, int *componentEdgeCount);

//  DFSCount  đếm số đỉnh, số cạnh trong một thành phần liên thông
void DFSComponent(Graph *graph, int source, int *numVertices, int *numEdges);


// Đếm số thành phần liên thông và liệt kê số đỉnh, số cạnh của mỗi thành phần
void countConnectedComponents(Graph *graph);

// Trả về chỉ số của đỉnh nếu nằm ngoài phạm vi bảng băm
int getOORIndex(int source);

// Duyệt toàn bộ đồ thị
void traverseGraph(Graph graph, int maximum);

// Giải phóng bộ nhớ của đồ thị
void freeGraph(Graph graph);

void importDataFromFile(Graph *g, char *filename);


#endif // GR1_GRAPH_H
