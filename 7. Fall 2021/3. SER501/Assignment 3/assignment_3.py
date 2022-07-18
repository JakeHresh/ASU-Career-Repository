# -*- coding: utf-8 -*-
"""
SER501 Assignment 3 scaffolding code
created by: Xiangyu Guo
"""
import sys
# =============================================================================

time = 0


class Graph(object):
    """docstring for Graph"""
    user_defined_vertices = []
    dfs_timer = 0

    def __init__(self, vertices, edges):
        super(Graph, self).__init__()
        n = len(vertices)
        self.matrix = [[0 for x in range(n)] for y in range(n)]
        self.vertices = vertices
        self.edges = edges
        for edge in edges:
            x = vertices.index(edge[0])
            y = vertices.index(edge[1])
            self.matrix[x][y] = edge[2]

    def display(self):
        print(self.vertices)
        for i, v in enumerate(self.vertices):
            print(v, self.matrix[i])

    def transpose(self):
        for i in range(1, len(self.vertices)):
            for j in range(0, i):
                x = self.matrix[i][j]
                self.matrix[i][j] = self.matrix[j][i]
                self.matrix[j][i] = x

    def in_degree(self):
        print("In degree of the graph:")
        indegreeCounts = []
        for i in range(0, len(self.vertices)):
            indegreeCount = 0
            for j in range(0, len(self.vertices)):
                if self.matrix[j][i] == 1:
                    indegreeCount = indegreeCount + 1
            indegreeCounts.append(indegreeCount)
        self.print_degree(indegreeCounts)

    def out_degree(self):
        print("Out degree of the graph:")
        outdegreeCounts = []
        for i in range(0, len(self.vertices)):
            outdegreeCount = 0
            for j in range(0, len(self.vertices)):
                if self.matrix[i][j] == 1:
                    outdegreeCount = outdegreeCount + 1
            outdegreeCounts.append(outdegreeCount)
        self.print_degree(outdegreeCounts)

    def dfs_on_graph(self):
        vertexCollection = []
        for i in range(0, len(self.vertices)):
            vertexCollection.append(["WHITE", 0, 0, self.vertices[i], i])
        global time
        time = 0
        for j in range(0, len(self.vertices)):
            if vertexCollection[j][0] == "WHITE":
                self.dfs_visit(vertexCollection[j], vertexCollection)
        finalDTimes = []
        finalFTimes = []
        for k in range(0, len(self.vertices)):
            finalDTimes.append(vertexCollection[k][1])
            finalFTimes.append(vertexCollection[k][2])
        self.print_discover_and_finish_time(finalDTimes, finalFTimes)

    def dfs_visit(self, vertex, vertexCollection):
        vertex[0] = "GRAY"
        global time
        time = time + 1
        vertex[1] = time
        for i in range(0, len(self.vertices)):
            if self.matrix[vertex[4]][i] == 1:
                adjVer = vertexCollection[i]
                if adjVer[0] == "WHITE":
                    self.dfs_visit(adjVer, vertexCollection)
        vertex[0] = "BLACK"
        time = time + 1
        vertex[2] = time

    def prim(self, root):
        vC = []
        distances = []
        parents = []
        for i in range(0, len(self.vertices)):
            if self.vertices[i] != root:
                vC.append([float('inf'),
                          float('inf'),
                          self.vertices[i],
                          "None", i, -1, False])
                distances.append(float('inf'))
                parents.append("None")
            else:
                vC.append([0,
                          float('inf'),
                          self.vertices[i],
                          "None", i, -1, False])
                distances.append(0)
                parents.append("None")
        self.print_d_and_pi("Initial", distances, parents)
        for j in range(0, len(vC)):
            u = None
            for k in range(0, len(vC)):
                if not vC[k][6]:
                    u = vC[k]
            for k in range(0, len(vC)):
                if vC[k][0] < u[0] and not vC[k][6]:
                    u = vC[k]
            u[6] = True
            for z in range(0, len(vC)):
                if (self.matrix[u[4]][z] != 0 and
                        not vC[z][6] and
                        self.matrix[u[4]][z] < vC[z][0]):
                    parents[z] = u[2]
                    vC[z][0] = self.matrix[u[4]][z]
                    distances[z] = self.matrix[u[4]][z]
            self.print_d_and_pi(j, distances, parents)

    def bellman_ford(self, source):
        vC = []
        edges = []
        distances = []
        parents = []
        for i in range(0, len(self.vertices)):
            if self.vertices[i] != source:
                vC.append([float('inf'),
                          float('inf'),
                          self.vertices[i],
                          "None", i, -1, False])
                distances.append(float('inf'))
                parents.append("None")
            else:
                vC.append([0,
                          float('inf'),
                          self.vertices[i],
                          "None", i, -1, False])
                distances.append(0)
                parents.append("None")
        self.relax(len(self.vertices), self.matrix, edges, vC)
        self.print_d_and_pi("Initial", distances, parents)
        for i in range(0, len(self.vertices) - 1):
            for edge in edges:
                if edge[1][0] > edge[0][0] + edge[4]:
                    parents[edge[3]] = edge[0][2]
                    edge[1][0] = edge[0][0] + edge[4]
                    vC[edge[3]][0] = edge[1][0]
                    distances[edge[3]] = edge[1][0]
            self.print_d_and_pi(i, distances, parents)
        for edge in edges:
            if edge[1][0] > edge[0][0] + edge[4]:
                print("No Solution")

    def relax(self, length, matrix, edges, vertices):
        for i in range(0, length):
            for j in range(0, length):
                if matrix[i][j] != 0:
                    edges.append(
                        [vertices[i], vertices[j],
                            i, j, matrix[i][j]])

    def dijkstra(self, source):
        vC = []
        distances = []
        parents = []
        for i in range(0, len(self.vertices)):
            if self.vertices[i] != source:
                vC.append([float('inf'),
                          float('inf'),
                          self.vertices[i],
                          "None", i, -1, False])
                distances.append(float('inf'))
                parents.append("None")
            else:
                vC.append([0,
                          float('inf'),
                          self.vertices[i],
                          "None", i, -1, False])
                distances.append(0)
                parents.append("None")
        self.print_d_and_pi("Initial", distances, parents)
        for j in range(0, len(vC)):
            u = None
            for k in range(0, len(vC)):
                if not vC[k][6]:
                    u = vC[k]
            for k in range(0, len(vC)):
                if vC[k][0] < u[0] and not vC[k][6]:
                    u = vC[k]
            u[6] = True
            for z in range(0, len(vC)):
                if (self.matrix[u[4]][z] != 0 and
                        not vC[z][6] and
                        self.matrix[u[4]][z] + u[0] < vC[z][0]):
                    parents[z] = u[2]
                    vC[z][0] = self.matrix[u[4]][z] + u[0]
                    distances[z] = self.matrix[u[4]][z] + u[0]
            self.print_d_and_pi(j, distances, parents)

    def print_d_and_pi(self, iteration, d, pi):
        assert((len(d) == len(self.vertices)) and
               (len(pi) == len(self.vertices)))

        print("Iteration: {0}".format(iteration))
        for i, v in enumerate(self.vertices):
            val = 'inf' if d[i] == sys.maxsize else d[i]
            print("Vertex: {0}\td: {1}\tpi: {2}".format(v, val, pi[i]))

    def print_discover_and_finish_time(self, discover, finish):
        assert((len(discover) == len(self.vertices)) and
               (len(finish) == len(self.vertices)))
        for i, v in enumerate(self.vertices):
            print("Vertex: {0}\tDiscovered: {1}\tFinished: {2}".format(
                    v, discover[i], finish[i]))

    def print_degree(self, degree):
        assert((len(degree) == len(self.vertices)))
        for i, v in enumerate(self.vertices):
            print("Vertex: {0}\tDegree: {1}".format(v, degree[i]))


