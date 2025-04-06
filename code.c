// void DFSCount(Graph *graph, int source, int *numVertices, int *numEdges) {
//     Graph tmp = *graph;
//     visited = resetArray(tmp->_numVertex);
//     visited[source] = 1;//Đỉnh source(nguồn) đã được thăm
//     (*numVertices)++;

//     node_t adjList = tmp->_hash[source];
//     while (adjList != NULL) {
//         (*numEdges)++;
//         if (visited[adjList->_vertex] == 0) {//Nếu đỉnh chưa được thăm
//             DFSCount(graph, adjList->_vertex, numVertices, numEdges);
//         }
//         adjList = adjList->_next;
//     }
    
    
//     *numEdges /= 2;
// }

// //Đếm số thanh phần liên thông trong đồ thị
// void countConnectedComponents(Graph *graph) {
//     Graph tmp = *graph;
//     visited = resetArray(tmp->_numVertex);  // Mảng visited để theo dõi các đỉnh đã thăm.
//     int numComponents = 0;

//     for (int i = 0; i < tmp->_numVertex; i++) {
//         if (visited[i] == 0) {  // Nếu đỉnh chưa được thăm, bắt đầu một DFS mới.
//             numComponents++;  // Tăng số thành phần liên thông.
//             int numVertices = 0;
//             int numEdges = 0;
            
//             // Thực hiện DFS hoặc BFS để tìm số đỉnh và số cạnh trong thành phần liên thông.
//             DFSCount(graph, i, &numVertices, &numEdges);
            
//             printf("Component %d: Number of vertices = %d, Number of edges = %d\n", 
//                    numComponents, numVertices, numEdges);
//         }
//     }

//     printf("Total connected components: %d\n", numComponents);
// }