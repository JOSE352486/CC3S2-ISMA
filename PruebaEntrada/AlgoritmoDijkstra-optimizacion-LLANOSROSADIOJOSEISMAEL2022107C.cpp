#include <queue>
#include <vector>
#include <functional>

void grafo::Algoritmodedijkstra(int src) {
    const int INF = INT_MAX;
    std::vector<int> dist(numVertices, INF);
    std::vector<int> prev(numVertices, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        pvertice pv = buscarVertice(u);
        if (pv == nullptr) continue;

        for (parista pa = pv->adyacente; pa != nullptr; pa = pa->sgteArista) {
            int v = pa->destino;
            int weight = pa->peso;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    imprimirRutasyCaminos(src, dist.data(), prev.data());
}
