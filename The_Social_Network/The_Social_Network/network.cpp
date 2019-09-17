#include "network.h"
#include "user.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <deque>
using namespace std;

int Network::read_friends(const char *filename)
{
    ifstream ifile (filename);
    
    //checks that filename is valid
    if (ifile.fail())
    {
        return -1;
    }
    
    //dynamically allocated int to temporarily hold size of user list
    int* num_users = new int;
    ifile >> *num_users;
    
    //ensures input is right type & num_users is a valid #
    if (ifile.fail() || *num_users < 0)
    {
        return -1;
    }
    
    
    for (int i = 0; i < *num_users; i++)
    {
        int id;
        ifile >> id;
        string name;
        
        getline(ifile, name, '\t');
        getline(ifile, name);
        
        int year, zip;
        ifile >> year;
        ifile >> zip;
        
        
        user_list.push_back(User(id, year, zip, name));
        
        string friends_line; //variable for line w/ friends' id #'s
        
        getline(ifile, friends_line); //reads in friends_line til tab
        getline (ifile, friends_line);
        
        stringstream ss(friends_line);
        int friends_id;
        
        while (ss>>friends_id) //reads in ids of friends til the end of line
        {
            //adds the current friend id to current user's friends list
            user_list[id].add_friend(friends_id);
        }
        
    }
    
    ifile.close();
    delete num_users;
    return 0;
}
int Network::write_friends(const char *filename)
{
    ofstream new_file(filename);
    
    //ensures that the empty filename is valid
    if (new_file.fail())
    {
        return -1;
    }
    
    //prints out the number of users first
    new_file << user_list.size() << '\n';
    
    //prints out the first user info before all others bc diff format
    new_file << user_list[0].get_id1() << '\n';
    new_file << '\t';
    new_file << user_list[0].get_name() << '\n';
    new_file << '\t' << user_list[0].get_birth_year() << '\n';
    new_file << '\t' << user_list[0].get_zip() << '\n';
    
    vector <int> friends = *user_list[0].friends_list();
    
    new_file << '\t';
    
    //prints the first user's friends id list
    for (int f = 0; f < friends.size(); f++)
    {
        new_file << friends[f] << " ";
    }
    cout << '\n';
    
    //prints out all other user info
    for (int i =1; i < user_list.size(); i++)
    {
        new_file << '\n';
        new_file << user_list[i].get_id1() << '\n';
        new_file << '\t';
        new_file << user_list[i].get_name() << '\n';
        new_file << '\t' << user_list[i].get_birth_year() << '\n';
        new_file << '\t' << user_list[i].get_zip() << '\n';
        
        vector <int> friends2 = *user_list[i].friends_list();
        
        new_file << '\t';
        
        //prints out current user's friends id list
        for (int f = 0; f < friends2.size(); f++)
        {
            new_file << friends2[f] << " ";
        }
        cout << '\n';
    }
    
    new_file.close();
    return 0;
    
}
Network::~Network()
{
    
}
Network::Network()
{
    
}

void Network::add_user(string username, int yr, int zipcode)
{
    int curr_index = (int) user_list.size();
    
    //adds a new user to user vector w/ given info
    user_list.push_back(User(curr_index, yr, zipcode, username));
    
}
int Network::add_connection(string name1, string name2)
{
    //variables to store ids
    int name1_id;
    int name2_id;
    
    name1_id = get_id(name1);
    name2_id = get_id (name2);
    
    if(name1_id == -1 || name2_id == -1)
    {
        return -1;
    }
    
    user_list[name1_id].add_friend(name2_id);
    user_list[name2_id].add_friend(name1_id);
    
    return 0;
}
int Network::remove_connection(string name1, string name2)
{
    //same as above
    int name1_id;
    int name2_id;
    
    name1_id = get_id(name1);
    name2_id = get_id (name2);
    
    if(name1_id == -1 || name2_id == -1)
    {
        return -1;
    }
    
    user_list[name1_id].delete_friend(name2_id);
    user_list[name2_id].delete_friend(name1_id);
    
    return 0;
    
}

