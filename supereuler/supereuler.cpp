#include"supereuler.h"

vector <int >sequence(1, NULL);
// The dynamic array records the current sequence of rings for final output.Placing in the floyd.h file causes multiple definition errors.

// Constructor function
Graph_DG::Graph_DG(int vexnum) {
	this->vexnum = vexnum;
	arc = new int*[this->vexnum];
	dis = new int*[this->vexnum];
	path = new int*[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new int[this->vexnum];
		dis[i] = new int[this->vexnum];
		path[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			arc[i][k] = INT_MAX;
		}
	}
}
// destructor function
Graph_DG::~Graph_DG() {
	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
		delete this->dis[i];
		delete this->path[i];

	}
	delete dis;
	delete arc;
	delete path;
}

void Graph_DG::clean() {
	sequence.assign({ NULL });
}

void Graph_DG::Floyd() {
	int row = 0;
	int col = 0;
	for (row = 0; row < this->vexnum; row++) {
		for (col = 0; col < this->vexnum; col++) {				// Initializes the matrix D to the value of the adjacency matrix
			this->dis[row][col] = this->arc[row][col];			// The initial value of the matrix P is the subscript of the vertices at the end of each edge
			this->path[row][col] = col;
		}
	}
	// Triple loop to calculate the shortest path for each point pair
	int temp = 0;
	int select = 0;
	for (temp = 0; temp < this->vexnum; temp++) {
		for (row = 0; row < this->vexnum; row++) {
			for (col = 0; col < this->vexnum; col++) {			// To prevent overflows, we need to introduce a SELECT value
				select = (dis[row][temp] == INT_MAX || dis[temp][col] == INT_MAX) ? INT_MAX : (dis[row][temp] + dis[temp][col]);
				if (this->dis[row][col] > select) {				// Update the D matrix
					this->dis[row][col] = select;				// Update the P matrix
					this->path[row][col] = this->path[row][temp];
				}
			}
		}
	}
}

bool Graph_DG::print_path() {
	int row = pre;
	int col = beh;

	if ((style == 1) && (this->dis[row - 1][col - 1] == INT_MAX)) {
		cout << "A new ring cannot be constructed, and the graph does not possess hyperEuler property" << endl;
		return true;
	}
	else {
		int post;												// The pubilc edge starts at the position of the sequence
		for (int i = 0; i < sequence.size() - 1; i++) {
			if (sequence[i] == row) {
				if (style == 1) {								// The pubilc point is a little different from the pubilc edge
					post = i;
					break;
				}
				else {
					int j = i + 1;
					if (j > sequence.size() - 1)
						j = 0;
					if (sequence[j] == col) {
						post = i;
						break;
					}
				}
			}
		}
		//Loop each path of the output path
		int temp = 0;
		cout << "new path:" << to_string(row) << " to " << to_string(col) << " path: " << to_string(row);
		temp = path[row - 1][col - 1];
		while (temp != col - 1) {
			cout << "-->" << to_string(temp + 1);
			sequence.insert(sequence.begin() + post + 1, temp + 1);		//Insert into the sequence
			post++;
			temp = path[temp][col - 1];
		}
		cout << "-->" << to_string(col) << endl;
		cout << endl;
		if (style == 1) {											//When the point is pubilc, the starting point is also inserted into the sequence to achieve splitting
			sequence.insert(sequence.begin() + post + 1, col);
			sequence.insert(sequence.begin() + post + 2, row);
		}
		else {
			if (sequence.size() > 4) {								//Save pubilc edge
				arc[row - 1][col - 1] = 1;
				arc[col - 1][row - 1] = 1;
			}
			else {
				pre = 0; beh = 0;
			}
		}
		////////////////////////////////////////////////////////////////
		cout << "Check the sequence after merging:";
		for (int i = 0; i < sequence.size(); i++)
		{
			cout << sequence[i] << " ";
		}
		cout << endl;
		cout << endl;
		////////////////////////////////////////////////////////////////
	}
	return false;
}

bool Graph_DG::check() {
	if (sequence[0] == NULL) {
		return true;
	}
	int k;
	for (int i = 1; i <= vexnum; i++) {
		for (int j = 0; j <= sequence.size() - 1; j++) {
			k = j;
			if (sequence[j] == i) {
				break;
			}
		}
		if (k == sequence.size() - 1) {
			cout << "point " << i << " not contain" << endl;
			return true;
		}
	}
	cout << "All points contain, the graph has surperEuler property" << endl;
	return false;
}

