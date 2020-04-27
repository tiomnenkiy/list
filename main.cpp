#include <iostream>
#include <string.h>
#include <stdio.h>
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
    void AddItem(type);
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

/*
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
 */


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
        //cout << p->info << "->";
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
        if (p->info == data) {
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

template <typename T> ostream& operator << (ostream& output, CList<T>& c) {
    c.DisplayList();
    return output;
}

int main() {
    CList<CListRemoveIfOddValue> listlist;
    int key = 10;
    CListRemoveIfOddValue p; // use only for dublicate
    //p.AddItem(1);
    //p.AddItem(2);
    p.DisplayList();
    //list.AddItem(p);
    //cout << "Added with AddItem(p):\n";
    //list.DisplayList();
    setlocale(0,"RUS");
    while (key != 0) {
        int kekes;

        printf("\n\n1 - добавление элемента\n");
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
    CList<char*> strlist;
    while (key != 0) {
        char* kekes;

        printf("\n\n1 - добавление элемента\n");
        printf("2 - вывод списка на экран\n");
        printf("3 - очитска списка\n");
        //printf("4 - удаление нечетных по значению из списка\n");
        printf("4 - дублирование\n");
        printf("ESC - выход\n");
        printf("Ваш выбор: \n");

        cin >> key;

        if (key == 1) {
            strlist.AddItem();
        } else if (key == 2) {
            cout << strlist;
        } else if (key == 3) {
            strlist.ReleaseList();
        } else if (key == 4) {
            
            strlist.Dublicate(kekes);
        }
    }
    return 0;
}