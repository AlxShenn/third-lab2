#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <map>
#include "hashset.h"

using namespace std;

void SaveSets(const string& filename, map<string, HashSet<string>*>& sets);
void LoadSets(const string& filename, map<string, HashSet<string>*>& sets);

#endif