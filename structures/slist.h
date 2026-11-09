#ifndef SLIST_H
#define SLIST_H

#include <string>
#include "hashSet.h"

using namespace std;

struct SlistNode {
    string text;
    SlistNode* next;
    HashSet<string>* set = nullptr; 
};

struct Slist {
    SlistNode* head;
};

void FInitializeSlist(Slist& slist);
void FPushHead(Slist& slist, const string& value);
void FPushTail(Slist& slist, const string& value);
void FPushBefore(Slist& slist, const string& target, const string& value);
void FPushAfter(Slist& slist, const string& target, const string& value);

void FDeleteHead(Slist& slist);
void FDeleteTail(Slist& slist);
void FDeleteBefore(Slist& slist, const string& target);
void FDeleteAfter(Slist& slist, const string& target);
void FDeleteValue(Slist& slist, const string& value);

bool FGet(Slist& slist, const string& value);
void FPrint(const Slist& slist); 
void FFree(Slist& slist);

HashSet<string>* FGetOrCreateSet(Slist& slist, const string& setName);

#endif