#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

class Index {
protected:
    string word;
    vector<int> pages;

public:
    Index(const string& word, const vector<int>& pages) : word(word), pages(pages) {}

    void addPage(int page) {
        pages.push_back(page);
    }

    void removePage(int page) {
        pages.erase(remove(pages.begin(), pages.end(), page), pages.end());
    }

    void display() const {
        cout << "Слово: " << word << "\nСторінки: ";
        for (int page : pages) {
            cout << page << " ";
        }
        cout << endl;
    }
};

class AdvancedIndex : public Index {
private:
    string context;
    int row;
    int paragraph;
    string bookTitle;

public:
    AdvancedIndex(const string& word, const vector<int>& pages, const string& context, int row, int paragraph, const string& bookTitle)
        : Index(word, pages), context(context), row(row), paragraph(paragraph), bookTitle(bookTitle) {}

    void display() const {
        Index::display();
        cout << "Контекст: " << context << "\nНомер рядка: " << row << "\nНомер абзацу: " << paragraph << "\nНазва книги: " << bookTitle << endl;
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    vector<Index*> indexEntries;
    int choice;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Додати запис\n";
        cout << "2. Видалити запис\n";
        cout << "3. Вивести інформацію про всі записи\n";
        cout << "4. Вийти\n";
        cout << "Виберіть опцію: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string word, context, bookTitle;
            vector<int> pages;
            int page, row, paragraph;

            cout << "Введіть назву книги: ";
            cin.ignore();
            getline(cin, bookTitle);

            cout << "Введіть слово: ";
            getline(cin, word);

            cout << "Введіть номери сторінок (введіть -1 для завершення): ";
            while (true) {
                cin >> page;
                if (page == -1) break;
                pages.push_back(page);
            }

            cout << "Введіть номер абзацу: ";
            cin >> paragraph;

            cout << "Введіть номер рядка абзацу: ";
            cin >> row;

            cout << "Введіть речення, де знаходиться слово: ";
            cin.ignore();
            getline(cin, context);

            indexEntries.push_back(new AdvancedIndex(word, pages, context, row, paragraph, bookTitle));
            cout << "Запис додано успішно!\n";
            break;
        }
        case 2: {
            if (!indexEntries.empty()) {
                cout << "Введіть індекс запису, який ви хочете видалити: ";
                int index;
                cin >> index;

                if (index >= 0 && index < indexEntries.size()) {
                    delete indexEntries[index];
                    indexEntries.erase(indexEntries.begin() + index);
                    cout << "Запис видалено успішно!\n";
                }
                else {
                    cout << "Недійсний індекс запису!\n";
                }
            }
            else {
                cout << "Немає записів для видалення!\n";
            }
            break;
        }
        case 3: {
            if (!indexEntries.empty()) {
                cout << "\nІнформація про всі записи:\n";
                for (int i = 0; i < indexEntries.size(); ++i) {
                    cout << "Запис " << i + 1 << ":\n";
                    indexEntries[i]->display();
                    cout << endl;
                }
            }
            else {
                cout << "Немає записів для відображення!\n";
            }
            break;
        }
        case 4: {
            cout << "До побачення!\n";
            for (int i = 0; i < indexEntries.size(); ++i) {
                delete indexEntries[i];
            }
            return 0;
        }
        default:
            cout << "Невірний вибір опції. Спробуйте ще раз.\n";
        }
    }
}
