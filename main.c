#include "stdio.h"
#include "stdlib.h"
#include "graph.h"

int numOutOfRange = 0;
//Đọc dữ liệu từ file vào đồ thị
void importDataFromFile(Graph *_graph, char *path) {
    Graph graph = *_graph;
    FILE *fPtr,*fPtrPairs; //fPtr chứa đồ thị, fPtrPairs chứa các cặp đỉnh không hợp lệ
    char buffer[100];
    char *pathPairs = "..\\pairs.txt";
    // Mở file đầu vào để đọc
    if ((fPtr = fopen(path, "r")) == NULL) {
        printf("Khong mo duoc file.\n");
        return;
    }

    // Mở file output để ghi nối tiếp (append)
    if ((fPtrPairs = fopen(pathPairs, "a")) == NULL) {
        printf("Khong mo duoc file.\n");
        
        return;
    }

    // 4 dòng đầu tiên
    int i;
    for ( i = 0; i < 4; i++) {
        fgets(buffer, sizeof(buffer), fPtr);//Đọc fPrt vào buffer
        if (!graph->_numVertex) {
            sscanf(buffer, "# Nodes: %d Edges: %d", &graph->_numVertex, &graph->_numUniqueEdge);
        }
    }

    graph->_numUniqueEdge /= 2;
    allocateMemoryToHashTable(&graph);
    resetHashTableToNull(&graph);

    int source, destination;
    while (fgets(buffer, sizeof(buffer), fPtr)) {
        sscanf(buffer, "%d  %d", &source, &destination);

        if (source < graph->_numVertex) addEdgeToGraph(&graph, source, destination, source);
        else {
            numOutOfRange += 1;
            fprintf(fPtrPairs, "%d  %d\n", source, destination);
        }
    }

    //Trong C nếu buffer không đầy dữ liệu sẽ được luuw vào đệm đến khi kết thúc
    //->fflush đảm bảo dữ liệu từ fPtrPairs được ghi vào index.txt
    //Đảm bảo mọi dữ liệu đã ghi vào file pairs.txt trước khi đóng file.
    fflush(fPtrPairs);
    printf("Thanh cong tai data len file.\n");
    fclose(fPtr);
    fclose(fPtrPairs);
}

//Tìm index của các đỉnh không hợp lệ/chưa được duyệt trong đồ thị
int *getNullIndex(Graph graph) {
    int track = 0;
    int *nullIndex = (int *) malloc(numOutOfRange * sizeof(int));

    for (int i = 0; i < graph->_numVertex; i++) {
        if (graph->_hash[i] == NULL) {
            nullIndex[track] = i;
            track += 1;
        }
    }

    return nullIndex;
}
//Nhập dữ liệu từ pairs và index vào đồ thị
void importOutOfRangeData(Graph *graph, int *nullIndex) {
    char *pathPairs = "..\\pairs.txt";
    FILE *fPtr;
    if ((fPtr = fopen(pathPairs, "r")) == NULL) {
        printf("Khong mo duoc file.\n");

        return;
    }

    char *pathOORIndex = "..\\index.txt";
    FILE *fPtrIndex;
    if ((fPtrIndex = fopen(pathOORIndex, "w")) == NULL) {
        printf("Khong mo duoc file.\n");

        return;
    }
    if ((fPtrIndex = fopen(pathOORIndex, "a")) == NULL) {
        printf("Khong mo duoc file.\n");

        return;
    }

    int track = 0;
    int source, destination;
    Graph tmp = *graph;
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), fPtr)) {
        sscanf(buffer, "%d  %d", &source, &destination);

        if (tmp->_hash[nullIndex[track]] == NULL) {
            tmp->_hash[nullIndex[track]] = initNode(source);
            addNode(&tmp->_hash[nullIndex[track]], destination);
            fprintf(fPtrIndex, "%d  %d\n", nullIndex[track], source);
            continue;
        }

        if (tmp->_hash[nullIndex[track]]->_vertex == source) {
            addNode(&tmp->_hash[nullIndex[track]], destination);
            continue;
        }

        track += 1;// đỉnh tại nullIndex[track] != source
        tmp->_hash[nullIndex[track]] = initNode(source);
        addNode(&tmp->_hash[nullIndex[track]], destination);
        fprintf(fPtrIndex, "%d  %d\n", nullIndex[track], source);
    }

    fflush(fPtrIndex);
    printf("Tai thanh cong cac node ngoai pham vi tu file.\n");
    fclose(fPtr);
    fclose(fPtrIndex);
}
//Kiểm tra xem đỉnh có hợp lệ hay không
int isValidVertex(Graph *graph, int vertex) {
    Graph tmp = *graph;
    for (int i= 0; i < tmp->_numVertex; i++) {
        if (tmp->_hash[i]->_vertex == vertex) return 1;
        //Kiểm tra có đỉnh nào trong hash có _vertex == vertex không
    }

    return 0;
}


void print_state_menu() {
    printf("\nChon mot bo du lieu:\n1. CA\n2. PA\n3. TX\n0. Exit\n");
}

void print_option_menu() {
    printf("\nChon mot thao tac:\n1. DFS\n2. BFS\n3. Kiem tra Vertex Cover\n4. Duyet do thi\n5. Dem thanh phan lien thong\n0. Back\n");
}

int main() {
    //char *KY = "..\\dataset\\roadNet-KY.txt\\roadNet-KY.txt";       // Simple graph data for testing
    char *CA = "..\\dataset\\roadNet-CA.txt\\roadNet-CA.txt";
    char *PA = "..\\dataset\\roadNet-PA.txt\\roadNet-PA.txt";
    char *TX = "..\\dataset\\roadNet-TX.txt\\roadNet-TX.txt";

    
    int option, isBreak = 0;
    while (1) {
        Graph g = initVanillaGraph();
        char *test_path;

        print_state_menu();
        printf("Nhap lua chon: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                importDataFromFile(&g, CA);
                test_path = CA_test;
                break;
            case 2:
                importDataFromFile(&g, PA);
                test_path = PA_test;
                break;
            case 3:
                importDataFromFile(&g, TX);
                test_path = TX_test;
                break;
            case 0:
                isBreak = 1;
                break;
            default:
                printf("Tuy chon khong hop le.\n");
        }

        if (isBreak) break;


        // Thao tác
        while(1) {
            print_option_menu();
            printf("Nhap lua chon: ");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    printf("DFS\n");
                    printf("Nhap dinh bat dau :");
                    scanf("%d", &option);

                    if (isValidVertex(&g, option)) DFS(&g, option);
                    else printf("Tuy chon khong hop le.");

                    break;
                case 2:
                    printf("BFS\n");
                    printf("Nhap dinh bat dau : ");
                    scanf("%d", &option);

                    if (isValidVertex(&g, option)) BFS(&g, option);
                    else printf("Tuy chon khong hop le.");

                    break;
                case 3:
                    printf("Checking Vertex Cover\n");
                    testVertexCover(&g, test_path);
                    break;
                case 4:
                    printf("Duyet do thi\n");
                    printf("Nhap dinh da di qua: ");
                    scanf("%d", &option);

                    if (option == 0) option = g->_numVertex;
                    traverseGraph(g, option);

                    break;
                case 5:
                    printf("Dem thanh phan lien thong\n");
                    countConnectedComponents(&g);
                    break;
                case 0:
                    isBreak = 1;
                    break;
                default:
                    printf("Tuy chon khong hop le.\n");
            }
            if (isBreak) break;
        }

        isBreak = 0;

        freeGraph(g);
       // free(nullIndex);
    }

    return 0;
}