def main():
    # Thoroughly test your program and produce useful output.
    # Q1 and Q2
    graph = Graph(['1', '2'], [('1', '2', 1)])
    graph.display()
    graph.transpose()
    graph.display()
    graph.transpose()
    graph.display()
    graph.in_degree()
    graph.out_degree()
    graph.print_d_and_pi(1, [1, sys.maxsize], [2, None])
    graph.print_degree([1, 0])
    graph.print_discover_and_finish_time([0, 2], [1, 3])

    # Q3
    graph = Graph(['q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'],
                  [('q', 's', 1),
                   ('s', 'v', 1),
                   ('v', 'w', 1),
                   ('w', 's', 1),
                   ('q', 'w', 1),
                   ('q', 't', 1),
                   ('t', 'x', 1),
                   ('x', 'z', 1),
                   ('z', 'x', 1),
                   ('t', 'y', 1),
                   ('y', 'q', 1),
                   ('r', 'y', 1),
                   ('r', 'u', 1),
                   ('u', 'y', 1)])
    graph.display()
    graph.dfs_on_graph()

    # Q4 - Prim
    graph = Graph(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'],
                  [('A', 'H', 6),
                   ('H', 'A', 6),
                   ('A', 'B', 4),
                   ('B', 'A', 4),
                   ('B', 'H', 5),
                   ('H', 'B', 5),
                   ('B', 'C', 9),
                   ('C', 'B', 9),
                   ('G', 'H', 14),
                   ('H', 'G', 14),
                   ('F', 'H', 10),
                   ('H', 'F', 10),
                   ('B', 'E', 2),
                   ('E', 'B', 2),
                   ('G', 'F', 3),
                   ('F', 'G', 3),
                   ('E', 'F', 8),
                   ('F', 'E', 8),
                   ('D', 'E', 15),
                   ('E', 'D', 15)])
    graph.prim('G')

    # Q5
    graph = Graph(['s', 't', 'x', 'y', 'z'],
                  [('t', 'x', 5),
                   ('t', 'y', 8),
                   ('t', 'z', -4),
                   ('x', 't', -2),
                   ('y', 'x', -3),
                   ('y', 'z', 9),
                   ('z', 'x', 7),
                   ('z', 's', 2),
                   ('s', 't', 6),
                   ('s', 'y', 7)])
    graph.bellman_ford('z')

    # Q5 alternate
    graph = Graph(['s', 't', 'x', 'y', 'z'],
                  [('t', 'x', 5),
                   ('t', 'y', 8),
                   ('t', 'z', -4),
                   ('x', 't', -2),
                   ('y', 'x', -3),
                   ('y', 'z', 9),
                   ('z', 'x', 4),
                   ('z', 's', 2),
                   ('s', 't', 6),
                   ('s', 'y', 7)])
    graph.bellman_ford('s')

    # Q6
    graph = Graph(['s', 't', 'x', 'y', 'z'],
                  [('s', 't', 3),
                   ('s', 'y', 5),
                   ('t', 'x', 6),
                   ('t', 'y', 2),
                   ('x', 'z', 2),
                   ('y', 't', 1),
                   ('y', 'x', 4),
                   ('y', 'z', 6),
                   ('z', 's', 3),
                   ('z', 'x', 7)])
    graph.dijkstra('s')


if __name__ == '__main__':
    main()
