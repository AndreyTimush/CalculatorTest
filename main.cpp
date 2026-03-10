#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include "mathlib.h"

struct Task
{
	int value1;
	int value2;
	char operation;
	float result;
};

void runner(int argc, char *argv[]);
void parser(int argc, char *argv[], Task &task);
void checkData(char *arg1, char *arg2, char *arg3, Task &task);
void calculate(Task &task);
void print(Task &task);
void printHelp();

int main(int argc, char *argv[])
{
	runner(argc, argv);
}

void runner(int argc, char *argv[]) 
{
	Task task;
	parser(argc, argv, task);
	calculate(task);
//	print(task);
}

void parser(int argc, char *argv[], Task &task) 
{
	int opt;
	while ((opt = getopt(argc, argv, "h")) != -1) {
                switch(opt) {
                        case 'h':
                                printHelp();
                                break;
                        default:
                                printf("Неожиданный код: %d\n", opt);
                                break;
                }
        }

	if (argc - optind < 2) {
		printf("Недостаточно аргументов\n");
		return;
	}

	char *str1 = argv[optind];
	char *str2 = argv[optind + 1];
	char *str3 = nullptr;
	printf("asdasd %d", argc - optind);
	if (argc - optind == 3) {
		str3 = argv[optind + 2];
	} else if (argc - optind == 2){
		str3 = nullptr;
	} else {
		printf("Слишком много аргументов");
		return;
	}

	checkData(str1, str2, str3, task);
}

void checkData(char *arg1, char *arg2, char *arg3, Task &task)
{
	if (arg1[0] == '0') {
		task.value1 = 0;
	} else {
		int a = atoi(arg1);
		if (a == 0) {
			printf("Ошибка, надо ввести целое число\n");
			return;
		} else {
			task.value1 = a;
		}
	}
	char operation = arg2[0];
	
	switch(operation) {
		case '+':
		case '-':
		case 'x':
		case '/':
		case '^':
		case '!':
			task.operation = operation;
			break;
		default:
			printf("Ошибка, введите валидную операцию");
			return;
	}

	if (arg3 != nullptr) {
		if (arg3[0] == '0') {
			task.value2 = 0;
		} else {	
			int b = atoi(arg3);
			if (b == 0) {
				printf("Ошибка, надо ввести целое число");
				return;
			} else {
				task.value2 = b;
			}
		}
	}
	printf("Число 1: %d\n", task.value1);
	printf("Операция: %c\n", task.operation);
	printf("Число 2: %d\n", task.value2);
}

void calculate(Task &task)
{

}

void printHelp()
{
	printf("Калькулятор v1.0\n");
	printf("Использование: calculator [опции] [число1] [операция] [число2]\n");
	printf("Опции:\n");
	printf("  -h    Показать эту справку\n");
	printf("Операции:\n");
	printf("  +  сложение\n");
	printf("  -  вычитание\n");
	printf("  x  умножение\n");
	printf("  /  деление\n");
	printf("  ^  возведение в степень\n");
	printf("  !  факториал (требуется только одно число)\n");
	printf("Примеры:\n");
	printf("  calculator 5 + 3 \n");
	printf("  calculator 5 !\n");
}
