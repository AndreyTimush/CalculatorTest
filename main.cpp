#include <getopt.h>
#include <unistd.h>

#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "mathlib.h"

struct Task {
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

bool errVal = false;

int main(int argc, char *argv[]) { runner(argc, argv); }

void runner(int argc, char *argv[]) {
    Task task{};
    parser(argc, argv, task);
    if (!task.value1) return;
    calculate(task);
    print(task);
}

void parser(int argc, char *argv[], Task &task) {
    int opt;

    int c;
    int option_index                    = 0;
    static struct option long_options[] = {{"help", no_argument, 0, 'h'}, {0, 0, 0, 0}};

    while (true) {
        c = getopt_long(argc, argv, "h", long_options, &option_index);

        if (c == -1) break;  // Конец опций

        switch (c) {
            case 'h':
                printHelp();
                return;
            default:
                printf("Неожиданный код: %d\n", c);
                printf("Для отрицательных чисел используйте '--'\n");
                printf("Пример: ./calculator -- -5 + 3\n");
                return;
        }
    }

    if (argc - optind < 2) {
        printf("Недостаточно аргументов\n");
        errVal = true;
        return;
    }

    char *str1 = argv[optind];
    char *str2 = argv[optind + 1];
    char *str3 = nullptr;

    if (argc - optind == 3) {
        str3 = argv[optind + 2];
    } else if (argc - optind == 2) {
        str3 = nullptr;
    } else {
        errVal = true;
        printf("Слишком много аргументов");
        return;
    }

    checkData(str1, str2, str3, task);
}

void checkData(char *arg1, char *arg2, char *arg3, Task &task) {
    errno = 0;
    if ((strlen(arg1) > 10) || (arg3 != nullptr && strlen(arg3) > 10)) {
        errVal = true;
        printf("Ошибка: число слишком большое\n");
        return;
    }

    if (arg1[0] == '0') {
        task.value1 = 0;
    } else {
        int a = atoi(arg1);
        if (errno == ERANGE || a > INT_MAX || a < INT_MIN) {
            errVal = true;
            printf("Ошибка: число выходит за пределы допустимого диапазона\n");
            return;
        }
        if (a == 0) {
            errVal = true;
            printf("Ошибка, надо ввести целое число\n");
            return;
        } else {
            task.value1 = a;
        }
    }
    char operation = arg2[0];

    switch (operation) {
        case '+':
        case '-':
        case 'x':
        case '/':
        case '^':
        case '!':
            task.operation = operation;
            break;
        default:
            errVal = true;
            printf("Ошибка, введите валидную операцию");
            return;
    }

    if (task.value1 < 0 && task.operation == '!') {
        errVal = true;
        printf("Факториал отрицательного числа не определен!\n");
        return;
    }

    if (arg3 != nullptr) {
        if (arg3[0] == '0') {
            task.value2 = 0;
        } else {
            int b = atoi(arg3);
            if (errno == ERANGE || b > INT_MAX || b < INT_MIN) {
                errVal = true;
                printf("Ошибка: число выходит за пределы допустимого диапазона\n");
                return;
            }
            if (b == 0) {
                errVal = true;
                printf("Ошибка, надо ввести целое число");
                return;
            } else {
                task.value2 = b;
            }
        }
    }
}

void calculate(Task &task) {
    switch (task.operation) {
        case '+':
            task.result = mathlib::sum(task.value1, task.value2);
            break;
        case '-':
            task.result = mathlib::subtraction(task.value1, task.value2);
            break;
        case 'x':
            task.result = mathlib::multiply(task.value1, task.value2);
            break;
        case '/':
            task.result = mathlib::division(task.value1, task.value2);
            break;
        case '^':
            task.result = mathlib::pow(task.value1, task.value2);
            break;
        case '!':
            task.result = mathlib::factorial(task.value1);
            break;
        default:
            errVal = true;
            printf("Неверная операция");
            break;
    }
}

void print(Task &task) {
    if (!mathlib::isError && !errVal)
        printf("%d %c %d = %f\n", task.value1, task.operation, task.value2, task.result);
}

void printHelp() {
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
