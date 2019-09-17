#include <iostream>
#include "delist.h"

using namespace std;



DEList::DEList()
{
    head = NULL;
    tail = NULL;
    size_of_list = 0;
}
// Destructor to clean-up memory of current list
DEList::~DEList()
{
    for (int i = 0; i < size_of_list; i++)
    {
        pop_front();
        cout <<"size: " << size_of_list << endl;
    }
}
// returns a Boolean 'true' if the list is empty
bool DEList:: empty()
{
    if (size_of_list==0)
    {
        return true;
    }
    
    return false;
}
// returns number of items in the list
int DEList:: size()
{
    int curr_size = size_of_list;
    return curr_size;
}
// returns front item or -1 if empty list
int DEList::front()
{
    if (head == NULL)
    {
        return -1;
    }
    
    
    return (head->val);
}
// returns back item or -1 if empty list
int DEList::back()
{
    if (tail == NULL)
    {
        return -1;
    }
    
    return (tail->val);
    
    
}
// Adds a new integer to the front of the list
void DEList:: push_front(int new_val)
{
    
    DEItem* temp = new DEItem;
    temp -> val = new_val;
    temp -> next = head;
    
    if (!empty())
    {
        head -> prev = temp;
    }
    else
    {
        tail = temp;
    }
    
    head = temp;
    temp -> prev = NULL;
    size_of_list++;
    
}
// Adds a new integer to the back of the list
void DEList:: push_back(int new_val)
{
    
    DEItem* temp = new DEItem;
    temp-> val = new_val;
    temp -> prev = tail;
    
    if(!empty())
    {
        tail -> next = temp;
    }
    else
    {
        head = temp;
    }
    
    tail = temp;
    temp -> next = NULL;
    size_of_list++;
    
}
// Removes the front item of the list (if it exists)
void DEList::pop_front()
{
    if (!empty())
    {
        DEItem* temp;
        if (head == tail)
        {
            delete head;
            head = NULL;
            tail = NULL;
            size_of_list = 0;
        }
        else
        {
            temp = head;
            head = temp->next;
            head -> prev = NULL;
            size_of_list--;
            delete temp;
        }
    }
    
    
}
// Removes the back item of the list (if it exists)
void DEList::pop_back()
{
    if (!empty())
    {
        DEItem* temp;
        if (head == tail)
        {
            delete head;
            head = NULL;
            tail = NULL;
            size_of_list = 0;
        }
        else
        {
            temp = tail;
            tail = temp->prev;
            tail -> next = NULL;
            size_of_list--;
            delete temp;
            
        }
        
    }
}
