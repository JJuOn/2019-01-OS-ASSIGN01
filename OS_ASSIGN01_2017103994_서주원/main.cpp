#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>

using namespace std;

//need<=work인지 반환해주는 함수
bool isAvailable(int need[], int work[], int resourceNum);
//모든 프로세스들이 끝났는지 반환해주는 함수
bool allFinished(bool finish[], int processNum);
//작업이 완료된 프로세스의 자원을 work에 추가해주는 함수
void deallocate(int allocation[], int work[], int resourceNum);

int main() {
	int processNum = 0, resourceNum = 0;// 프로세스의 개수 processNum, 자원의 종류의 개수 resourceNum
	// 프로세스들이 갖고 있는 자원의 상태를 나타낼 allocation, 프로세스들이 특정 순간에 최대로 필요로 하는 자원의 개수를 나타낼 max, max - allocation이 저장될 need
	int **allocation = NULL, **max = NULL, **need = NULL;   
	int *work=NULL;// 현재 이용가능한 자원의 개수를 나타낼 work
	bool *finish = NULL; // 프로세스들이 작업이 끝났는 지 알려줄 finish
	//프로세스의 개수 입력
	cout << "Enter the number of processes : ";
	cin >> processNum;
	// 프로세스의 개수가 3개 미만이거나 10개 이상이면 재입력 
	while (processNum < 3 || processNum >=10) {
		cout << "Enter the number of processes again : ";
		cin >> processNum;
	}
	// 자원의 종류 개수 입력
	cout << "Enter the number of resource types : ";
	cin >> resourceNum;
	// 자원의 종류의 개수가 10개 이상이면 재입력
	while (resourceNum >= 10) {
		cout << "Enter the number of resource types again : ";
		cin >> resourceNum;
	}
	// 프로세스 개수만큼의 배열 동적 할당
	allocation = new int*[processNum];
	max = new int*[processNum];
	need = new int*[processNum];
	for (int i = 0; i < processNum; i++) {
		//allocation, max, need는 2차원 배열이므로, 추가로 동적 할당
		allocation[i] = new int[resourceNum];
		max[i] = new int[resourceNum];
		need[i] = new int[resourceNum];
		//work는 1차원 배열이므로 동적 할당
		work = new int[resourceNum];
	}
	// 각각의 프로세스에 대해서 현재 할당 상태 입력
	for (int i = 0; i < processNum; i++) {
		cout << "Enter allocation of process" << i << " : ";
		for (int j = 0; j < resourceNum; j++) {
			cin >> allocation[i][j];
		}
	}
	int opr;
	// 사용자는 MAX를 입력할 지 NEED를 입력할 지 선택할 수 있음 
	cout << "What do you want to enter? (1: MAX, 2:NEED) : ";
	cin >> opr;
	// MAX를 입력할 시
	if (opr == 1) {
		// 각각의 프로세스들에 대하여 
		for (int i = 0; i < processNum; i++) {
			//max 값을 입력 받고
			cout << "Enter max of process" << i << " : ";
			for (int j = 0; j < resourceNum; j++) {
				cin >> max[i][j];
				// max - allocation 한 값을 need에 저장
				need[i][j] = max[i][j] - allocation[i][j];
			}
		}
	}
	// NEED를 바로 입력할 시
	else {
		// 각각의 프로세스들에 대하여
		for (int i = 0; i < processNum; i++) {
			// need 값을 입력 받아 저장
			cout << "Enter need of process" << i << " : ";
			for (int j = 0; j < resourceNum; j++) {
				cin >> need[i][j];
			}
		}
	}
	// 현재 사용가능한 자원의 개수 입력
	cout << "Enter available(work) : ";
	for (int i = 0; i < resourceNum; i++) {
		cin >> work[i];
	}
	// 프로세스들의 작업 완료 상태를 알려주기 위한 finish 동적 할당
	finish = new bool[processNum];
	// 초기값은 false로 설정
	for (int i = 0; i < processNum; i++) {
		finish[i] = false;
	}
	// safe sqeuence를 출력하기위한 result
	stringstream result;
	// 끝나지 않은 프로세스가 있을 때,
	while (!allFinished(finish,processNum)) {
		// 다음 조건을 만족시키는 i를 찾아 저장할 index
		int index = -1;
		// 각각의 프로세스에 대해
		for (int i = 0; i < processNum; i++) {
			// 작업이 완료되지 않았고, 동시에 need <= work이면
			if (!finish[i] && isAvailable(need[i], work, resourceNum)) {
				// index에 i를 저장
				index = i;
				break;
			}
		}
		// 만일 위 조건을 만족하는 프로세스를 찾지 못했다면
		if (index == -1) {
			// safe sequence가 없다고 판단
			cout << "No Safe Sequence" << endl;
			// 프로그램 종료
			return 0;
		}
		// 위 조건을 만족하는 프로세스를 찾았다면
		else {
			// result에 해당 프로세스를 추가하고
			result << "P" << index << '\t';
			// 이 프로세스가 가진 자원을 반환한 후
			deallocate(allocation[index], work, resourceNum);
			// 해당 프로세스가 끝났다고 표시
			finish[index] = true;
		}
	}
	// safe sequence 출력
	cout << result.str() << endl;
	// 동적 할당한 메모리 해제
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

//need<=work인지 반환해주는 함수
bool isAvailable(int need[], int work[], int resourceNum) {
	// 각각의 자원에 대해
	for (int i = 0; i < resourceNum; i++) {
		// 한번이라도 need > work라면
		if (need[i] > work[i]) {
			//false 반환
			return false;
		}
	}
	// 모든 자원에 대해 need <= work이면 true 반환
	return true;
}

//모든 프로세스들이 끝났는지 반환해주는 함수
bool allFinished(bool finish[], int processNum) {
	// 각각의 프로세스들에 대해
	for (int i = 0; i < processNum; i++) {
		// 작업이 완료되지 않은 프로세스가 있다면
		if (finish[i] == false) {
			//false 반환
			return false;
		}
	}
	// 모든 프로세스들이 끝났다면 true 반환
	return true;
}

//작업이 완료된 프로세스의 자원을 work에 추가해주는 함수
void deallocate(int allocation[], int work[], int resourceNum) {
	// 해당 프로세스에 할당된 모든 자원에 대해
	for (int i = 0; i < resourceNum; i++) {
		// work에 allocation의 값을 더함
		work[i] += allocation[i];
	}
	return;
}