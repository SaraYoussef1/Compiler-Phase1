#include "DFA.h"
#include <iostream>
#include <bits/stdc++.h>
#include <iterator>

using namespace std;
vector<DFA_State*>Table;
int Count = 2;
template<typename T>
bool isEqual(std::set<T> const& v1, std::set<T> const& v2)
{
    return (v1.size() == v2.size() &&
        std::equal(v1.begin(), v1.end(), v2.begin()));
}
bool Check(set<int> v)
{

    for (auto i : Table)
    {
        if (isEqual(v, i->subset_ids))
        {
            return false;
        }
    }
    return true;
}

vector <NFA_State*> E_closure(NFA_State* original) {
    vector <NFA_State*> closures;
    stack <NFA_State*> temp;
    temp.push(original);
    while (!temp.empty()) {
        NFA_State* state = temp.top();
        temp.pop();
        vector <Transition> t = state->transitions;
        for (auto item : t) {
            if (item.input_symbol.name == "e") {
                if (!count(closures.begin(), closures.end(), item.next)) {
                    closures.push_back(item.next);
                    temp.push(item.next);
                }
            }
        }
    }
    return closures;
}
vector<DFA_State*> get()
{
    return Table;
}

void Move_To(DFA_State* Basic_node) //struct node
{
    set<NFA_State*> Initial_state = Basic_node->subset;
    map <string, set<NFA_State*>> temp_symbols;
    map <string, set<int>> temp_ids;
    for (auto i : Initial_state)//int i=0;i<Initial_state.size();i++
    {
        vector<Transition> Total_Transition = i->transitions;

        for (int j = 0; j < Total_Transition.size(); j++)
        {
            if (Total_Transition[j].input_symbol.name == "e") continue;
            temp_symbols[Total_Transition[j].input_symbol.name].insert(Total_Transition[j].next);  //push the next node .
            temp_ids[Total_Transition[j].input_symbol.name].insert((Total_Transition[j].next)->id);
            // part of epsilon ..
            vector <struct NFA_State*> Epsilon_state = E_closure(Total_Transition[j].next);
            if (Epsilon_state.size() != 0) //epsilon of each reachable node.
            {
                for (auto item : Epsilon_state)
                {
                    temp_symbols[Total_Transition[j].input_symbol.name].insert(item); //push epsilon of each reachable node.
                    temp_ids[Total_Transition[j].input_symbol.name].insert(item->id);
                }
            }

        }
    }
    //after that the row is fish must push it in the vector under each input symbol.
    for (auto i : temp_ids)
    {
        if (Check(i.second))
        {
            DFA_State* temp = new DFA_State;
            temp->id = Count++; //cout<<i.first<<endl;
            temp->subset = temp_symbols[i.first]; //i.first mean input;
            temp->subset_ids = temp_ids[i.first];
            Table.push_back(temp);

        }
    }
    Basic_node->symbols = temp_symbols;
    //print...
    /*for(auto t :Basic_node->symbols)
    {
        cout<<t.first<<" "<<endl;
        for(auto e: t.second)
            cout<<"id"<<e->id<<" "<<endl;

    }*/
    Basic_node->Group_ids = temp_ids;
}


void Subset_Construction(NFA_State* original)
{
    // prepare the initial state by original.
    DFA_State* a = new DFA_State;
    a->id = 1;
    a->subset.insert(original);
    a->subset_ids.insert(original->id);

    //call epsilon .
    vector <struct NFA_State*> Epsilon_state = E_closure(original);
    if (Epsilon_state.size() != 0) //epsilon of each reachable node.
    {
        for (auto item : Epsilon_state)
        {
            a->subset.insert(item);
            a->subset_ids.insert(item->id);
        }
    }
    //push a to the Table as start state.
    Table.push_back(a);
    int t = 0;
    while (t < Table.size())
    {
        Move_To(Table[t]);
        t++;
    }
}


void test(DFA_State* a)
{

    Table.push_back(a);

    int t = 0;
    while (t < Table.size())
    {
        Move_To(Table[t]);
        t++;
    }

    for (int i = 0; i < Table.size(); i++)
    {
        cout << "State : { ";
        for (auto item : Table[i]->subset_ids)
        {
             cout<< item << " ";
        }
        cout << "}";
        for (auto const& pair : Table[i]->Group_ids) {
            std::cout << " transition {" << pair.first << ": ";

            set<int> myset = pair.second;

            // using begin() to print set
            for (auto it = myset.begin(); it != myset.end(); ++it)
            {
                cout << ' ' << *it << " ";

            }
            cout << "}\n";
        }
    }
}

map<int, map<string, int>> get_graph (){
    //first map: DFA state id with DFA transitions
    //second map: input symbol with the id of corresponding reached DFA state
    map<int, map<string, int>> graph;
    map<string, int> second_map;
    for(int i=0; i<Table.size(); i++){
        int current_id = Table[i]->id;
        map <string, set<NFA_State*>> transition = Table[i]->symbols;
        for(auto item : transition){
            string input = item.first;
            int next_id;
            set <NFA_State*> sub = item.second;
            for(auto next:Table){
                if(next->subset == sub){
                    next_id = next->id;
                    break;
                }
            }
            second_map.insert({input, next_id});
        }
        graph.insert({current_id, second_map});

        second_map.clear();
    }
    print_graph(graph);
    return graph;
}

void print_graph(map<int, map<string, int>> graph){
    cout<<graph[1]["1"];
    // graph[1] -> maptT
    //Print your graph here
    //map<int, map<string, int>> graph;
    map<int, map<string, int>>::iterator itr1;
    map<string, int>::iterator itr2;
    for(itr1 =  graph.begin(); itr1 !=  graph.end(); ++itr1){
        cout<<"\n state id is "<<itr1->first<<"\n";
        for(itr2 = itr1->second.begin(); itr2 != itr1->second.end(); ++itr2)
            cout<<"under input "<< itr2->first<<"  it goes to state "<<itr2->second<<"\n";
        cout<<"*******************"<<"\n";
    }
}



