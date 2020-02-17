// Example program
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

unsigned test_size = 3;

string solve( int ,  string );

class node {
    
    public:
    
    
    private:
        unsigned rep_cnt;
        string chars;
    
};

int main()
{
    string input_tests[test_size] = {"5[abc]4[ab]c", "2[3[a]b]", "5[4[3[2[1[hi]]]]]"};
    
    for(unsigned i = 0; i < test_size; i++){
        cout << "Test #" << i+1 << ": " << endl;
        cout << "Answer: ";
        solve(0, input_tests[i]);
        cout << endl << "=======================" << endl;
        
    }
    
}

int countAmount(char c, string input){
    int cntr = 0;
    int lb_cnt = 1;
    for(unsigned i = 0; i < input.size(); i++){
        if(input[i] == c)
            cntr++;
        if(input[i] == ']')
            lb_cnt--;
        if(lb_cnt == 0)
            return cntr;
    }
    return cntr;
}

int getRepCount(string input ){
    // Gets number of occurences for its wrapped string
    size_t first_lb_loc = input.find('[');
    return stoi(input.substr(0, first_lb_loc));
}

bool noBrackets(string input){
    for(unsigned i = 0; i < input.size(); i++){
        if(input[i] == '[' || input[i] == ']')
            return false;
    }
    return true;
}

void setupStrings(string& relevant_str, string& remaining_str, string input){
    if(noBrackets(input)){
        relevant_str = input;
        return;
    }
    size_t first_lb_loc = input.find('[');
    string butchered_str = input.substr(first_lb_loc, input.size());
    int curr_lb_cnt = countAmount('[', butchered_str);
        //cout << "Amount of '[' in group " << butchered_str << ": " << curr_lb_cnt << endl;
    
    int cut_loc = -1;
    for(unsigned i = 0; i < butchered_str.size(); i++){
        
        if(curr_lb_cnt <= 0){
            break;
        }
        
        if(butchered_str[i] == ']'){
            //cout << "Found rb at indx: " << i << endl;
            cut_loc = i;
            curr_lb_cnt--;
        }
        
    }
    if(cut_loc < 0)
        cout << "ERROR" << endl;
    
    // Offset ending of _lb until string ends or another lb is spotted
    
    relevant_str = butchered_str.substr(0, cut_loc+1);
    remaining_str = butchered_str.substr(cut_loc+1, butchered_str.size());
}

bool anyNums(string a){
    for(unsigned i = 0; i < a.size(); i++){
        if(a[i] == '0' || a[i] == '1' || a[i] == '2' || a[i] == '3' || a[i] == '4' || a[i] == '5' || a[i] == '6' || a[i] == '7' || a[i] == '8' || a[i] == '9')
            return true;
    }
    return false;
}

string prepareString(string a){
    if(a[0] == '['){
        a = a.substr(1, a.size()-2);
    }
    return a;
}

string solve(int lb_cnt, string input ){
    
    int rep_cnt = 1;
    string relevant_str;
    string remaining_str;
    
    if(isdigit(input[0]))
        rep_cnt = getRepCount(input);
    
    setupStrings(relevant_str, remaining_str, input);
    
    //cout << "REMAINING STR: " << remaining_str << endl;
    //cout << "BUCKET STRING: " << relevant_str << " to be repeated " << rep_cnt << " times" << endl;
    
    // Output
    
    if(anyNums(relevant_str) == false){ // Non-recursive
        //cout << "hi" << endl;
        for(unsigned i = 0; i < rep_cnt; i++){
            for(unsigned j = 0; j < relevant_str.size(); j++){
                if(relevant_str[j] != '[' && relevant_str[j] != ']')
                    cout << relevant_str[j];
            }
        }
        //cout << endl;
        
        if(remaining_str.size()){
            remaining_str = prepareString(remaining_str);
            solve(0, remaining_str);
        }
        
    } else { // Recursive
        //cout << "bye" << endl;
        relevant_str = prepareString(relevant_str);
        
        for(unsigned i = 0; i < rep_cnt; i++){
            solve(0, relevant_str);
        }
        
    }
   
   return "";
    
}
