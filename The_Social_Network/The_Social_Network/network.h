#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"

class Network {
public:
    Network();
    ~Network();
    
    int read_friends(const char *filename);
    int write_friends(const char *filename);
    void add_user(std::string username, int yr, int zipcode);
    int add_connection(std::string name1, std::string name2);
    int remove_connection(std::string name1, std::string name2);
    
    int get_id(std::string username);
    string get_nom(int id);
    
    void print_users ();
    void print_friends(string name);
    
    
    vector<int>shortest_path(int from, int to);
    vector<vector<int> >groups();
    vector<int> suggest_friends(int who, int& score);
    void bfs (int s, int f);
    void reset_depth_pred_groups_score ();
    
    
private:
    
    std::vector <User> user_list;
    
};


#endif
