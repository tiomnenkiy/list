#include <iostream>
#include <stdio.h>
#include <string.h>
#include "list.h"

using namespace std;

template <typename type>
class CList {
    struct list {
        type info;
        struct list *next;
    };
    struct list *head;
    struct list *tail;

public:
    CList() {
        head=nullptr;
        tail=nullptr;
    };
    ~CList() {
        ReleaseList();
    };
    void AddItem(type); //для типов int, double, char*
    void AddItem(); // нужно создавать CListRemoveIfOddValue сразу в списке, иначе он будет удаляться 2 раза: в конце main и вместе со списком
    void DisplayList();
    void ReleaseList();
    bool Dublicate(type);
    template <typename T> friend ostream& operator << (ostream& output, CList<T>& c);
};

template <typename type>
void CList<type>::AddItem(type data) {
    struct list *newItem;
    newItem = new struct list;
    newItem->info = data; // реализовать перемещение?
    if (head==nullptr) {
        head=newItem;
        tail=newItem;
        head->next = nullptr;
    } else {
        tail->next = newItem;
        newItem->next = nullptr;
        tail = newItem;
    }
}


template <>
void CList<char*>::AddItem(char* data) {
    struct list *newItem;
    newItem = new struct list;
    strcpy(newItem->info, data);
    if (head==nullptr) {
        head=newItem;
        tail=newItem;
        head->next = nullptr;
    } else {
        tail->next = newItem;
        newItem->next = nullptr;
        tail = newItem;
    }
}


template <>
void CList<CListRemoveIfOddValue>::AddItem() {
    struct list *newItem;
    newItem = new struct list;
    newItem->info.InputList();
    cout << "Added new item: ";
    newItem->info.DisplayList();
    if (head==nullptr) {
        head=newItem;
        tail=newItem;
        head->next = nullptr;
    } else {
        tail->next = newItem;
        newItem->next = nullptr;
        tail = newItem;
    }
}

template <typename type>
void CList<type>::DisplayList() {
    struct list *p;
    p = head;
    while (p!=nullptr) {
        cout << p->info << "->";
        p = p->next;
    }
    printf("nullptr\n");
}

template <>
void CList<CListRemoveIfOddValue>::DisplayList() {
    struct list *p;
    p = head;
    while (p!=nullptr) {
        p->info.DisplayList();
        cout << " | " << endl;
        p = p->next;
    }
    printf("nullptr\n");
}

template <typename type>
void CList<type>::ReleaseList() {
    struct list *p;
    while (head!=nullptr) {
        p = head;
        head = head->next;
        delete p;
    }
    head=nullptr;
    tail=nullptr;
    cout << "List cleared\n";
}

template<>
void CList<char*>::ReleaseList() {
    struct list *p;
    while (head!=nullptr) {
        p = head;
        head = head->next;
        delete[] p->info;
        delete p;
    }
    head=nullptr;
    tail=nullptr;
    cout << "List cleared\n";
}

template<>
void CList<CListRemoveIfOddValue>::ReleaseList() {
    struct list *p;
    while (head!=nullptr) {
        p = head;
        head = head->next;
        p->info.ReleaseList();
        delete p;
    }
    head=nullptr;
    tail=nullptr;
    cout << "List cleared\n";
}

template <typename type>
bool CList<type>::Dublicate(type data) {
    struct list *p = head;
    struct list *NewItem;
    if (head != nullptr && head->info == data) {
        NewItem = new struct list;
        NewItem->info = data;
        NewItem->next = p->next;
        p->next = NewItem;
        p = p->next->next;
    }
    while (p != nullptr) {
        if (p->info == data && p == tail) {
            NewItem = new struct list;
            NewItem->info = data;
            NewItem->next = NULL;
            p->next = NewItem;
            tail = NewItem;
            p = NULL;
        } else if (p->info == data) {
                NewItem = new struct list;
                NewItem->info = data;
                NewItem->next = p->next;
                p->next = NewItem;
                p = p->next->next;
        } else {
            p = p->next;
        }
    }
    return true;
}


template<>
bool CList<CListRemoveIfOddValue>::Dublicate(CListRemoveIfOddValue data) {
    struct list *p = head;
    struct list *NewItem;
    if (head != nullptr && head->info == data) {
        NewItem = new struct list;
        NewItem->info.Copy(data);
        NewItem->next = p->next;
        p->next = NewItem;
        if(head == tail) {
            tail = NewItem;
        }
        p = p->next->next;
    }
    while (p != nullptr) {
        if (p->info == data && p == tail) {
            NewItem = new struct list;
            NewItem->info.Copy(data);
            NewItem->next = NULL;
            p->next = NewItem;
            tail = NewItem;
            p = NULL;
        } else if (p->info == data) {
            NewItem = new struct list;
            NewItem->info.Copy(data);
            NewItem->next = p->next;
            p->next = NewItem;
            p = p->next->next;
        } else {
            p = p->next;
        }
    }
    return true;
}

