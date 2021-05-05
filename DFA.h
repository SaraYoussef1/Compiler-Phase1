#include <iostream>
#include <vector>
#include <map>
#include "NFA.h"
#include <bits/stdc++.h>
using namespace std;


struct DFA_State{
    int id;
    set <NFA_State*> subset;
    set <int> subset_ids; //of NFA_state
    //string represents the content of input_symbol
    //vector represents move+epsilon transitions
    map <string, set<NFA_State*>> symbols;
    map <string, set<int>> Group_ids;
};


void Move_To(DFA_State *Basic_node);
void test(DFA_State *Basic_node);
map<int, map<string, int>> get_graph ();
void print_graph(map<int, map<string, int>> graph);
