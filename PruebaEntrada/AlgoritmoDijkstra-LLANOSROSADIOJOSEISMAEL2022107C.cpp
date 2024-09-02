#include <iostream>
#include <climits>

using namespace std;

struct arista {
    int origen, destino, peso;
    arista *sgteArista;
};

typedef arista *parista;

struct vertice {
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
};

typedef vertice *pvertice;

class grafo {
private:
    pvertice pGrafo;
    int numVertices;

public:
    grafo();
    ~grafo();
    void insertarVertice(int);
    void insertarArista(int, int, int);
    void imprimirGrafo();
    void Algoritmodedijkstra(int src);
    void imprimirRuta(int src, int target, const int* prev);
    void imprimirRutasyCaminos(int src, const int* dist, const int* prev);
    pvertice buscarVertice(int dato);
};

grafo::grafo() {
    pGrafo = NULL;
    numVertices = 0;
}

grafo::~grafo() {
    pvertice p = pGrafo, tmp;
    while (p != NULL) {
        parista a = p->adyacente, aTmp;
        while (a != NULL) {
            aTmp = a;
            a = a->sgteArista;
            delete aTmp;
        }
        tmp = p;
        p = p->sgteVertice;
        delete tmp;
    }
}

void grafo::insertarVertice(int x) {
    pvertice p = new vertice;
    p->datoOrigen = x;
    p->adyacente = NULL;
    p->sgteVertice = pGrafo;
    pGrafo = p;
    numVertices++;
}

void grafo::insertarArista(int x, int y, int peso) {
    pvertice p = pGrafo;
    while (p != NULL && p->datoOrigen != x) {
        p = p->sgteVertice;
    }
    if (p != NULL) {
        parista a = new arista;
        a->origen = x;
        a->destino = y;
        a->peso = peso;
        a->sgteArista = p->adyacente;
        p->adyacente = a;
    }
}

pvertice grafo::buscarVertice(int dato) {
    pvertice p = pGrafo;
    while (p != NULL && p->datoOrigen != dato) {
        p = p->sgteVertice;
    }
    return p;
}

void grafo::imprimirGrafo() {
    pvertice p = pGrafo;
    if (p == NULL) {
        cout << "Grafo vacio" << endl;
    } else {
        cout << "Vertice -> Aristas" << endl;
        while (p != NULL) {
            cout << p->datoOrigen;
            parista a = p->adyacente;
            if (a != NULL) {
                cout << " -> ";
                while (a != NULL) {
                    cout << a->destino << " (" << a->peso << ")";
                    if (a->sgteArista != NULL) {
                        cout << " -> ";
                    }
                    a = a->sgteArista;
                }
            }
            cout << endl;
            p = p->sgteVertice;
        }
    }
}

void grafo::Algoritmodedijkstra(int src) {
    const int INF = INT_MAX;
    int *dist = new int[numVertices];
    int *prev = new int[numVertices];
    bool *visited = new bool[numVertices];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int i = 0; i < numVertices; i++) {
        int u = -1;
        for (int j = 0; j < numVertices; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;

        visited[u] = true;

        pvertice pv = buscarVertice(u);
        if (pv == NULL) continue;

        parista pa = pv->adyacente;
        while (pa != NULL) {
            int v = pa->destino;
            int weight = pa->peso;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
            pa = pa->sgteArista;
        }
    }

    imprimirRutasyCaminos(src, dist, prev);

    delete[] dist;
    delete[] prev;
    delete[] visited;
}

void grafo::imprimirRuta(int src, int target, const int* prev) {
    if (target == src) {
        cout << src;
    } else if (prev[target] == -1) {
        cout << "No path";
    } else {
        imprimirRuta(src, prev[target], prev);
        cout << " -> " << target;
    }
}

void grafo::imprimirRutasyCaminos(int src, const int* dist, const int* prev) {
    for (int i = 0; i < numVertices; ++i) {
        if (i != src) {
            cout << "Ruta de " << src << " a " << i << ": ";
            imprimirRuta(src, i, prev);
            if (dist[i] == INT_MAX) {
                cout << " | No hay ruta";
            } else {
                cout << " | Peso Total: " << dist[i];
            }
            cout << endl;
        }
    }
}

int main() {
    grafo g;
    g.insertarVertice(0);
    g.insertarVertice(1);
    g.insertarVertice(2);
    g.insertarVertice(3);
    g.insertarVertice(4);
    g.insertarVertice(5);

    g.insertarArista(0, 1, 41);
    g.insertarArista(1, 0, 41);
    g.insertarArista(1, 2, 51);
    g.insertarArista(2, 1, 51);
    g.insertarArista(2, 3, 50);
    g.insertarArista(3, 2, 50);
    g.insertarArista(4, 3, 36);
    g.insertarArista(3, 4, 36);
    g.insertarArista(3, 5, 38);
    g.insertarArista(5, 3, 38);
    g.insertarArista(3, 0, 45);
    g.insertarArista(0, 3, 45);
    g.insertarArista(0, 5, 29);
    g.insertarArista(5, 0, 29);
    g.insertarArista(5, 4, 21);
    g.insertarArista(4, 5, 21);
    g.insertarArista(1, 4, 32);
    g.insertarArista(4, 1, 32);
    g.insertarArista(4, 2, 32);
    g.insertarArista(2, 4, 32);
    g.insertarArista(5, 1, 24);
    g.insertarArista(1, 5, 24);
    cout << "Grafo:" << endl;
    g.imprimirGrafo();

    for(int ruta = 0; ruta<6;ruta++){
         cout << "\nAlgoritmo de Dijkstra desde el vertice inicial " << ruta << ":" ;
         
    g.Algoritmodedijkstra(ruta);
    }
    return 0;
}

