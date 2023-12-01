#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<chrono>
usingnamespacestd;
usingnamespacestd::chrono;

structQueue{
int front, rear, size;
unsignedcapacity;
int* array;
};

Queue* createQueue(unsignedcapacity) {
    Queue* queue = newQueue();
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = newint[(queue->capacity * sizeof(int))];
    returnqueue;
}

intisFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

intisEmpty(Queue* queue) {
    return (queue->size == 0);
}

voidenqueue(Queue* queue, intitem) {
    if (isFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

intdequeue(Queue* queue) {
    if (isEmpty(queue)) return-1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    returnitem;
}

vector<vector<int>>generateRandomGraph(intn) {
    vector<vector<int>>graph(n, vector<int>(n, 0));
    srand(time(0));

    for (inti = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int random = rand() % 2;
            graph[i][j] = random;
            graph[j][i] = random;
        }
    }

    returngraph;
}

voidprintMatrix(vector<vector<int>>& matrix) {
    cout << "Матрицасмежности:" << endl;
    for (inti = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

voidBFSUsingMatrix(vector<vector<int>>& graph, vector<bool>& visited, intstartVertex) {
    queue<int>q;
    q.push(startVertex);
    visited[startVertex] = true;

    while (!q.empty()) {
        intcurrentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";

        for (inti = 0; i < graph[currentVertex].size(); i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

voidBFSUsingMatrixWithTime(vector<vector<int>>& graph, vector<bool>& visited, intstartVertex) {
    auto start = high_resolution_clock::now();
    BFSUsingMatrix(graph, visited, startVertex);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nВремяобходачерезматрицусмежности (стандартная queue): " << duration.count() << " микросекунд" << endl;
}

voidBFSUsingCustomQueue(vector<vector<int>>& graph, vector<bool>& visited, intstartVertex) {
    int n = graph.size();
    Queue* q = createQueue(n);
    enqueue(q, startVertex);
    visited[startVertex] = true;

    while (!isEmpty(q)) {
        intcurrentVertex = dequeue(q);
        cout << currentVertex << " ";

        for (inti = 0; i < n; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                enqueue(q, i);
                visited[i] = true;
            }
        }
    }
}

voidBFSUsingCustomQueueWithTime(vector<vector<int>>& graph, vector<bool>& visited, intstartVertex) {
    auto start = high_resolution_clock::now();
    BFSUsingCustomQueue(graph, visited, startVertex);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nВремя обхода через матрицу смежности (структура данных): " << duration.count() << " микросекунд" << endl;
}

voidprintAdjacencyList(vector<vector<int>>& graph) {
    cout << "Списоксмежности:" << endl;
    for (inti = 0; i < graph.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}


voidBFSUsingLists(vector<vector<int>>& graph, vector<bool>& visited, intstartVertex) {
    queue<int>q;
    q.push(startVertex);
    visited[startVertex] = true;


    while (!q.empty()) {
        intcurrentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";


        for (inti = 0; i < graph[currentVertex].size(); i++) {
            intadjacentVertex = graph[currentVertex][i];
            if (!visited[adjacentVertex]) {
                q.push(adjacentVertex);
                visited[adjacentVertex] = true;
            }
        }
    }
}


intmain() {
    setlocale(LC_ALL, "Russian");
    intn;
    cout << "Введите количество вершин : ";
    cin >> n;


    vector<vector<int>>adjacencyMatrix = generateRandomGraph(n);
    printMatrix(adjacencyMatrix);

    vector<bool>visited(n, false);
    intstartVertex;
    cout << "Введите вершину, с которой начать обход: ";
    cin >> startVertex;

    if (startVertex < 0 || startVertex >= n) {
        cout << "Некорректная вершина. Пожалуйста, введите вершину от 0 до " << n - 1 << "." << endl;
        return 0;
    }

    cout << "Обход в ширину через матрицу смежности: ";
    BFSUsingMatrixWithTime(adjacencyMatrix, visited, startVertex);

    vector<vector<int>>adjacencyList(n);
    for (inti = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    visited.assign(n, false);
    cout << "\nОбходвширинучерезкастомнуюочередь: ";
    BFSUsingCustomQueueWithTime(adjacencyMatrix, visited, startVertex);
    cout << endl;


    printAdjacencyList(adjacencyList);


    visited.assign(n, false);
    cout << "Обход в ширину через список смежности: ";
    BFSUsingLists(adjacencyList, visited, startVertex);
    cout << endl;


    return 0;
}
