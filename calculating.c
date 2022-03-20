#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#define BUFSIZ 512

typedef struct
{
	int id;
	char string[512];
} msg;

void difference(char* max, char* min, char* res, int length, int minlength, int mFlag) {
	int imin = 0;
	int imax = 0;
	int jx = 0;
	for (imin = minlength, imax = length; imin != -1; imin--, imax--) {
		if (max[imax] < min[imin]) {
			max[imax - 1]--;
			res[jx] = 10 + max[imax] - min[imin] + '0';
		}
		else {
			res[jx] = max[imax] - min[imin] + '0';
		}
		jx++;


	}

	for (imax = length - minlength - 1; imax != -1; imax--) {
		res[jx] = max[imax];
		jx++;
	}
}
void columnPlus(char* num1, char* num2, int size1, int size2) {
	int vUme = 0;
	int i = 0;
	int reverseI = 0;
	char temp[BUFSIZ];
	if (size1 == 0) {
		for (i = 0; num2[i] != '\0'; i++) {
			num1[i] = num2[i];

		}
		return;
	}
	else if (size2 == 0) {
		return;
	}
	if (size1 >= size2) {
		while (size2 >= 0) {
			temp[i] = (num1[size1] - '0') + (num2[size2] - '0');
			if (vUme) {
				temp[i]++;
				vUme--;
			}
			size1--;
			size2--;
			if (temp[i] > 9) {
				temp[i] = temp[i] - 10;
				vUme++;
			}
			i++;
		}
		while (size1 >= 0) {
			temp[i] = num1[size1] - '0';
			if (vUme) {
				temp[i]++;
				vUme--;
			}
			size1--;
			if (temp[i] > 9) {
				temp[i] = temp[i] - 10;
				vUme++;
			}
			i++;
		}
		if (vUme) {
			temp[i] = 1;
			i++;
		}

	}
	else if (size1 < size2) {
		while (size1 >= 0) {
			temp[i] = (num1[size1] - '0') + (num2[size2] - '0');
			if (vUme) {
				temp[i]++;
				vUme--;
			}
			size1--;
			size2--;
			if (temp[i] > 9) {
				temp[i] = temp[i] - 10;
				vUme++;
			}
			i++;
			printf(" PROMESHUTOK : %c\n", temp[i] + '0');
		}
		while (size2 >= 0) {
			temp[i] = num2[size2] - '0';
			if (vUme) {
				temp[i]++;
				vUme--;
			}
			size2--;
			if (temp[i] > 9) {
				temp[i] = temp[i] - 10;
				vUme++;
			}
			i++;
		}
		if (vUme) {
			temp[i] = 1;
			i++;
		}
	}
	temp[i] = '\0';
	reverseI = i - 1;
	for (i = 0; reverseI != -1; i++) {
		num1[i] = temp[reverseI] + '0';
		reverseI--;
	}
	printf("ANSWER FROM COLUMN FUNC : %s\n", num1);

}
void columnMultiplication(char* num1, char* num2, int size1, int size2) {
	int vUme = 0;
	int sizeOfRes = 0;
	char tempReverse[BUFSIZ];
	int sizeOfTempReverse = 0;
	int sizeOfTemp = 0;
	char temp[BUFSIZ];
	char result[BUFSIZ];
	int flag = 0;
	int i = 0, j = 0, k = 0, g = 0, zeroCounter = 0;
	for (i = size1; i != -1; i--) {

		for (j = size2; j != -1; j--) {
			tempReverse[k] = (num1[i] - '0') * (num2[j] - '0');
			if (vUme) {
				tempReverse[k] += vUme;
				vUme = 0;
			}
			if (tempReverse[k] > 9) {
				vUme = tempReverse[k] / 10;
				tempReverse[k] = tempReverse[k] % 10 + '0';
			}
			else {
				tempReverse[k] += '0';
			}
			k++;
		}
		if (vUme) {
			tempReverse[k] = vUme;
			vUme = 0;
		}
		for (sizeOfTempReverse = k - 1; sizeOfTempReverse != -1; sizeOfTempReverse--) {
			if ((flag == 0) && (tempReverse[sizeOfTempReverse] == '0')) {
				continue;
			}
			else {
				flag = 1;
				temp[sizeOfTemp] = tempReverse[sizeOfTempReverse];
				sizeOfTemp++;
			}
		}
		while (zeroCounter != g) {
			temp[sizeOfTemp] = '0';
			zeroCounter++;
			sizeOfTemp++;
		}
		zeroCounter = 0;
		temp[sizeOfTemp] = '\0';
		columnPlus(result, temp, sizeOfRes, sizeOfTemp - 1);
		while (result[sizeOfRes + 1] != '\0') {
			sizeOfRes++;
		}
		memset(temp, 0, BUFSIZ);
		memset(tempReverse, 0, BUFSIZ);
		k = 0;
		sizeOfTemp = 0;
		sizeOfTempReverse = 0;
		g++;
	}
	for (i = 0; result[i] != '\0'; i++) {
		num1[i] = result[i];
	}
	num1[i] = '\0';
}
void columnSplit(char* num1, char* num2) {
	int vUme = 0;
}

