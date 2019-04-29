#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <stdio.h>

using namespace std;

    class contact_node{
    private:
        string num;
        string name;
        contact_node *next, *prev;
    public:

        contact_node(string num, string name){
            this->num = num;
            this->name = name;
            this->prev = NULL;
            this->next = NULL;
        };

    };


    class hashtable{
    public:
        unsigned int size = 8963;
        contact_node list[8963];

    };


    int hash_func(std::string name){
        int hash_value;
        for(int i=0; i<name.length(); i++){
            hash_value = hash_value + name.at(i);
        }

        return hash_value;
    }