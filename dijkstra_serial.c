#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/* Number of vertices in the graph. */
#define N 256
/* Define the source vertex. */
#define SOURCE 1
#define MAXINT 9999999

/* Function that implements Dijkstra's single source shortest path algorithm
   for a graph represented by adjacency matrix, and use source vertex as input. */
void dijkstra(int graph[N][N], int source);

int main(int argc, char *argv[]) {
    int weight[N][N];
    int i, j;
    char fn[255];
    FILE *fp;
    double time_start, time_end;
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.00;

    /* Open input file, read adjacency matrix */
    strcpy(fn, "input256.txt");
    fp = fopen(fn, "r");
    if ((fp = fopen(fn, "r")) == NULL) {
        printf("Can't open the input file: %s\n\n", fn);
        exit(1);
    }

    // printf("\nThe adjacency matrix: \n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            fscanf(fp, "%d", &weight[i][j]);
            // if (weight[i][j] == 9999999) printf("%4s", "INT");
            // else printf("%4d", weight[i][j]);
        }
        // printf("\n");
    }

    dijkstra(weight, SOURCE);
    printf("\n");
    printf("Nodes: %d ", N);

    gettimeofday(&tv, &tz);
    time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.00;
    printf("time cost is %1f\n", time_end - time_start);
    printf("\n");

    return 0;
}

void dijkstra(int graph[N][N], int source) {
    /* This array holds the shortest distance from source to other vertices. */
    int distance[N];
    /* This value sets to 1 if vertices are finished to compute. */
    int visited[N];
    int i, j, count, nextNode, minDistance;

    /* Initialize all vertices' distance and status. */
    for (i = 0; i < N; i++) {
        distance[i] = graph[source][i];
        visited[i] = 0;
    }
    visited[source] = 1;
    count = 1;

    /* Find shortest path for all vertices. */
    while (count < N) {
        minDistance = MAXINT;

        /* Pick the minimum distance vertex from the set of vertices that
           is not processed. */
        for (i = 0; i < N; i++) {
            if (distance[i] < minDistance && !visited[i]) {
                minDistance = distance[i];
                nextNode = i;
            }
        }

        /* Mark this vertex as processed. */
        visited[nextNode] = 1;
        count++;

        /* Update the dist value of the picked vertex. */
        for (i = 0; i < N; i++) {
            if (!visited[i] && minDistance + graph[nextNode][i] < distance[i]) {
                distance[i] = minDistance + graph[nextNode][i];
            }
        }
    }

    /* Print the distance values. */
    // printf("\nThe distance vector is\n");
    // for (i = 0; i < N; i++) {
    //     printf("%d ", distance[i]);
    // }
    // printf("\n");
}

