#include <stdio.h>

#define V 8

char *airports[V] = {
    "Mumbai", "Delhi", "Bengaluru", "Hyderabad",
    "Kolkata", "Chennai", "Pune", "Ahmedabad"
};

int graph[V][V] = {0};
int visited[V];

// Add a flight connection (undirected graph)
void addFlight(int src, int dest) {
    graph[src][dest] = 1;
    graph[dest][src] = 1;
}

// Display airport connections
void displayFlights() {
    printf("\n--- AIRPORT CONNECTIVITY ---\n");

    for (int i = 0; i < V; i++) {
        printf("%s -> ", airports[i]);

        for (int j = 0; j < V; j++) {
            if (graph[i][j])
                printf("%s  ", airports[j]);
        }

        printf("\n");
    }
}

// Breadth-First Search
void BFS(int start, int destination) {
    int queue[V];
    int parent[V];
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];

        if (current == destination)
            break;

        for (int i = 0; i < V; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                parent[i] = current;
                queue[rear++] = i;
            }
        }
    }

    if (!visited[destination]) {
        printf("\nNo route available between %s and %s.\n",
               airports[start], airports[destination]);
        return;
    }

    int path[V], count = 0;
    int current = destination;

    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    printf("\nShortest route: ");

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", airports[path[i]]);

        if (i > 0)
            printf(" -> ");
    }

    printf("\nNumber of flight connections: %d\n", count - 1);
}

// Depth-First Search
void DFS(int current) {
    visited[current] = 1;
    printf("%s ", airports[current]);

    for (int i = 0; i < V; i++) {
        if (graph[current][i] && !visited[i])
            DFS(i);
    }
}

int main() {
    int choice, src, dest;

    // Sample airport network
    addFlight(0, 1); // Mumbai - Delhi
    addFlight(0, 2); // Mumbai - Bengaluru
    addFlight(0, 6); // Mumbai - Pune
    addFlight(1, 4); // Delhi - Kolkata
    addFlight(1, 7); // Delhi - Ahmedabad
    addFlight(2, 3); // Bengaluru - Hyderabad
    addFlight(2, 5); // Bengaluru - Chennai
    addFlight(3, 4); // Hyderabad - Kolkata
    addFlight(3, 5); // Hyderabad - Chennai
    addFlight(6, 7); // Pune - Ahmedabad

    do {
        printf("\n========== AIRROUTE ==========\n");
        printf("1. Display Airport Connections\n");
        printf("2. Find Shortest Route (BFS)\n");
        printf("3. Explore Network (DFS)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayFlights();
                break;

            case 2:
                printf("\nAirport indices:\n");
                for (int i = 0; i < V; i++)
                    printf("%d. %s\n", i, airports[i]);

                printf("Enter source and destination indices: ");
                scanf("%d %d", &src, &dest);

                if (src < 0 || src >= V || dest < 0 || dest >= V) {
                    printf("Invalid airport index!\n");
                    break;
                }

                BFS(src, dest);
                break;

            case 3:
                printf("\nDFS traversal starting from Mumbai:\n");

                for (int i = 0; i < V; i++)
                    visited[i] = 0;

                DFS(0);
                printf("\n");
                break;

            case 4:
                printf("\nExiting AirRoute. Thank you!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
