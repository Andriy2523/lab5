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
        cout << "�����: " << word << "\n�������: ";
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
        cout << "��������: " << context << "\n����� �����: " << row << "\n����� ������: " << paragraph << "\n����� �����: " << bookTitle << endl;
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    vector<Index*> indexEntries;
    int choice;

    while (true) {
        cout << "\n����:\n";
        cout << "1. ������ �����\n";
        cout << "2. �������� �����\n";
        cout << "3. ������� ���������� ��� �� ������\n";
        cout << "4. �����\n";
        cout << "������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string word, context, bookTitle;
            vector<int> pages;
            int page, row, paragraph;

            cout << "������ ����� �����: ";
            cin.ignore();
            getline(cin, bookTitle);

            cout << "������ �����: ";
            getline(cin, word);

            cout << "������ ������ ������� (������ -1 ��� ����������): ";
            while (true) {
                cin >> page;
                if (page == -1) break;
                pages.push_back(page);
            }

            cout << "������ ����� ������: ";
            cin >> paragraph;

            cout << "������ ����� ����� ������: ";
            cin >> row;

            cout << "������ �������, �� ����������� �����: ";
            cin.ignore();
            getline(cin, context);

            indexEntries.push_back(new AdvancedIndex(word, pages, context, row, paragraph, bookTitle));
            cout << "����� ������ ������!\n";
            break;
        }
        case 2: {
            if (!indexEntries.empty()) {
                cout << "������ ������ ������, ���� �� ������ ��������: ";
                int index;
                cin >> index;

                if (index >= 0 && index < indexEntries.size()) {
                    delete indexEntries[index];
                    indexEntries.erase(indexEntries.begin() + index);
                    cout << "����� �������� ������!\n";
                }
                else {
                    cout << "�������� ������ ������!\n";
                }
            }
            else {
                cout << "���� ������ ��� ���������!\n";
            }
            break;
        }
        case 3: {
            if (!indexEntries.empty()) {
                cout << "\n���������� ��� �� ������:\n";
                for (int i = 0; i < indexEntries.size(); ++i) {
                    cout << "����� " << i + 1 << ":\n";
                    indexEntries[i]->display();
                    cout << endl;
                }
            }
            else {
                cout << "���� ������ ��� �����������!\n";
            }
            break;
        }
        case 4: {
            cout << "�� ���������!\n";
            for (int i = 0; i < indexEntries.size(); ++i) {
                delete indexEntries[i];
            }
            return 0;
        }
        default:
            cout << "������� ���� �����. ��������� �� ���.\n";
        }
    }
}
