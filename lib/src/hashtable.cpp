//
// Created by camer on 5/3/2019.
//

#include "hashtable.h"
#include "contact_node.h"
#include <string>

using namespace std;  //Not sure why this is getting errors
namespace lib{
    hashtable::hashtable() {                    // Not sure why hashtable is undeclared
        hash_table = new contact_node*[size];
        // Create empty hash table
        for(int i=0; i<size; i++){
            hash_table[i] = nullptr;
        }
    }

    contact_node* hsshtable::get(string name) {}

    hashtable::~hashtable(){
        for(int i=0; i<size; i++){
            contact_node *entry = hash_table[i];

            while(entry != nullptr){
                contact_node *prev = entry;
                while(entry->num_node != nullptr){
                    info_node *info_prev = entry->num_node;
                    entry->num_node = entry->num_node->next_num;
                    delete info_prev;
                }
                entry = entry->next;
                delete prev;
            }
        }
    }

    int hashtable::hash_func(string name){
        int hash_value;
        for(int i=0; i<name.length(); i++){
            // Add each ASCII value cubed to hash value
            // Cubed to ensure entire table is used
            hash_value = (hash_value + (name.at(i)^3));
        }
        return hash_value%size;
    }
}