#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

struct input{
    string name;
    string content;
};

struct Transition{
    //struct input
    struct input input_symbol;
    struct NFA_State* next;
};

struct NFA_State {
    int id;
    vector <Transition> transitions;
};


