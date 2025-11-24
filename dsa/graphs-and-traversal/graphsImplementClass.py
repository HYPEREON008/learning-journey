


class Graph:
    def __init__(self,size):
        self.adj_matrix = [[0]*size for i in range(size)]
        #avoid using [[0]*size]*size as it creates references to the same list, changing one list changes this other,, this happens for mutable data types like lists
        self.size = size
        self.vertex_data = [""]*size
        #Initialize vertex data with empty strings
        #vertex data contains names of the vertices
    
    def add_edge(self,u,v):
        if 0<=u<self.size and 0<=v<self.size:
            self.adj_matrix[u][v] = 1
            self.adj_matrix[v][u] = 1

    def add_vertex_data(self,v,data):
        if 0<=v<self.size:
            self.vertex_data[v] = data

    def display(self):
        print("adjacency matrix:")
        for row in self.adj_matrix:
            #convert ints to strings for joining
            str_row = [str(i) for i in row]
            #or str_row = map(str, row)
            print(" ".join(str_row))
        print("vertex data:")
        # for i in range(self.size):
        #     print(f"{i}: {self.vertex_data[i]}")
        #or
        for i,data in enumerate(self.vertex_data):
            print(f"{i}: {data}")

    def dfs_help(self, v, visited): 
        # helper function for dfs is not meant to be called by user
        visited[v] = True
        print(self.vertex_data[v], end=" ") #process the vertex(here we just print it)

        for i in range(self.size):
            if self.adj_matrix[v][i] == 1 and not visited[i]: 
                #if there exists edge between v and i and i has not been visited
                self.dfs_help(i, visited)

    def dfs(self, start_vertex_data):
        visited = [False]*self.size #list of booleans to track visited vertices
        start_vertex_index = self.vertex_data.index(start_vertex_data) #get index of start vertex from its data
        self.dfs_help(start_vertex_index, visited)

    def bfs(self, start_vertex_data):
        visited = [False]*self.size
        start_vertex_index = self.vertex_data.index(start_vertex_data)
        queue = []
        visited[start_vertex_index] = True
        queue.append(start_vertex_index)

        while queue:
            v = queue.pop(0) #O(n) operation, can be optimized using collections.deque for O(1) pops from left
            #deque stands for double ended queue
            print(self.vertex_data[v], end=" ") #process the vertex(here we just print it)
            for i in range(self.size):
                if self.adj_matrix[v][i] == 1 and not visited[i]:
                    visited[i] = True
                    queue.append(i)

        print("\nBFS complete")

#algorithm
"""
add vertex to visited
add vertex to queue

unload vertex from queue

do vertex action(here print)
check its edges for children vertices

mark them visited
add them to queue

unload these vertices from queue one by one
repeat until queue is empty
"""


#Eg usage
g = Graph(5)
g.add_vertex_data(0,"A")
g.add_vertex_data(1,"B")
g.add_vertex_data(2,"C")
g.add_vertex_data(3,"D")
g.add_vertex_data(4,"E")

g.add_edge(0,1) #A-B
g.add_edge(0,4) #A-E
g.add_edge(1,4) #B-E

g.display()

g.dfs('A') #start DFS from vertex with data 'A'


