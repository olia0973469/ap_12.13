#include <iostream>
#include <string>

using namespace std;

struct Student {
    string surname;
    int exam1;
    int exam2;
    int exam3;
};

const int TABLE_SIZE = 100;

class OpenHashTable {
private:
    struct Node {
        Student student;
        Node* next;

        Node(const Student& s) : student(s), next(nullptr) {}
    };

    Node* table[TABLE_SIZE];

    int hash(const string& key) const {
        const int p = 31;
        const int m = TABLE_SIZE;
        int hash_value = 0;
        int p_pow = 1;
        for (char ch : key) {
            hash_value = (hash_value + (ch - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash_value;
    }

public:
    OpenHashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    void insert(const Student& student) {
        int index = hash(student.surname);
        Node* new_node = new Node(student);

        if (!table[index]) {
            table[index] = new_node;
        }
        else {
            Node* current = table[index];
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    void remove(const string& surname) {
        int index = hash(surname);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->student.surname == surname) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    table[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void edit(const string& surname, const Student& updated_student) {
        int index = hash(surname);
        Node* current = table[index];

        while (current) {
            if (current->student.surname == surname) {
                current->student = updated_student;
                return;
            }
            current = current->next;
        }
    }

    void display() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current) {
                cout << "Surname: " << current->student.surname
                    << ", Exam1: " << current->student.exam1
                    << ", Exam2: " << current->student.exam2
                    << ", Exam3: " << current->student.exam3 << "\n";
                current = current->next;
            }
        }
    }
};

int main() {
    OpenHashTable hash_table;
    int choice;
    do {
        cout << "\n====== Menu ======\n";
        cout << "1. Add a student\n";
        cout << "2. Remove a student\n";
        cout << "3. Edit a student's grades\n";
        cout << "4. Display all students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string surname;
        Student student;

        switch (choice) {
        case 1:
            cout << "Enter surname: ";
            cin >> student.surname;
            cout << "Enter exam1 grade: ";
            cin >> student.exam1;
            cout << "Enter exam2 grade: ";
            cin >> student.exam2;
            cout << "Enter exam3 grade: ";
            cin >> student.exam3;
            hash_table.insert(student);
            break;
        case 2:
            cout << "Enter surname of student to remove: ";
            cin >> surname;
            hash_table.remove(surname);
            break;
        case 3:
            cout << "Enter surname of student to edit: ";
            cin >> surname;
            cout << "Enter new exam1 grade: ";
            cin >> student.exam1;
            cout << "Enter new exam2 grade: ";
            cin >> student.exam2;
            cout << "Enter new exam3 grade: ";
            cin >> student.exam3;
            student.surname = surname;
            hash_table.edit(surname, student);
            break;
        case 4:
            hash_table.display();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
