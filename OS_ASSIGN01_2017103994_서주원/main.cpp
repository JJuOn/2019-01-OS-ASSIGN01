#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>

using namespace std;

//need<=work���� ��ȯ���ִ� �Լ�
bool isAvailable(int need[], int work[], int resourceNum);
//��� ���μ������� �������� ��ȯ���ִ� �Լ�
bool allFinished(bool finish[], int processNum);
//�۾��� �Ϸ�� ���μ����� �ڿ��� work�� �߰����ִ� �Լ�
void deallocate(int allocation[], int work[], int resourceNum);

int main() {
	int processNum = 0, resourceNum = 0;// ���μ����� ���� processNum, �ڿ��� ������ ���� resourceNum
	// ���μ������� ���� �ִ� �ڿ��� ���¸� ��Ÿ�� allocation, ���μ������� Ư�� ������ �ִ�� �ʿ�� �ϴ� �ڿ��� ������ ��Ÿ�� max, max - allocation�� ����� need
	int **allocation = NULL, **max = NULL, **need = NULL;   
	int *work=NULL;// ���� �̿밡���� �ڿ��� ������ ��Ÿ�� work
	bool *finish = NULL; // ���μ������� �۾��� ������ �� �˷��� finish
	//���μ����� ���� �Է�
	cout << "Enter the number of processes : ";
	cin >> processNum;
	// ���μ����� ������ 3�� �̸��̰ų� 10�� �̻��̸� ���Է� 
	while (processNum < 3 || processNum >=10) {
		cout << "Enter the number of processes again : ";
		cin >> processNum;
	}
	// �ڿ��� ���� ���� �Է�
	cout << "Enter the number of resource types : ";
	cin >> resourceNum;
	// �ڿ��� ������ ������ 10�� �̻��̸� ���Է�
	while (resourceNum >= 10) {
		cout << "Enter the number of resource types again : ";
		cin >> resourceNum;
	}
	// ���μ��� ������ŭ�� �迭 ���� �Ҵ�
	allocation = new int*[processNum];
	max = new int*[processNum];
	need = new int*[processNum];
	for (int i = 0; i < processNum; i++) {
		//allocation, max, need�� 2���� �迭�̹Ƿ�, �߰��� ���� �Ҵ�
		allocation[i] = new int[resourceNum];
		max[i] = new int[resourceNum];
		need[i] = new int[resourceNum];
		//work�� 1���� �迭�̹Ƿ� ���� �Ҵ�
		work = new int[resourceNum];
	}
	// ������ ���μ����� ���ؼ� ���� �Ҵ� ���� �Է�
	for (int i = 0; i < processNum; i++) {
		cout << "Enter allocation of process" << i << " : ";
		for (int j = 0; j < resourceNum; j++) {
			cin >> allocation[i][j];
		}
	}
	int opr;
	// ����ڴ� MAX�� �Է��� �� NEED�� �Է��� �� ������ �� ���� 
	cout << "What do you want to enter? (1: MAX, 2:NEED) : ";
	cin >> opr;
	// MAX�� �Է��� ��
	if (opr == 1) {
		// ������ ���μ����鿡 ���Ͽ� 
		for (int i = 0; i < processNum; i++) {
			//max ���� �Է� �ް�
			cout << "Enter max of process" << i << " : ";
			for (int j = 0; j < resourceNum; j++) {
				cin >> max[i][j];
				// max - allocation �� ���� need�� ����
				need[i][j] = max[i][j] - allocation[i][j];
			}
		}
	}
	// NEED�� �ٷ� �Է��� ��
	else {
		// ������ ���μ����鿡 ���Ͽ�
		for (int i = 0; i < processNum; i++) {
			// need ���� �Է� �޾� ����
			cout << "Enter need of process" << i << " : ";
			for (int j = 0; j < resourceNum; j++) {
				cin >> need[i][j];
			}
		}
	}
	// ���� ��밡���� �ڿ��� ���� �Է�
	cout << "Enter available(work) : ";
	for (int i = 0; i < resourceNum; i++) {
		cin >> work[i];
	}
	// ���μ������� �۾� �Ϸ� ���¸� �˷��ֱ� ���� finish ���� �Ҵ�
	finish = new bool[processNum];
	// �ʱⰪ�� false�� ����
	for (int i = 0; i < processNum; i++) {
		finish[i] = false;
	}
	// safe sqeuence�� ����ϱ����� result
	stringstream result;
	// ������ ���� ���μ����� ���� ��,
	while (!allFinished(finish,processNum)) {
		// ���� ������ ������Ű�� i�� ã�� ������ index
		int index = -1;
		// ������ ���μ����� ����
		for (int i = 0; i < processNum; i++) {
			// �۾��� �Ϸ���� �ʾҰ�, ���ÿ� need <= work�̸�
			if (!finish[i] && isAvailable(need[i], work, resourceNum)) {
				// index�� i�� ����
				index = i;
				break;
			}
		}
		// ���� �� ������ �����ϴ� ���μ����� ã�� ���ߴٸ�
		if (index == -1) {
			// safe sequence�� ���ٰ� �Ǵ�
			cout << "No Safe Sequence" << endl;
			// ���α׷� ����
			return 0;
		}
		// �� ������ �����ϴ� ���μ����� ã�Ҵٸ�
		else {
			// result�� �ش� ���μ����� �߰��ϰ�
			result << "P" << index << '\t';
			// �� ���μ����� ���� �ڿ��� ��ȯ�� ��
			deallocate(allocation[index], work, resourceNum);
			// �ش� ���μ����� �����ٰ� ǥ��
			finish[index] = true;
		}
	}
	// safe sequence ���
	cout << result.str() << endl;
	// ���� �Ҵ��� �޸� ����
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

	return 0;
}

//need<=work���� ��ȯ���ִ� �Լ�
bool isAvailable(int need[], int work[], int resourceNum) {
	// ������ �ڿ��� ����
	for (int i = 0; i < resourceNum; i++) {
		// �ѹ��̶� need > work���
		if (need[i] > work[i]) {
			//false ��ȯ
			return false;
		}
	}
	// ��� �ڿ��� ���� need <= work�̸� true ��ȯ
	return true;
}

//��� ���μ������� �������� ��ȯ���ִ� �Լ�
bool allFinished(bool finish[], int processNum) {
	// ������ ���μ����鿡 ����
	for (int i = 0; i < processNum; i++) {
		// �۾��� �Ϸ���� ���� ���μ����� �ִٸ�
		if (finish[i] == false) {
			//false ��ȯ
			return false;
		}
	}
	// ��� ���μ������� �����ٸ� true ��ȯ
	return true;
}

//�۾��� �Ϸ�� ���μ����� �ڿ��� work�� �߰����ִ� �Լ�
void deallocate(int allocation[], int work[], int resourceNum) {
	// �ش� ���μ����� �Ҵ�� ��� �ڿ��� ����
	for (int i = 0; i < resourceNum; i++) {
		// work�� allocation�� ���� ����
		work[i] += allocation[i];
	}
	return;
}