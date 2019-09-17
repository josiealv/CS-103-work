#include "user.h"
#include <iostream>
using namespace std;

User::User(int u_id, int year, int zip_code, string username)
{
    //stores all info given from social_network.cpp into
    //the private variables in User class
    id = u_id;
    birth_year = year;
    zip = zip_code;
    name = username;
    
}
User::~User()
{
    
}
void User:: add_friend (int f_id)
{
    //searches thru friends list to ensure they aren't
    //friends yet
    for (int i=0; i < friends.size(); i++)
    {
        if (f_id == friends[i])
        {
            return;
        }
    }
    friends.push_back (f_id);
    
}
void User:: delete_friend (int f_id)
{
    //looks for friend id in friend list, then removes friend
    for (int i=0; i < friends.size(); i++)
    {
        if (f_id == friends[i])
        {
            friends.erase(friends.begin()+i);
            return;
        }
    }
    
}
int User::get_id1 () const
{
    return id;
}
int User::get_birth_year () const
{
    return birth_year;
}
int User::get_zip () const
{
    return zip;
}
string User::get_name () const
{
    return name;
}

vector <int>* User::friends_list( )
{
    return &friends;
}
int User:: getDepth ()
{
    return depth;
}
int User :: getPred()
{
    return predecessor;
}
void User::setDepth (int d)
{
    depth = d;
}
void User:: setPred (int p)
{
    predecessor = p;
}
