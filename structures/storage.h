#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include "hashset.h"
#include "slist.h"

using namespace std;

void SaveSets(const string& filename, Slist& sets);
void LoadSets(const string& filename, Slist& sets);

#endif