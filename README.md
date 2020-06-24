# GraphColoring
C++ Implementation of 2 methods of Graph coloring algorithm

This is an an implementation of 2 greedy algorithms to address the Graph coloring problem. The graph coloring problems states that what is the least amount of colors you can color k nodes with such that no two adjacent nodes may share a color.

<b>How to run </b>

This code runs from the command line and requires the following arguments from command line upon running

argv[1]: inFile1.txt which is provided "a text file contains a list of bi-directional edges,
representing an undirected graph, G=<N, E>.   A bi-directional edge in the data file should be treated as having two edges.  For example, an undirected edge <3, 5> in the data file,  means one directed edge from 3 to 5 and another directed edge from 5 to 3"

argv[2]: the number 1 or 2 to decide which if the greedy methods to use

argv[3]: outFile1.txt is created(displays each node and the color it was assigned to)

argv[4]: outFile2.txt is created outputs the graph from the data structure used to store it, in this case a 2-d dynamically allocated array

argv[5]: outFile3.txt is created outputs debuging

