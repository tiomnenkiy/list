#include <stdio.h>
#include <string.h>
#include <iostream>
#include "list.h"

CListRemoveIfOddValue::CListRemoveIfOddValue() {
    head=NULL;
    tail=NULL;
}

CListRemoveIfOddValue::~CListRemoveIfOddValue() {
    ReleaseList();
}

void CListRemoveIfOddValue::AddItem(int data) {
    struct flist *newItem;
    newItem = new struct flist;
    newItem->info = data;
    if (head==NULL) {
        head=newItem;
        tail=newItem;
        head->next = NULL;
    } else {
        tail->next = newItem;
        newItem->next = NULL;
        tail = newItem;
    }
}

void CListRemoveIfOddValue::DisplayList() {
    struct flist *p;
    p = head;
    while (p!=NULL) {
        printf("%d->", p->info);
        p = p->next;
    }
    printf("NULL\n");
}

void CListRemoveIfOddValue::ReleaseList() {
    struct flist *p;
    while (head!=NULL) {
        p = head;
        head = head->next;
        delete p;
    }
    head=NULL;
    tail=NULL;
}

void CListRemoveIfOddValue::RemoveIfOddValue() {
    struct flist *p = head;
    struct flist *d;
    while (head != nullptr && head->info%2 != 0) {
        p = head;
        head = head->next;
        delete p;
    }
    p = head;
    if (p != nullptr) {
        while (p->next != nullptr ) {
            if (p->next->info%2 != 0) {
                if (p->next == tail) {
                    tail = p;
                }
                d = p->next;
                p->next = p->next->next;
                delete d;
            } else {
                p = p->next;
            }
        }
    }
}

void CListRemoveIfOddValue::Copy(const CListRemoveIfOddValue& x){
    struct CListRemoveIfOddValue::flist *p;
    p = x.head;
    while(p!=NULL) {
        this->AddItem(p->info);
        p = p->next;
    }
}

bool operator== (CListRemoveIfOddValue const& c1, CListRemoveIfOddValue const& c2) {
    struct CListRemoveIfOddValue::flist *p1;
    struct CListRemoveIfOddValue::flist *p2;
    p1 = c1.head;
    p2 = c2.head;
    bool equal = 1;
    while (p1!=NULL && p2!=NULL && equal) {
        if (p1->info != p2->info)
            equal = 0;
        p1 = p1->next;
        p2 = p2->next;
    }
    if (p1 != p2)
        equal = 0;
    return equal;
}

void CListRemoveIfOddValue::InputList () {
    int key = 10;

    setlocale(0,"RUS");
    while (key != 0) {
        int kekes;
        printf("\n\nCListRemoveIfOddValue\n");
        printf("1 - добавление элемента\n");
        printf("2 - вывод списка на экран\n");
        printf("3 - очитска списка\n");
        printf("0 - выход\n");
        printf("Ваш выбор: \n");

        std::cin >> key;

        if (key == 1) {
            printf("Введите элемент списка: ");
            std::cin >> kekes;
            this->AddItem(kekes);
        } else if (key == 2) {
            this->DisplayList();
        } else if (key == 3) {
            this->ReleaseList();
        }
    }
}
