// Kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma warning(disable:4996)
#include <stdio.h>
#include <locale.h>
#include <string.h>
#define ENG 26
#define RUS 32

struct avaliable {
    int area;
    int price;
    int id;
    int district_id;
    char street[50];
    char town[50];
    int type;//1-Сельхоз 2-нас.пункт 3-промышленность 4-особо охран. объектов 5-земли лесного фонда 6 - водного запаса, 7-запас.
};
struct owner {
    int id;
    int siteID;
    char surname[50];
    char name[50];
    int birthYear;
    char town[50];
};
struct registered {
    int area;
    int id;
    int district_id;
    owner _owner;
    int type;
};
const char* avaliable_file;
const char* input;
const char* registred_file;
const char* logins_pass;

void reg();
void encrypt(const char* logins);
void decrypt(const char* logins);
void login();

int main()
{
    setlocale(LC_ALL, "Russian");

    avaliable_file = "avaliable.bat";
    registred_file = "registred.bat";
    logins_pass = "loging_pass.txt";
    reg();
    login();

}

void reg() {
    FILE* regs;
    char login[30];
    char pass[30];
    regs = fopen("timereg.txt", "w+");
    printf("Введите логин: ");
    gets_s(login);
    printf("Введите пароль: ");
    gets_s(pass);
    fprintf(regs, "%s %s\n", login, pass);
    fclose(regs);
    encrypt(logins_pass);
}
void login() {
    FILE* logs;
    logs = fopen("timelog.txt", "w+");
    char login[30];
    char pass[30];
    char logstr[70];
    char decstr[70];
    printf("Введите логин: ");
    gets_s(login);
    printf("Введите пароль: ");
    gets_s(pass);
    fprintf(logs, "%s %s\n", login, pass);
    fread(logstr, sizeof(logstr), 1, logs);
    printf("%s", logstr);
    decrypt(logins_pass);
    FILE* decrypted;
    decrypted = fopen("decrypted.txt", "r");
    while (!feof(decrypted)) {
        fread(decstr, sizeof(decstr), 1, decrypted);
        if (strcmp(decstr, logstr) == 0) {
            printf("Loggined");
            break;
        }
        else printf("No string");
    }


};

void encrypt(const char* logins) {
    int n = 1, flag;
    char c;
    FILE* from, *passes;
    from = fopen("timereg.txt", "r");
    passes = fopen(logins, "a+");
    c = getc(from);
    while (!feof(from))
    {
        flag = 0;
        if (c >= 'A' && c <= 'Z') {
            c = c + (n % ENG);
            if (c > 'Z') c = 'A' + (c - 'Z') - 1;
            fprintf(passes, "%c", c);
            flag = 1;
        }
        if (c >= 'a' && c <= 'z')
        {
            c = c + (n % ENG);
            if (c > 'z') c = 'a' + (c - 'z') - 1;
            fprintf(passes, "%c", c);
            flag = 1;
        }
        if (c >= 'А' && c <= 'Я')
        {
            c = c + (n % RUS);
            if (c > 'Я') c = 'А' + (c - 'Я') - 1;
            fprintf(passes, "%c", c);
            flag = 1;
        }
        if (c >= 'а' && c <= 'я')
        {
            c = c + (n % RUS);
            if (c > 'я') c = 'а' + (c - 'я') - 1;
            fprintf(passes, "%c", c);
            flag = 1;
        }
        if (!flag) fprintf(passes, "%c", c);
        c = getc(from);
    }
    fclose(from);
    fclose(passes);

};
void decrypt(const char* logins) {
    int n = 1, flag;
    char c;
    FILE* from, * passes_decr;
    passes_decr = fopen("decrypted.txt", "w+");
    from = fopen(logins, "a+");
    c = getc(from);
    while (!feof(from))
    {
        flag = 0;
        if (c >= 'A' && c <= 'Z') {
            c = c - (n % ENG);
            if (c > 'Z') c = 'A' - (c - 'Z') - 1;
            fprintf(passes_decr, "%c", c);
            flag = 1;
        }
        if (c >= 'a' && c <= 'z')
        {
            c = c - (n % ENG);
            if (c > 'z') c = 'a' - (c - 'z') - 1;
            fprintf(passes_decr, "%c", c);
            flag = 1;
        }
        if (c >= 'А' && c <= 'Я')
        {
            c = c - (n % RUS);
            if (c > 'Я') c = 'А' - (c - 'Я') - 1;
            fprintf(passes_decr, "%c", c);
            flag = 1;
        }
        if (c >= 'а' && c <= 'я')
        {
            c = c - (n % RUS);
            if (c > 'я') c = 'а' - (c - 'я') - 1;
            fprintf(passes_decr, "%c", c);
            flag = 1;
        }
        if (!flag) fprintf(passes_decr, "%c", c);
        c = getc(from);
    }
    fclose(from);
    fclose(passes_decr);

};

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
