import networkx as nx
import matplotlib.pyplot as plt


class Graph:
    def __init__(self, filename):
        self.adjacency_list = self.read_graph_from_file(filename)

    def read_graph_from_file(self, filename):
        with open(filename, 'r') as file:
            N = int(file.readline().strip())
            adjacency_matrix = [list(map(int, file.readline().strip().split())) for _ in range(N)]
        return self.convert_to_adjacency_list(adjacency_matrix)

    def convert_to_adjacency_list(self, adjacency_matrix):
        adjacency_list = {}
        for i in range(len(adjacency_matrix)):
            adjacency_list[i] = []
            for j in range(len(adjacency_matrix[i])):
                if adjacency_matrix[i][j] == 1:
                    adjacency_list[i].append(j)
        return adjacency_list

    def dfs(self, start_vertex):
        visited = set()
        traversal_order = []
        spanning_tree_edges = []

        def _dfs(v):
            visited.add(v)
            traversal_order.append(v)
            for neighbor in self.adjacency_list[v]:
                if neighbor not in visited:
                    spanning_tree_edges.append((v, neighbor))
                    _dfs(neighbor)

        _dfs(start_vertex)
        return traversal_order, spanning_tree_edges

    def bfs(self, start_vertex):
        visited = set()
        queue = [start_vertex]
        traversal_order = []
        spanning_tree_edges = []

        visited.add(start_vertex)
        while queue:
            v = queue.pop(0)
            traversal_order.append(v)
            for neighbor in self.adjacency_list[v]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
                    spanning_tree_edges.append((v, neighbor))

        return traversal_order, spanning_tree_edges

    def draw_graph(self):
        G = nx.Graph()
        for node, neighbors in self.adjacency_list.items():
            for neighbor in neighbors:
                G.add_edge(node, neighbor)

        pos = nx.spring_layout(G)
        nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=500, edge_color='gray')
        plt.show()


def main():
    filename = 'test.txt'
    graph = Graph(filename)

    # Przeszukiwanie w głąb (DFS)
    dfs_order, dfs_edges = graph.dfs(0)
    print("DFS Order:", dfs_order)
    print("DFS Spanning Tree Edges:", dfs_edges)

    # Przeszukiwanie wszerz (BFS)
    bfs_order, bfs_edges = graph.bfs(0)
    print("BFS Order:", bfs_order)
    print("BFS Spanning Tree Edges:", bfs_edges)

    # Rysowanie grafu
    graph.draw_graph()


if __name__ == "__main__":
    main()
