#ifndef USER_H
#define USER_H
#include <vector>
#include <string>
using std::string;
using std::vector;

class User {
public:
    User (int u_id, int year, int zip_code, string username);
    ~User();

    void add_friend (int id);
    void delete_friend (int id);
    
    //accessor methods that will return
    //just the copies of the private variables
    int get_id1 () const;
    int get_birth_year () const;
    int get_zip () const;
    string get_name () const;
    int getDepth ();
    int getPred ();
    
    //mutator methods for depth and predecessor
    void setDepth (int d);
    void setPred (int p);
    
    //getting friends list
    vector <int>* friends_list();
    
    int group;
    int sugg_score;
    
private:
    
    int id, birth_year, zip;
    string name;
    vector <int> friends;
    
    int depth;
    int predecessor;
    
};


#endif
