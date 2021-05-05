#include <iostream>
#include <map>
#include "DFA.h"
using namespace std;

void table_filling(map<int, DFA_Graph> graph);
bool mark(map<int, DFA_Graph> graph, int id1, int id2);
