#include "slist.h"
#include <iostream>

void FInitializeSlist(Slist& slist) {
    slist.head = nullptr;
}

void FPushHead(Slist& slist, const string& value) {
    SlistNode* newNode = new SlistNode{value, slist.head, nullptr};
    slist.head = newNode;
}

void FPushTail(Slist& slist, const string& value) {
    if (slist.head == nullptr) {
        FPushHead(slist, value);
        return;
    }
    SlistNode* current = slist.head;
    while (current->next != nullptr) { 
        current = current->next;
    }
    current->next = new SlistNode{value, nullptr, nullptr};
}

void FPushAfter(Slist& slist, const string& target, const string& value) {
    if (slist.head == nullptr) return;
    SlistNode* current = slist.head;
    while (current != nullptr && current->text != target) {
        current = current->next;
    }
    if (current != nullptr) {
        SlistNode* newNode = new SlistNode{value, current->next, nullptr};
        current->next = newNode;
    }
}

void FPushBefore(Slist& slist, const string& target, const string& value) {
    if (slist.head == nullptr) return;
    if (slist.head->text == target) {
        FPushHead(slist, value);
        return;
    }
    SlistNode* current = slist.head;
    while (current->next != nullptr && current->next->text != target) {
        current = current->next;
    }
    if (current->next != nullptr) {
        SlistNode* newNode = new SlistNode{value, current->next, nullptr};
        current->next = newNode;
    }
}

void FDeleteBefore(Slist& slist, const string& target) {
    if (slist.head == nullptr || slist.head->next == nullptr) return;
    if (slist.head->next->text == target) {
        FDeleteHead(slist);
        return;
    }
    SlistNode* current = slist.head;
    while (current->next->next != nullptr && current->next->next->text != target) {
        current = current->next;
    }
    if (current->next->next != nullptr) {
        SlistNode* delNode = current->next;
        current->next = delNode->next;
        if (delNode->set) delete delNode->set; 
        delete delNode;
    }
}

void FDeleteAfter(Slist& slist, const string& target) {
    if (slist.head == nullptr) return;
    SlistNode* current = slist.head;
    while (current != nullptr && current->text != target) {
        current = current->next;
    }
    if (current != nullptr && current->next != nullptr) {
        SlistNode* delNode = current->next;
        current->next = delNode->next;
        if (delNode->set) delete delNode->set;
        delete delNode;
    }
}

void FDeleteHead(Slist& slist) {
    if (slist.head == nullptr) return;
    SlistNode* nodeToDelete = slist.head;
    slist.head = slist.head->next;
    if (nodeToDelete->set) delete nodeToDelete->set; 
    delete nodeToDelete;
}

void FDeleteTail(Slist& slist) {
    if (slist.head == nullptr) return;
    if (slist.head->next == nullptr) {
        FDeleteHead(slist);
        return;
    }
    SlistNode* current = slist.head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    SlistNode* delNode = current->next;
    current->next = nullptr;
    if (delNode->set) delete delNode->set;
    delete delNode;
}   

void FDeleteValue(Slist& slist, const string& value) {
    if (slist.head == nullptr) return;
    if (slist.head->text == value) {
        FDeleteHead(slist);
        return;
    }
    SlistNode* current = slist.head;
    while (current->next != nullptr && current->next->text != value) {
        current = current->next;
    }

    if (current->next != nullptr){
        SlistNode* delNode = current->next;
        current->next = delNode->next;
        if (delNode->set) delete delNode->set;
        delete delNode;
    }
}

bool FGet(Slist& slist, const string& target) {
    SlistNode* currentNode = slist.head;
    while (currentNode != nullptr) {
        if (currentNode->text == target) {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

void FPrint(const Slist& slist) {
    if (slist.head == nullptr) {
        cout << "Slist is empty" << endl;
        return;
    }
    for (SlistNode* currentNode = slist.head; currentNode != nullptr; currentNode = currentNode->next) {
        cout << currentNode->text << " ";
    }
    cout << "\n";
}

void FFree(Slist& slist) {
    while (slist.head != nullptr) {
        FDeleteHead(slist);
    }
}

HashSet<string>* FGetOrCreateSet(Slist& slist, const string& setName) {
    SlistNode* current = slist.head;
    while (current != nullptr) {
        if (current->text == setName) {
            return current->set; 
        }
        current = current->next;
    }
    FPushHead(slist, setName);
    slist.head->set = new HashSet<string>();
    return slist.head->set;
}