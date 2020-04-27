//
// Created by merso on 06.01.2020.
//
#ifndef OOP_1_LIST_H
#define OOP_1_LIST_H

class CListRemoveIfOddValue {
    struct flist {
        int info;
        struct flist *next;
    };
    struct flist *head;
    struct flist *tail;

public:
    CListRemoveIfOddValue();
    ~CListRemoveIfOddValue();
    void AddItem(int);
    void DisplayList();
    void ReleaseList();
    void RemoveIfOddValue();
    flist* GetHead() {
        return head;
    }
    CListRemoveIfOddValue& operator= (CListRemoveIfOddValue const& c);
    friend bool operator== (CListRemoveIfOddValue const& c1, CListRemoveIfOddValue const& c2);
    void InputList ();
};

#endif //OOP_1_LIST_H