bool Graph_DG::public_side() {
	style = 0;
	if (sequence[0] == NULL) {								//The first time I look for it, I base it on vertex one and its adjacent edges
		sequence[0] = 1;
		sequence.insert(sequence.begin(), 1);				//The loop ends with the same vertices
		for (int i = 2; i <= vexnum; i++) {					// The adjacency matrix finds the second point
			if (arc[0][i - 1] != INT_MAX) {
				sequence.insert(sequence.begin() + 1, i);
				break;
			}
		}
		pre = sequence[0]; beh = sequence[1];
		cout << "Set the initial sequence:";
		for (int i = 0; i < sequence.size(); i++) {
			cout << sequence[i] << " ";
		}
		cout << endl;
		arc[sequence[0] - 1][sequence[1] - 1] = INT_MAX;
		arc[sequence[1] - 1][sequence[0] - 1] = INT_MAX;
		Floyd();
	}
	else {													//If have a ring, find a point with contiguity greater than or equal to 3 as a pubilc edge
		for (int i = 0; i < sequence.size() - 1; i++) {
			int j = i + 1;
			if (((sequence[i] == pre) && (sequence[j] == beh)) || ((sequence[j] == pre) && (sequence[i] == beh))) {
				//degree[pre - 1] --; degree[beh - 1] --;	//The degree is modified only when the pubilc edge exists in the vertex sequence
			}
			if (j > sequence.size() - 1)
				j = 0;
			if (arc[sequence[i] - 1][sequence[j] - 1] != INT_MAX) {
				arc[sequence[i] - 1][sequence[j] - 1] = INT_MAX;
				arc[sequence[j] - 1][sequence[i] - 1] = INT_MAX;
			}
		}
		int k;
		Floyd();
		for (int i = 0; i <= sequence.size() - 2; i++) {
			k = i;
			if (degree[sequence[i] - 1] >= 3) {
				int j = i + 1;

				if (degree[sequence[j] - 1] >= 3) {

					if (dis[sequence[i] - 1][sequence[j] - 1] != INT_MAX) {			//Try to find a pubilc edge that forms a ring
						cout << "Find the pubilc edge:" << sequence[i] << "-->" << sequence[j] << endl;
						pre = sequence[i]; beh = sequence[j];
						return true;
					}
				}
			}
		}
		if (k == sequence.size() - 2) {
			cout << "No pubilc edge found" << endl;
			return false;
		}
	}
}

bool Graph_DG::public_point() {
	style = 1;													//Look for points with degrees greater than or equal to 4 as pubilc points
	for (int i = 0; i < sequence.size() - 1; i++) {				//Remove the original ring edge from the adjacency matrix
		int j = i + 1;
		if (j > sequence.size() - 1)
			j = 0;
		if (arc[sequence[i] - 1][sequence[j] - 1] != INT_MAX) {
			arc[sequence[i] - 1][sequence[j] - 1] = INT_MAX;
			arc[sequence[j] - 1][sequence[i] - 1] = INT_MAX;
		}
	}
	int i;
	for (i = 0; i <= sequence.size() - 1; i++) {
		if (degree[sequence[i] - 1] >= 4) {
			pre = sequence[i];
			for (int k = 1; k <= vexnum; k++) {
				if (pre == k)continue;
				if (arc[pre - 1][k - 1] != INT_MAX) {
					arc[pre - 1][k - 1] = INT_MAX;
					arc[k - 1][pre - 1] = INT_MAX;
					Floyd();
					if (dis[pre - 1][k - 1] != INT_MAX) {
						cout << "Find a pubilc point:" << sequence[i] << endl;
						beh = k;
						degree[pre - 1] = degree[pre - 1] - 2;						//Modifies the pubilc point degree in a degree group

						cout << "The starting edge of the new ring" << pre << "-->" << beh << endl;
						return true;
					}
					else {
						arc[pre - 1][k - 1] = 1;
						arc[k - 1][pre - 1] = 1;
					}
				}
			}
		}
	}
	if (i == sequence.size()) {
		cout << "No pubilc point found" << endl;
		return false;
	}
}
