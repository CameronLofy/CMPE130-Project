#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <stdio.h>

using namespace std;

    class contact_node{
    public:

        std::string name;
        class numlist{
            string num;
            numlist *next, *prev;
        };

        contact_node *next, *prev;
    };


    class hashtable{
    public:
        unsigned int size = 8963;
        contact_node list[8963];

    };


    void hash_func(struct name){

    }