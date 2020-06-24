// Joseph Bdaro

#include <iostream>
#include <fstream>

using namespace std;

class GraphColoring {

public:
	int numNodes;
	int** gList;
	int* colorList;
	int* usedColorList;
	int newColor = 0;
	int newNode;
	int whichMethod;
	int usedColor;

	GraphColoring(ifstream& inFile1, int whichMethod) {
		inFile1 >> numNodes;
		
		//declares and initializes the 1-d array colorlist
		colorList = new int[numNodes + 1];
		for (int i = 0; i < numNodes + 1; i++) {
			//0 means they are uncolored
			colorList[i] = 0;
		}

		//initialized the array used Color list which will label all the used colors
		usedColorList = new int[numNodes + 1];
		for (int i = 0; i < numNodes + 1; i++) {
			//0 means they are not used
			usedColorList[i] = 0;
		}

		//initializes the 2-d array that will hold the graph
		gList = new int* [numNodes + 1];
		for (int i = 0; i < numNodes + 1; i++) {
			gList[i] = new int[numNodes + 1];
		}
		for (int i = 0; i < numNodes + 1; i++) {
			for (int j = 0; j < numNodes + 1; j++) {
				gList[i][j] = 0;
			}
		}

		//fills the graphs up from the inFile
		int x, y;
		while (inFile1 >> x && inFile1 >> y) {
			gList[x][y] = 1;
			gList[y][x] = 1;
		}

		this->whichMethod = whichMethod;
	}

	void method1(ifstream& inFile1, ofstream& outFile1, ofstream& outFile2, ofstream& outFile3) {
		//loops untill all nodes are colored 
		while (allNodesColored() == false) {
			newColor++;
			newNode = 1;
			newNode = getUncoloredNode(newNode);
			while (newNode <= numNodes && colorList[newNode] == 0) {
				//grabs a new uncolored node
				if (ok(newNode, newColor) == true) {
					colorList[newNode] = newColor;
				}
				newNode = getUncoloredNode(newNode + 1);
			}
			printColorList(outFile3);
		}
		printColorList(outFile1);
		printDataStruct(outFile2);
	}
	
	void method2(ifstream& inFile1, ofstream& outFile1, ofstream& outFile2, ofstream& outFile3) {
		newNode = 1;
		newNode = getUncoloredNode(newNode);
		while (allNodesColored() != true) {
			if (findUsedColor(newNode) == true) {
				colorList[newNode] = usedColor;
			}
			else {
				colorList[newNode] = findNewColor();
			}
			newNode = getUncoloredNode(newNode + 1);
			printColorList(outFile3);
		}
		printColorList(outFile1);
		printDataStruct(outFile2);
	}

	int getUncoloredNode(int newNode) {
		int i = newNode;
		while (i <= numNodes && colorList[i] != 0) {
			i++;
		}
		return i;
	}
	//returns true if all nodes are colored and false if not
	bool allNodesColored() {
		int i = 1;
		while (i <= numNodes) {
			if (colorList[i] == 0) {
				return false;
			}
			i++;
		}
		return true;
	}

	bool ok(int newNode, int newColor) {
		for(int i = 1; i <= numNodes; i++) {
			if (gList[newNode][i] != 0) {
				if (colorList[i] == newColor) {
					return false;
				}
			}
		}
		return true;
	}

	//prints the color list
	void printColorList(ofstream& outFile) {
		outFile << whichMethod << endl <<endl;
		outFile << numNodes <<endl;
		for (int i = 1; i <= numNodes; i++) {
			outFile << i << " " << colorList[i] << endl;
		}
		outFile << endl << endl << endl;
	}

	//prints the adjacency matrix
	void printDataStruct(ofstream& outFile2) {
		outFile2 << "  ";
		for (int i = 1; i <= numNodes; i++) {
			if (i >= 10) {
				outFile2 << "|" << i << " ";
			}
			else {
				outFile2 << "| " << i << " ";
			}
		}
		outFile2 << "|" <<endl;

		for (int i = 1; i <= numNodes; i++) {
			if (i >= 10) {
				outFile2 << i << "| ";
			}
			else {
				outFile2 << i << " | ";
			}
			for (int j = 1; j <= numNodes; j++) {
				outFile2 << gList[i][j] << " | ";
			}
			outFile2 << endl;
		}
	}

	//it gets very complicated here but bear with me we will go through the entire used color list first with this for loop
	bool findUsedColor(int newNode) {
		for (int i = 1; i <= numNodes; i++) {
			//the first color we find that is considered used we will do the following 
			if (usedColorList[i] != 0) {
				//we will take that used color in our case right now it's i and we will test it 
				for (int j = 1; j <= numNodes; j++) {
					//we will go through the 2d- array and if we find an edge 
					if (gList[newNode][j] != 0) {
						//we will check if the neightbor of our newnode has that same color that we picked from the used colorlist if it is then we will need to break and find the next used color i
						if (colorList[j] == i) {
							break;
						}

					}
					//if we have reached  this line of code then this used color i is perfectly acceptable to use to color our newNode as it has checked all it's neighbors and none of the neighbors were using that used color
					if (j == numNodes) {
						usedColor = i;
						return true;
					}
				}
				
			}
		}
		//if we have gotten to this line of code that means we have checked all the used colors and none of them were suitable, we will have to find a new color to use
		return false;
	}

	int findNewColor() {
		for (int i = 1; i <= numNodes; i++) {
			if (usedColorList[i] == 0) {
				usedColorList[i] = 1;
				return i;
			}
		}
	}
};

int main(int argc, char* argv[])
{
	ifstream inFile1;
	ofstream outFile1;
	ofstream outFile2;
	ofstream outFile3;

	inFile1.open(argv[1]);

	int whichMethod = strtol(argv[2], NULL, 10);
	
	outFile1.open(argv[3]);
	outFile2.open(argv[4]);
	outFile3.open(argv[5]);

	GraphColoring* newGraph = new GraphColoring(inFile1, whichMethod);

	switch (whichMethod)
	{
	case 1: newGraph->method1(inFile1, outFile1, outFile2, outFile3);
		break;
	
	case 2: newGraph->method2(inFile1, outFile1, outFile2, outFile3);
		break;

	default:
		cout << "Your entry was invalid please choose either 1 or 2";
		break;
	}
	inFile1.close();
	outFile1.close();
	outFile2.close();
	outFile3.close();

}
