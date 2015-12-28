#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
typedef struct node_struct *airport;
typedef struct edge_struct *route;
typedef struct graph_struct *graph;
typedef struct tree_struct *tree;
typedef struct coda *tail;


struct tree_struct{
airport elem;
tree nxt;
tree father;
int val;
};
struct node_struct {
int nodeid;
char *code;
route starOut;
airport nxt;
int visitato;
};
struct edge_struct {
int cost;
int distance;
airport nodeDst;
route prv;
};
struct graph_struct {
int numberOfNodes;
airport listOfAirport;
int id;
};
struct coda{
    tail nxt;
    tail bck;
    airport elem;
};
