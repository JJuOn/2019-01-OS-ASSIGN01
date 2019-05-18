#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>

using namespace std;

bool isAvailable(int need[], int work[], int resourceNum);
bool allFinished(bool finish[], int processNum);
void deallocate(int allocation[], int work[], int resourceNum);

int main() {
	int processNum = 0, resourceNum = 0;
	int **allocation = NULL, **max = NULL, **need = NULL;
	int *work=NULL;
	bool *finish = NULL;
	cout << "Enter the number of processes : ";
	cin >> processNum;
	while (processNum < 3 || processNum >10) {
		cout << "Enter the number of processes again : ";
		cin >> processNum;
	}
	cout << "Enter the number of resource types : ";
	cin >> resourceNum;
	while (resourceNum > 10) {
		cout << "Enter the number of resource types again : ";
		cin >> resourceNum;
	}
	allocation = new int*[processNum];
	max = new int*[processNum];
	need = new int*[processNum];
	for (int i = 0; i < processNum; i++) {
		allocation[i] = new int[resourceNum];
		max[i] = new int[resourceNum];
		need[i] = new int[resourceNum];
		work = new int[resourceNum];
	}
	for (int i = 0; i < processNum; i++) {
		cout << "Enter allocation of process" << i << " : ";
		for (int j = 0; j < resourceNum; j++) {
			cin >> allocation[i][j];
		}
	}
	int opr;
	cout << "What do you want to enter? (1: MAX, 2:NEED) : ";
	cin >> opr;
	if (opr == 1) {
		for (int i = 0; i < processNum; i++) {
			cout << "Enter max of process" << i << " : ";
			for (int j = 0; j < resourceNum; j++) {
				cin >> max[i][j];
				need[i][j] = max[i][j] - allocation[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < processNum; i++) {
			cout << "Enter need of process" << i << " : ";
			for (int j = 0; j < resourceNum; j++) {
				cin >> need[i][j];
			}
		}
	}
	cout << "Enter available(work) : ";
	for (int i = 0; i < resourceNum; i++) {
		cin >> work[i];
	}
	finish = new bool[processNum];
	for (int i = 0; i < processNum; i++) {
		finish[i] = false;
	}
	stringstream result;
	while (!allFinished(finish,processNum)) {
		int index = -1;
		for (int i = 0; i < processNum; i++) {
			if (!finish[i] && isAvailable(need[i], work, resourceNum)) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "No Safe Sequence" << endl;
			return 0;
		}
		else {
			result << "P" << index << '\t';
			deallocate(allocation[index], work, resourceNum);
			finish[index] = true;
		}
	}
	cout << result.str() << endl;
	for (int i = 0; i < processNum; i++) {
		delete[] allocation[i];
		delete[] max[i];
		delete[] need[i];
	}
	delete[] allocation;
	delete[] max;
	delete[] need;
	delete[] work;
	delete[] finish;
}

bool isAvailable(int need[], int work[], int resourceNum) {
	for (int i = 0; i < resourceNum; i++) {
		if (need[i] > work[i]) {
			return false;
		}
	}
	return true;
}

bool allFinished(bool finish[], int processNum) {
	for (int i = 0; i < processNum; i++) {
		if (finish[i] == false) {
			return false;
		}
	}
	return true;
}

void deallocate(int allocation[], int work[], int resourceNum) {
	for (int i = 0; i < resourceNum; i++) {
		work[i] += allocation[i];
	}
	return;
}