char* columnMinus(char* num1, char* num2, int size1, int size2) {
	char temp[BUFSIZ];
	int mFlag = 0;
	char result[BUFSIZ];
	int i = 0, j = 0;
	int flag = 0;
	int k = 3; // если к == 3, значит числа одинаковой длинны
	int length = size1;
	if (size1 > size2)
	{
		length = size1;
		k = 1; // если к == 1, значит первое число длиннее второго
	}
	else
		if (size2 > size1)
		{
			mFlag = 1;
			length = size2;
			k = 2; // если к == 2, значит второе число длиннее первого
		}
		else {// если числа одинаковой длинны, то необходимо сравнить их веса
			for (int ix = 0; ix < length; ix++) // поразрядное сравнение весов чисел
			{
				if (num1[ix] > num2[ix]) // если разряд первого числа больше
				{
					k = 1; // значит первое число длиннее второго
					break; // выход из цикла for
				}

				if (num2[ix] > num1[ix]) // если разряд второго числа больше
				{
					k = 2; // значит второе число длиннее первого
					break; // выход из цикла for
				}

			} // конец for
		}
	if (k == 3) {
		num1[0] = '0';
		num1[1] = '\0';
	}
	if (k == 1) {
		difference(num1, num2, temp, length, size2, mFlag);
		for (i = length, j = 0; i != -1; i--) {
			if ((flag == 0) && (temp[i] == '0')) {
				continue;
			}
			else {
				flag = 1;
				num1[j] = temp[i];
				j++;
			}
		}
	}
	if (k == 2) {
		difference(num2, num1, temp, length, size1, mFlag);
		for (i = length, j = 0; i != -1; i--) {
			if (!j) {
				num1[j] = '-';
				j++;
			}
			if ((flag == 0) && (temp[i] == '0')) {
				continue;
			}
			else {
				num1[j] = temp[i];
				j++;
			}
		}
	}

	num1[j] = '\0';
}



char* makeCalculations(char* str) {
	char num1[BUFSIZ];
	char num2[BUFSIZ];
	int size1 = 0;
	int size2 = 0;
	char operation;
	int i, j;
	for (i = 0; str[i] != ' '; i++) {
		num1[i] = str[i];
	}
	size1 = i - 1;
	num1[i] = '\0';
	printf("num1 for work : %s\n", num1);

	i++;
	operation = str[i];
	i += 2;

	for (j = 0; str[i] != '\n'; j++, i++) {
		num2[j] = str[i];
	}
	size2 = j - 1;
	num2[j] = '\0';
	printf("num2 for work : %s\n", num2);
	printf("size1 for work : %d\n", size1);
	printf("size2 for work : %d\n", size2);
	switch (operation) {
	case '+':
		columnPlus(num1, num2, size1, size2);
		break;
	case'-':
		columnMinus(num1, num2, size1, size2);
		break;
	case'*':
		columnMultiplication(num1, num2, size1, size2);
		break;
	case'/':
		/*columnSplit(num1, num2);*/
		break;
	}
	str = num1;
	return str;
}

int main() {
	int semID, shmID, rc;
	int i;
	key_t semKey;
	struct sembuf ops[2];
	msg* message;
	void* segment;
	short semaphoreArr[2];
	semKey = ftok("./", 1);

	//GET SEMID
	printf("semKey is %d\n", semKey);
	printf("change check2\n");
	semID = semget(semKey, 2, 0666 | IPC_CREAT);
	printf("semID is %d\n", semID);
	semaphoreArr[0] = 0;
	semaphoreArr[1] = 1;

	if ((semctl(semID, 1, SETALL, semaphoreArr)) < 0) {
		perror("SEMCTL SETALL ");
		exit(-1);
	}

	//GET SHMID
	size_t siz = sizeof(message);
	if ((shmID = shmget(semKey, siz, 0666 | IPC_CREAT ) < 0)) {
		perror("SHMGET ");
		exit(-1);
	}

	printf("calc serv is work!\n");
	while (1) {
		ops[0].sem_num = 0;
		ops[0].sem_op = -1;
		ops[0].sem_flg = 0;

		ops[1].sem_num = 1;
		ops[1].sem_op = 0;
		ops[1].sem_flg = 0;
		if((rc = semop(semID, ops, 2) < 0)){
			perror("SEMOP 1 ");
			exit(-1);
		}
		printf("GOT MESSAGE : \n");

		//GET ACCESS TO FILLED SEGMENT AND SET MSG STRUCTURE
		if ((segment = shmat(shmID, NULL, 0)) < (void*)0) {
			perror("SHMAT ");
			exit(-1);
		}
		message = (msg*)segment;
		printf("this message is : %s\n", message->string);
		char* buf = makeCalculations(message->string);
		printf("answer from local server : %s\n", buf);
		for (i = 0; buf[i] != '\0'; i++) {
			message->string[i] = buf[i];
		}
		message->string[i] = '\0';
		printf("server send answer : %s", message->string);

		// PLUS UP ACCES TO MEMORY
		ops[0].sem_op = 1;
		ops[0].sem_flg = IPC_NOWAIT;
		ops[1].sem_op = 1;
		ops[1].sem_flg = IPC_NOWAIT;
		if ((semop(semID, ops, 2)) < 0) {
			perror("SEMOP 2 ");
			exit(-1);
		}
	}
}




