#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
#include "exception.h"

using namespace std;

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {
private:
    DLink(T);
    DLink(T, DLink<T>*, DLink<T>*);
    DLink(const DLink<T>&);

    T value;
    DLink<T> *previous;
    DLink<T> *next;

    friend class DList<T>;
    friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
    DList();
    DList(const DList<T>&);
    DList<T>& operator=(const DList<T>&);
    ~DList();

    void add(T);
    int  length() const;
    T    get(int) const;
    bool contains(T) const;
    bool empty() const;
    void clear();
    int  indexOf(T) const;
    T    remove(int);
    bool removeFirstOcurrence(T);

private:
    DLink<T> *head;
    DLink<T> *tail;
    int size;

    friend class DListIterator<T>;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
    clear();
}

template <class T>
bool DList<T>::empty() const {
    return (head == 0 && tail == 0);
}

template <class T>
int DList<T>::length() const {
    return size;
}

template <class T>
bool DList<T>::contains(T val) const {
    DLink<T> *p = head;
    while (p != 0) {
        if (p->value == val) return true;
        p = p->next;
    }
    return false;
}

template <class T>
void DList<T>::add(T val) {
    DLink<T> *newLink = new DLink<T>(val);
    if (newLink == 0) {
        throw OutOfMemory();
    }

    if (empty()) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

template <class T>
T DList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw IndexOutOfBounds();
    }

    DLink<T> *p = head;
    int pos = 0;
    while (pos != index) {
        p = p->next;
        pos++;
    }
    return p->value;
}

template <class T>
void DList<T>::clear() {
    DLink<T> *p = head, *q;
    while (p != 0) {
        q = p->next;
        delete p;
        p = q;
    }
    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
DList<T>::DList(const DList<T> &source) : head(0), tail(0), size(0) {
    DLink<T> *p = source.head;
    while (p != 0) {
        add(p->value);
        p = p->next;
    }
}

template <class T>
DList<T>& DList<T>::operator=(const DList<T> &source) {
    if (this != &source) {
        clear();
        DLink<T> *p = source.head;
        while (p != 0) {
            add(p->value);
            p = p->next;
        }
    }
    return *this;
}

template <class T>
int DList<T>::indexOf(T val) const {
    int index = 0;
    DLink<T> *p = head;
    while (p != 0) {
        if (p->value == val) return index;
        index++;
        p = p->next;
    }
    return -1;
}

template <class T>
T DList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        throw IndexOutOfBounds();
    }

    DLink<T> *p = head;
    int pos = 0;
    while (pos != index) {
        p = p->next;
        pos++;
    }

    T val = p->value;

    if (head == tail) {
        head = 0;
        tail = 0;
    } else if (p == head) {
        head = p->next;
        head->previous = 0;
    } else if (p == tail) {
        tail = p->previous;
        tail->next = 0;
    } else {
        p->previous->next = p->next;
        p->next->previous = p->previous;
    }

    delete p;
    size--;
    return val;
}

template <class T>
bool DList<T>::removeFirstOcurrence(T val) {
    DLink<T> *p = head;
    while (p != 0) {
        if (p->value == val) break;
        p = p->next;
    }

    if (p == 0) return false;

    if (head == tail) {
        head = 0;
        tail = 0;
    } else if (p == head) {
        head = p->next;
        head->previous = 0;
    } else if (p == tail) {
        tail = p->previous;
        tail->next = 0;
    } else {
        p->previous->next = p->next;
        p->next->previous = p->previous;
    }

    delete p;
    size--;
    return true;
}

template <class T>
class DListIterator {
public:
    DListIterator(DList<T>*);
    DListIterator(const DListIterator<T>&);

    bool begin();
    bool end();
    T&   operator() ();
    bool operator++ ();
    void operator= (T);

private:
    DLink<T> *current;
    DLink<T> *previous;
    DList<T> *theList;

    friend class DList<T>;
};

template <class T>
DListIterator<T>::DListIterator(DList<T> *aList) : theList(aList) {
    begin();
}

template <class T>
DListIterator<T>::DListIterator(const DListIterator<T> &source) : theList(source.theList) {
    begin();
}

template <class T>
bool DListIterator<T>::begin() {
    previous = 0;
    current = theList->head;
    return (current != 0);
}

template <class T>
T& DListIterator<T>::operator() () {
    if (current == 0) throw NoSuchElement();
    return current->value;
}

template <class T>
bool DListIterator<T>::end() {
    if (current == 0 && previous != 0) {
        current = previous->next;
    }
    return (current == 0);
}

template <class T>
bool DListIterator<T>::operator++ () {
    if (current == 0) {
        current = (previous == 0) ? theList->head : previous->next;
    } else {
        previous = current;
        current = current->next;
    }
    return (current != 0);
}

template <class T>
void DListIterator<T>::operator= (T val) {
    if (current == 0) throw NoSuchElement();
    current->value = val;
}

#endif
