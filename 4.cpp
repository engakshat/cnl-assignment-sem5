#include <stdio.h>
#define MAX 10
#define INF 999
int main() {
int n, cost[MAX][MAX], dist[MAX][MAX];
int nextHop[MAX][MAX], i, j, k, changed;
int src, dest, path[MAX], count;
prin􀆞("Enter number of nodes: ");
scanf("%d", &n);
prin􀆞("Enter cost matrix (999 for no direct link):\n");
for (i = 0; i < n; i++) {
for (j = 0; j < n; j++) {
scanf("%d", &cost[i][j]);
dist[i][j] = cost[i][j];
if (i == j)
nextHop[i][j] = i;
else if (cost[i][j] != INF)
nextHop[i][j] = j;
else
nextHop[i][j] = -1;
}
}
prin􀆞("\nIni􀆟al Rou􀆟ng Tables:\n");
for (i = 0; i < n; i++) {
prin􀆞("\nRouter %c:\n", 'A' + i);
prin􀆞("Des􀆟na􀆟on\tCost\tNext Hop\n");
for (j = 0; j < n; j++) {
prin􀆞("%c\t\t", 'A' + j);
if (dist[i][j] == INF)
prin􀆞("INF\t");
else
prin􀆞("%d\t", dist[i][j]);
if (nextHop[i][j] == -1)
prin􀆞("-\n");
else
prin􀆞("%c\n", 'A' + nextHop[i][j]);
}
}
do {
changed = 0;
int newDist[MAX][MAX];
int newNext[MAX][MAX];
for (i = 0; i < n; i++) {
for (j = 0; j < n; j++) {
newDist[i][j] = dist[i][j];
newNext[i][j] = nextHop[i][j];
}
}
for (i = 0; i < n; i++) {
for (j = 0; j < n; j++) {
if (i == j)
con􀆟nue;
for (k = 0; k < n; k++) {
if (cost[i][k] != INF &&
dist[k][j] != INF &&
cost[i][k] + dist[k][j] < newDist[i][j]) {
newDist[i][j] =
cost[i][k] + dist[k][j];
newNext[i][j] = k;
changed = 1;
}
}
}
}
for (i = 0; i < n; i++) {
for (j = 0; j < n; j++) {
dist[i][j] = newDist[i][j];
nextHop[i][j] = newNext[i][j];
}
}
} while (changed);
prin􀆞("\nFinal Rou􀆟ng Tables:\n");
for (i = 0; i < n; i++) {
prin􀆞("\nRouter %c:\n", 'A' + i);
prin􀆞("Des􀆟na􀆟on\tCost\tNext Hop\n");
for (j = 0; j < n; j++) {
prin􀆞("%c\t\t", 'A' + j);
if (dist[i][j] == INF)
prin􀆞("INF\t");
else
prin􀆞("%d\t", dist[i][j]);
if (nextHop[i][j] == -1)
prin􀆞("-\n");
else
prin􀆞("%c\n", 'A' + nextHop[i][j]);
}
}
prin􀆞("\nEnter source node (0 to %d): ", n - 1);
scanf("%d", &src);
prin􀆞("Enter des􀆟na􀆟on node (0 to %d): ", n - 1);
scanf("%d", &dest);
if (src < 0 || src >= n || dest < 0 || dest >= n) {
prin􀆞("Invalid node number.\n");
return 1;
}
if (dist[src][dest] == INF) {
prin􀆞("Des􀆟na􀆟on is unreachable.\n");
return 0;
}
prin􀆞("\nShortest path: ");
prin􀆞("%c", 'A' + src);
count = 0;
path[count++] = src;
i = src;
while (i != dest && count < n) {
i = nextHop[i][dest];
if (i == -1)
break;
path[count++] = i;
}
if (i != dest) {
prin􀆞("\nUnable to reconstruct path.\n");
return 1;
}
for (i = 1; i < count; i++)
prin􀆞(" -> %c", 'A' + path[i]);
prin􀆞("\nMinimum cost: %d\n", dist[src][dest]);
return 0;
}