int Network::get_id(string username)
{
    //variable to store id (-1 = id not found i.e. invalid name)
    int username_id = -1;
    
    //ensures that name is in user list
    for (int i = 0; i < user_list.size(); i++)
    {
        if (username == user_list[i].get_name())
        {
            username_id = user_list[i].get_id1();
        }
        
    }
    return username_id;
}


//gets name from user class (nom is name in Catalan)
string Network :: get_nom (int id)
{
    string nom = user_list[id].get_name();
    
    return nom;
    
}

void Network::print_users()
{
    cout << endl;
    cout << "ID     Name            Year    Zip      " << endl;
    cout << "==============================="
    << "============================" << endl;
    
    for (int i= 0; i < user_list.size(); i++)
    {
        cout << user_list[i].get_id1() << ".";
        
        if(user_list[i].get_id1() < 10)
        {
            cout << setw (5) << " ";
        }
        
        //adjusts width if id # is >= 10 but < 100
        else if (user_list[i].get_id1() >= 10 &&
                 user_list[i].get_id1() < 100)
        {
            cout << setw (3) << " ";
        }
        //adjusts width id # >= 100
        else
        {
            cout << setw (2) << " ";
        }
        cout << user_list[i].get_name();
        //adjusts width according to size of name
        cout << setw(16-((user_list[i].get_name()).size()))
        << std::right << " ";
        cout << user_list[i].get_birth_year();
        cout << setw(4) << " ";
        cout << user_list[i].get_zip();
        cout << endl;
    }
    
}

void Network:: print_friends(string name)
{
    int name_id = get_id(name);
    
    if (name_id == -1)
    {
        cout << "User does not exist. Please enter a valid user" << endl;
        return;
    }
    
    cout << endl;
    cout << "ID     Name            Year    Zip      " << endl;
    cout << "==============================="
    << "============================" << endl;
    
    
    vector <int> user_friends = *user_list[name_id].friends_list();
    
    //sorts friends list
    for (int i = 0; i < user_friends.size(); i++)
    {
        for (int j = i+1; j < user_friends.size(); j++)
        {
            if (user_friends[i] > user_friends[j])
            {
                int temp = user_friends[i];
                user_friends[i] = user_friends[j];
                user_friends[j] = temp;
            }
        }
    }
    
    //prints out friends list w/ their info by finding id's in user_list
    for (int f = 0; f < user_friends.size(); f++)
    {
        for (int u = 0; u < user_list.size(); u++)
        {
            //prints in same format as print_users() once user is found
            if(user_list[u].get_id1() == user_friends[f])
            {
                cout << user_friends[f] << ".";
                if(user_friends[f] < 10)
                {
                    cout << setw (5) << " ";
                }
                
                else if (user_friends[f] >= 10 &&
                         user_friends[f] < 100)
                {
                    cout << setw (3) << " ";
                }
                
                else
                {
                    cout << setw(2) << " ";
                }
                cout << user_list[u].get_name();
                cout << setw(16-((user_list[u].get_name()).size()))
                << std::right << " ";
                cout << user_list[u].get_birth_year();
                cout << setw(4) << " ";
                cout << user_list[u].get_zip();
                cout << endl;
            }
        }
    }
}
void Network::reset_depth_pred_groups_score ()
{
    /*resets all the user's depths, predecessors, & group ids
     to be -1 (-1 is outside of range)*/
    for (int i = 0; i < user_list.size(); i++)
    {
        user_list[i].setDepth(-1);
        user_list[i].setPred(-1);
        user_list[i].group = -1;
        /*suggested score set to 0 bc it's incr l8r
         as mutual friends r found (easier to incr too)*/
        user_list[i].sugg_score = 0;
    }
}
void Network::bfs (int s, int f)
{
    deque <int> q;
    user_list[s].setDepth(0);
    
    //starting user @ top of queue
    q.push_back(s);
    
    while (q.size() > 0)
    {
        int fr = q.front();
        int curr_depth = user_list[fr].getDepth();
        q.pop_front();
        
        //friend list of current user @ top
        vector <int> friends = *user_list[fr].friends_list();
        
        //updates depth & predecessor 4 all friends & adds them to top
        for (int i = 0; i < friends.size(); i++)
        {
            int f_id = friends[i];
            if (user_list[f_id].getDepth() == -1)
            {
                user_list[f_id].setDepth(curr_depth+1);
                user_list[f_id].setPred(fr);
                q.push_back(friends[i]);
            }
        }
        
        
    }
    
}

