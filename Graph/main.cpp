#include "Graph.cpp"
int main() {

    AdjGraph G;
    InitGraph(G);
    CreateGraph(G);
    MTGraph G2=TransferAdjGraph(G);
    Print(G2);


    MTGraph G3;
    InitGraph(G3);
    CreateGraph(G3);
    Print(G3);
    AdjGraph G4=TransferMTGraph(G3);
    Print(G4);
}