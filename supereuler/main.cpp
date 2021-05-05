#include"supereuler.h"
#pragma warning(disable:4996)

int main() {
	ifstream myfile("data.txt");
	ofstream outfile("out.txt", ios::app);
	if (!myfile.is_open()) {
		cout << "The file was not opened successfully" << endl;
		system("pause");
		return 0;
	}
	int vexnum;
	int n = 1;
	int arccopy[100][100] = { NULL };
	while (myfile >> vexnum) {
		Graph_DG graph(vexnum);									//Generate an adjacency matrix space
		int weight;
		memset(graph.degree, 0, sizeof(graph.degree));			//The degree matrix is given an initial value of 0
		for (int i = 0; i != vexnum; i++) {
			for (int j = 0; j != vexnum; j++) {					//Assigns a value to the corresponding point of the adjacency matrix
				myfile >> weight;
				arccopy[i][j] = weight;							//saving with arccopy might write to a matrix in a file
				if (weight == 0) {
					graph.arc[i][j] = INT_MAX;
				}
				else {
					graph.arc[i][j] = weight;
					graph.degree[i] = graph.degree[i] + 1;
				}
			}
		}
		while (graph.check()) {									//Check that all vertices are included
			if (graph.public_side()) {							//Find and set public edges
				if (graph.print_path()) {						//Add the shortest path found to the sequence
					outfile << "No." << n << "It's not a hypereuler graph(public side):" << endl;
					for (int i = 0; i != vexnum; i++) {
						for (int j = 0; j != vexnum; j++) {
							outfile << arccopy[i][j] << " ";
						}
						outfile << endl;
					}
					goto loop;
				}
				continue;
			}
			if (graph.public_point()) {							// Find and set public points
				if (graph.print_path()) {
					outfile << "No." << n << "It's not a hypereuler graph(public point):" << endl;
					for (int i = 0; i != vexnum; i++) {
						for (int j = 0; j != vexnum; j++) {
							outfile << arccopy[i][j] << " ";
						}
						outfile << endl;
					}
					goto loop;
				}
			}
			else {
				outfile << "No." << n << "It's not a hypereuler graph(All conditions are not met):" << endl;
				for (int i = 0; i != vexnum; i++) {
					for (int j = 0; j != vexnum; j++) {
						cout << arccopy[i][j] << " ";
						outfile << arccopy[i][j] << " ";
					}
					cout << endl;
					outfile << endl;
				}
				break;
			}
		}
	loop:graph.clean();
		//system("pause");
		n++;
	}
	myfile.close();
	outfile.close();
	system("pause");
	return 0;
}