vector<int> Network::shortest_path(int from, int to)
{
    reset_depth_pred_groups_score();
    bfs (from, to);
    
    vector <int> path;
    
    //returns empty path vector if no path found
    if (user_list[to].getDepth() == -1)
    {
        return path;
    }
    else
    {
        path.push_back (to);
        int curr = user_list[to].getPred();
        
        //runs til there is no predecessor
        while (curr!=-1)
        {
            path.push_back (curr);
            curr = user_list[curr].getPred();
        }
        
    }
    
    //reverse path vector
    for (int i = 0; i < (path.size()/2); i++)
    {
        int temp = path [i];
        path [i] = path [path.size()-1-i];
        path [path.size()-1-i] = temp;
    }
    
    return path;
    
}


vector<vector<int> > Network::groups()
{
    //double vector to hold num of groups & users in each
    vector <vector<int> > groups;
    reset_depth_pred_groups_score();
    
    int group_id = 0;
    
    /*finds users w/ group id = -1, does bfs,
     updates group id of users w/ depth>1, & incr group id*/
    for (int i = 0; i < user_list.size(); i++)
    {
        if (user_list[i].group == -1)
        {
            bfs (user_list[i].get_id1(), -1);
            
            for (int p = 0; p < user_list.size(); p++)
            {
                if (user_list[p].getDepth() > -1 && user_list[p].group == -1)
                {
                    user_list[p].group = group_id;
                }
            }
            
            group_id++;
        }
    }
    
    
    groups.resize(group_id);
    
    //adds users to their respective groups
    for (int g=0; g < user_list.size(); g++)
    {
        groups[user_list[g].group].push_back(g);
    }
    
    return groups;
    
}
vector<int>Network::suggest_friends(int who, int& score)
{
    reset_depth_pred_groups_score();
    
    bfs (who, -1);
    
    //actual vector to that has id's of users w/ hi score
    vector <int> suggest_friends;
    
    //buffer vector for suggested_friends til max score found
    vector <int> buff_friends;
    
    
    //search for users with depth 2
    for (int i = 0; i < user_list.size(); i++)
    {
        if (user_list[i].getDepth() == 2)
        {
            buff_friends.push_back(i);
        }
        
    }
    
    //returns empty vector if no suggested friends r found
    if (buff_friends.size() == 0)
    {
        //score = -1 to signify no suggested friends
        score = -1;
        return suggest_friends;
    }
    
    
    //friend list of 'who' user
    vector <int> friends = *user_list[who].friends_list();
    
    /*goes thru friends of every user in buff_friends
     to find mutual friends w/ 'who' & incr suggested score*/
    for (int f=0; f < buff_friends.size(); f++)
    {
        vector <int> curr_friends = *user_list[buff_friends[f]].friends_list();
        for (int j=0; j< curr_friends.size(); j++)
        {
            for (int k = 0; k < friends.size(); k++)
            {
                if (curr_friends[j] == friends[k])
                {
                    user_list[buff_friends[f]].sugg_score++;
                }
            }
            
        }
    }
    
    
    int max_score=0;
    //finds max score
    for (int m = 0; m < buff_friends.size(); m++)
    {
        if (user_list[buff_friends[m]].sugg_score > max_score)
        {
            max_score = user_list[buff_friends[m]].sugg_score;
        }
    }
    
    //finds users w/ max score & puts them in suggested_friends
    for (int s = 0; s < buff_friends.size(); s++)
    {
        if (user_list[buff_friends[s]].sugg_score == max_score)
        {
            suggest_friends.push_back(buff_friends[s]);
        }
    }
    
    score = max_score;
    
    return suggest_friends;
    
}
