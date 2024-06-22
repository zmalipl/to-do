#include <iostream>
#include <fstream>
using namespace std;

const int MAX_TASKS = 100;
char tasks[MAX_TASKS][256];
bool status[MAX_TASKS];
int taskCount = 0;

void loadTasks() {
    ifstream file("tasks.txt");
    taskCount = 0;
    while (file.getline(tasks[taskCount], 256)) {
        if (tasks[taskCount][0] == '\0') continue;
        int len = strlen(tasks[taskCount]);
        if (tasks[taskCount][len - 1] == '*') {
            status[taskCount] = true;
            tasks[taskCount][len - 1] = '\0';
        } else {
            status[taskCount] = false;
        }
        taskCount++;
    }
    file.close();
}

void saveTasks() {
    ofstream file("tasks.txt");
    for (int i = 0; i < taskCount; i++) {
        file << tasks[i];
        if (status[i]) {
            file << "*";
        }
        file << endl;
    }
    file.close();
}

void printTasks() {
    cout << "Zadania do wykonania:\n";
    for (int i = 0; i < taskCount; i++) {
        cout << i + 1 << ". " << tasks[i];
        if (status[i]) {
            cout << " (wykonane)";
        }
        cout << endl;
    }
}

int main() {
    loadTasks();
    int choice;

    do {
        cout << "\nWitaj w aplikacji zarządzającej zadaniami!" << endl;
        printTasks();
        cout << "\n1. Dodaj zadanie" << endl;
        cout << "2. Oznacz zadanie jako wykonane" << endl;
        cout << "3. Usuń wykonane zadania" << endl;
        cout << "0. Zamknij aplikację" << endl;
        cout << "Wybierz opcję: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                if (taskCount < MAX_TASKS) {
                    cout << "Wpisz zadanie: ";
                    cin.getline(tasks[taskCount], 256);
                    status[taskCount] = false;
                    taskCount++;
                    saveTasks();
                }
                break;
            }
            case 2: {
                printTasks();
                cout << "Podaj numer zadania do oznaczenia jako wykonane: ";
                int num;
                cin >> num;
                if (num > 0 && num <= taskCount) {
                    status[num - 1] = true;
                    saveTasks();
                }
                break;
            }
            case 3: {
                int newCount = 0;
                for (int i = 0; i < taskCount; i++) {
                    if (!status[i]) {
                        strcpy(tasks[newCount], tasks[i]);
                        status[newCount] = false;
                        newCount++;
                    }
                }
                taskCount = newCount;
                saveTasks();
                break;
            }
        }
    } while (choice != 0);

    return 0;
}