template<>
bool CList<char*>::Dublicate(char* data) {
    struct list *p = head;
    struct list *NewItem;
    if (head != nullptr && strcmp(head->info, data) == 0) {
        NewItem = new struct list;
        strcpy(NewItem->info, data);
        NewItem->next = p->next;
        p->next = NewItem;
        p = p->next->next;
    }
    while (p != nullptr) {
        if (strcmp(head->info, data) == 0 && p == tail) {
            NewItem = new struct list;
            strcpy(NewItem->info, data);
            NewItem->next = NULL;
            p->next = NewItem;
            tail = NewItem;
            p = NULL;
        } else if (strcmp(head->info, data) == 0 && p == tail) {
            NewItem = new struct list;
            strcpy(NewItem->info, data);
            NewItem->next = p->next;
            p->next = NewItem;
            p = p->next->next;
        } else {
            p = p->next;
        }
    }
    return true;
}

template <typename T> ostream& operator << (ostream& output, CList<T>& c) {
    c.DisplayList();
    return output;
}

void ActInt() {
    CList<int> listint;
    int key = 10;
    while (key != 0) {

        printf("\n\nCList<int>\n");
        printf("1 - добавление элемента\n");
        printf("2 - вывод списка на экран\n");
        printf("3 - очитска списка\n");
        printf("4 - дублирование\n");
        printf("0 - выход\n");
        printf("Ваш выбор: \n");

        cin >> key;

        if (key == 1) {
            int x;
            cout << "Введите элемент\n";
            cin >> x;
            listint.AddItem(x);
        } else if (key == 2) {
            cout << "" << listint;
        } else if (key == 3) {
            listint.ReleaseList();
        } else if (key == 4) {
            int x;
            cout << "Введите элемент, который нужно дублировать\n";
            cin >> x;
            listint.Dublicate(x);
        }
    }
}
void ActDouble() {
    CList<double> listdouble;
    int key = 10;
    while (key != 0) {

        printf("\n\nCList<double>\n");
        printf("1 - добавление элемента\n");
        printf("2 - вывод списка на экран\n");
        printf("3 - очитска списка\n");
        printf("4 - дублирование\n");
        printf("0 - выход\n");
        printf("Ваш выбор: \n");

        cin >> key;

        if (key == 1) {
            double x;
            cout << "Введите элемент\n";
            cin >> x;
            listdouble.AddItem(x);
        } else if (key == 2) {
            cout << listdouble;
        } else if (key == 3) {
            listdouble.ReleaseList();
        } else if (key == 4) {
            double x;
            cout << "Введите элемент, который нужно дублировать\n";
            cin >> x;
            listdouble.Dublicate(x);
        }
    }
}
void ActStr() {
    CList<char*> liststr;
    int key = 10;
    while (key != 0) {

        printf("\n\nCList<char*>\n");
        printf("1 - добавление элемента\n");
        printf("2 - вывод списка на экран\n");
        printf("3 - очитска списка\n");
        printf("4 - дублирование\n");
        printf("0 - выход\n");
        printf("Ваш выбор: \n");

        cin >> key;

        if (key == 1) {
            char x[100];
            cout << "Введите элемент\n";
            cin >> x;
            liststr.AddItem(x);
        } else if (key == 2) {
            cout << liststr;
        } else if (key == 3) {
            liststr.ReleaseList();
        } else if (key == 4) {
            char x[100];
            cout << "Введите элемент, который нужно дублировать\n";
            cin >> x;
            liststr.Dublicate(x);
        }
    }
}
void ActList() {
    int key = 10;
    CList<CListRemoveIfOddValue> listlist;
    CListRemoveIfOddValue p; // use only for dublicate
    p.AddItem(1);
    p.AddItem(2);
    p.DisplayList();
    while (key != 0) {
        int kekes;

        printf("\n\nCList<CListRemoveIfOddValue>\n");
        printf("1 - добавление элемента\n");
        printf("2 - вывод списка на экран\n");
        printf("3 - очитска списка\n");
        //printf("4 - удаление нечетных по значению из списка\n");
        printf("4 - дублирование\n");
        printf("ESC - выход\n");
        printf("Ваш выбор: \n");

        cin >> key;

        if (key == 1) {
            listlist.AddItem();
        } else if (key == 2) {
            cout << listlist;
        } else if (key == 3) {
            listlist.ReleaseList();
        } else if (key == 4) {
            listlist.Dublicate(p);
        }
    }
}

int main() {
    setlocale(0,"RUS");
    int key = 10;
    while (key != 0) {
        int kekes;

        printf("\n\n1 - cоздать список int\n");
        printf("2 - cоздать список double\n");
        printf("3 - cоздать список char*\n");
        printf("4 - cоздать список CListRemoveIfOddValue\n");
        printf("0 - выход\n");
        printf("Ваш выбор: \n");

        cin >> key;

        if (key == 1) {
            ActInt();
        } else if (key == 2) {
            ActDouble();
        } else if (key == 3) {
            ActStr();
        } else if (key == 4) {
            ActList();
        }
    }

    return 0;
}
