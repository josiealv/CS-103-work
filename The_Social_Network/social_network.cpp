#include "network.h"
#include "user.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

//function that concatanates first & last names into 1 string
string full_name (string first_name, string last_name)
{
    string full_name = first_name + " " + last_name;
    return full_name;
}

int main(int argc, char *argv[])
{
    
    int file_open;
    
    Network run; //object for network class
    
    //check if filename is valid
    file_open = run.read_friends (argv[1]);
    
    if (file_open == -1)
    {
        cout << "Couldn't open file. Please enter valid file name" << endl;
        return 1;
    }
    
    int menu_options = 0; //0 to enter loop & keep it running
    
    while (menu_options >= 0 && menu_options < 10)
    {
        cout << "Please choose one of the following options "
        << "or type 'q' to quit" << endl;
        
        cout << "Option 1. Add a user" << endl;
        cout << "Option 2. Add friend connection" << endl;
        cout << "Option 3. Remove friend connection" << endl;
        cout << "Option 4. Print users" << endl;
        cout << "Option 5. List friends" << endl;
        cout << "Option 6. Write to file" << endl;
        cout << "Option 7. Shortest Path" << endl;
        cout << "Option 8. Disjoint Sets" << endl;
        cout << "Option 9. Friend Suggestions" << endl;
        
        cin >> menu_options;
        if (cin.fail())
        {
            break;
        }
        
        if (menu_options == 1)
        {
            int year;
            int zip_code;
            
            //dynamically allocated strings to get first & last name
            string* u_name_first = new string;
            string* u_name_last = new string;
            
            cin >> *u_name_first >> *u_name_last >> year >> zip_code;
            
            //creates string of full name of user
            string u_name = full_name (*u_name_first, *u_name_last);
            
            delete u_name_first;
            delete u_name_last;
            
            run.add_user(u_name, year, zip_code);
        }
        else if (menu_options==2)
        {
            //same as above but for 1st user's 1st & last name
            string* first_first = new string;
            string* first_last = new string;
            
            //same as above but for 2nd user's 1st & last name
            string* second_first = new string;
            string* second_last = new string;
            
            cin >> *first_first >> *first_last >>
            *second_first >> *second_last;
            
            //same as above for 1st user
            string name1 = full_name(*first_first, *first_last);
            //same as above for 2nd user
            string name2 = full_name(*second_first, *second_last);
            
            delete first_first;
            delete first_last;
            delete second_first;
            delete second_last;
            
            int worked_for_add;
            worked_for_add = run.add_connection(name1, name2);
            if (worked_for_add == -1)
            {
                cout << "Couldn't find 1 or more users. Try again" << endl;
            }
            
        }
        else if (menu_options==3)
        {
            //same as above
            string* first_first_d = new string;
            string* first_last_d = new string;
            string* second_first_d = new string;
            string* second_last_d = new string;
            
            cin >> *first_first_d >> *first_last_d >>
            *second_first_d >> *second_last_d;
            
            //same as above
            string name1_delete = full_name(*first_first_d, *first_last_d);
            string name2_delete = full_name(*second_first_d, *second_last_d);
            
            delete first_first_d;
            delete first_last_d;
            delete second_first_d;
            delete second_last_d;
            
            
            int worked_4_delete;
            worked_4_delete = run.remove_connection(name1_delete, name2_delete);
            if (worked_4_delete == -1)
            {
                cout << "Couldn't find 1 or more users. Try again" << endl;
            }
            
        }
        else if (menu_options == 4)
        {
            run.print_users();
        }
        else if (menu_options == 5)
        {
            //dynamically allocated strings to get 1st & last name
            //of user whose friends list we want to print
            string* name_p_first = new string;
            string* name_p_last = new string;
            
            cin >> *name_p_first >> *name_p_last;
            
            //creates string of full name of user
            string name_print_friends = full_name(*name_p_first, *name_p_last);
            
            delete name_p_first;
            delete name_p_last;
            
            run.print_friends(name_print_friends);
        }
        else if (menu_options == 6)
        {
            string filename;
            cin >> filename;
            
            int make_new_file = run.write_friends(filename.c_str());
            
            //checks if filename was valid
            if (make_new_file == -1)
            {
                cout << "Invalid file name. Try again." << endl;
            }
        }
        else if (menu_options == 7)
        {
            //dynamically allocated strings to get 1st & last names
            string* from_name_1st = new string;
            string* from_name_last = new string;
            string* to_name_1st = new string;
            string* to_name_last = new string;
            
            cin >> *from_name_1st >> *from_name_last >>
            *to_name_1st >> *to_name_last;
            
            //creates full names
            string from_name = full_name (*from_name_1st, *from_name_last);
            string to_name = full_name (*to_name_1st, *to_name_last);
            
            delete from_name_1st;
            delete from_name_last;
            delete to_name_1st;
            delete to_name_last;
            
            //checks if starting user = final user
            if (from_name == to_name)
            {
                cout << "Distance: 0" << endl;
            }
            else
            {
                
                int from_id, to_id;
                
                from_id = run.get_id(from_name);
                to_id = run.get_id(to_name);
                
                vector <int> smallest_path = run.shortest_path (from_id, to_id);
                
                //checks if path was found
                if (smallest_path.size() == 0)
                {
                    cout << "None" << endl;
                }
                else
                {
                    cout << "Distance: " << smallest_path.size()-1 << endl;
                    
                    //prints out actual path
                    for(int i = 0; i < smallest_path.size(); i++)
                    {
                        int curr_id = smallest_path[i];
                        
                        //(nombre is name in Spanish)
                        string nombre = run.get_nom(curr_id);
                        
                        if (curr_id != to_id)
                        {
                            cout << nombre << " "<< "->" << " ";
                        }
                        else
                        {
                            cout << nombre;
                        }
                    }
                    
                }
            }
            cout << endl;
        }
        else if (menu_options == 8)
        {
            vector<vector<int> > dis_sets = run.groups();
            
            //prints out all sets & the user's in them
            for(int i=0; i< dis_sets.size(); i++)
            {
                cout << "Set " << i << " => ";
                for (int j = 0; j < dis_sets[i].size(); j++)
                {
                    int u_id = dis_sets[i][j];
                    
                    //(nome is name in Italian)
                    string nome = run.get_nom(u_id);
                    
                    if (j != dis_sets[i].size()-1)
                    {
                        cout << nome << ", ";
                    }
                    else
                    {
                        cout << nome;
                    }
                    
                }
                cout << endl;
            }
            
        }
        else if (menu_options == 9)
        {
            //dynamically allocated strings to get 1st & last names
            
            string* nombre_de_pila = new string; //1st name
            string* apellido = new string;       //last name
            
            cin >> *nombre_de_pila >> *apellido;
            
            //creates full name
            string nombre = full_name (*nombre_de_pila, *apellido);
            
            delete nombre_de_pila;
            delete apellido;
            
            int who_id = run.get_id(nombre);
            
            //runs if who_id is in user list
            if (who_id != -1)
            {
                int hi_score = 0;
                
                vector <int> s_friends = run.suggest_friends(who_id, hi_score);
                
                //checks if there are friends to suggest
                if (hi_score == -1)
                {
                    cout << "None" << endl;
                }
                else
                {
                    cout << "The suggested friend(s) is/are:" << endl;
                    
                    //prints out all suggested friends and highest score
                    for (int i = 0; i < s_friends.size(); i++)
                    {
                        int m_id = s_friends[i];
                        string m_name = run.get_nom(m_id);
                        
                        cout << setw(3) << std::left << " ";
                        cout << m_name;
                        cout << setw(17-m_name.size())<< std::right<< " ";
                        cout << "Score: " << hi_score << endl;
                    }
                }
                
            }
            
        }
        
    }
    
    
    return 0;
}
