OS_ASSIGN01_2017103994_서주원 README.txt

1. 프로그램이 시작되면 다음과 같은 메세지가 출력됩니다.

Enter the number of processes :

그러면 다음과 같이 3 이상 10 미만의 프로세스의 전체 개수를 입력해 주시면 됩니다.

Enter the number of processes : 5

2. 자원의 타입의 개수를 물어보는 메시지가 출력됩니다. 이때, 자원의 타입의 개수는 10개 미만이어야 합니다.

Enter the number of resource types :

자원의 타입을 수업시간의 예제와 같이 3개(A, B, C)로 정하고 3을 입력하겠습니다.

Enter the number of resource types : 3

3. 각각의 프로세스에 대해 현재 할당 상태(allocation)을 묻는 메세지가 출력되면 다음과 같이 입력해 주시면 됩니다.

Enter allocation of process0 : 0 1 0
Enter allocation of process1 : 2 0 0
Enter allocation of process2 : 3 0 2
Enter allocation of process3 : 2 1 1
Enter allocation of process4 : 0 0 2

위 예시에서는 스페이스바를 이용하여 프로세스 안의 자원끼리 구분지었습니다.

4. 다음과 같은 메세지가 출력되었을 때 MAX를 입력하시길 원하시면 1을, NEED를 입력하시길 원하시면 2를 입력해 주세요.

What do you want to enter? (1: MAX, 2:NEED) :

5-1. What do you want to enter? (1: MAX, 2:NEED) : 1

4번에서 1을 입력하시면 프로세스가 최대로 요구하는 자원의 개수(max)를 묻는 메세지가 출력됩니다. 다음과 같이 입력해 주세요.

Enter max of process0 : 7 5 3
Enter max of process1 : 3 2 2
Enter max of process2 : 9 0 2
Enter max of process3 : 2 2 2
Enter max of process4 : 4 3 3

3번에서와 마찬가지로 스페이스바를 이용하여 자원의 개수를 구분지었습니다.

5-2. What do you want to enter? (1: MAX, 2:NEED) : 2
4번에서 2을 입력하시면 프로세스가 자원을 최대로 요구할 때, 필요한 자원의 개수(need)를 묻는 메세지가 출력됩니다. 다음과 같이 입력해 주세요.

Enter need of process0 : 7 4 3
Enter need of process1 : 1 2 2
Enter need of process2 : 6 0 0
Enter need of process3 : 0 1 1
Enter need of process4 : 4 3 1

3번에서와 마찬가지로 스페이스바를 이용하여 자원의 개수를 구분지었습니다.

6. 마지막으로 현재 사용가능한 자원의 상태(available 또는 work)를 묻는  메세지가 출력되면 다음과 같이 입력해 주세요.

Enter available(work) : 3 3 2

입력방법은 이전과 동일합니다.

7. 모든 입력을 마치면 safe sequence가 있으면 다음과 같이 safe sequence를,

P1      P3      P0      P2      P4

safe sequence가 존재하지 않으면 

No Safe Sequence

를 출력하면서 프로그램이 종료됩니다.
