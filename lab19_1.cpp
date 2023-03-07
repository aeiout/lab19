#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    string data;
    ifstream source(filename);
    int a,b,c,sum = 0;
    char p[1000];
    while(getline(source,data)){
        char format[] = "%[^:]: %d %d %d";
        sscanf(data.c_str(),format,p,&a,&b,&c);
        sum = a + b + c;
        scores.push_back(sum);
        names.push_back(p);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    string take;
    char A[1000];
    char B[1000];
    getline(cin,take);
    char format[] = "%s %[^\n]";
    sscanf(take.c_str(),format,A,B);
    command = A;
    key = B;
}

void searchName(vector<string>names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------"<< endl;
    bool find = false;
    for(unsigned int i = 0; i < names.size(); i++){
        string K = toUpperStr(names[i]);
        if(K == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            find = true;
        }
        
    }
    if(!find) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}   

void searchGrade(vector<string>names, vector<int> scores, vector<char> grades, string key){
    bool find = false ;
    cout << "---------------------------------"<< endl;
    for(unsigned int i = 0; i < grades.size(); i++){
        char K = key[0];
        char G = toupper(grades[i]);
        if(G == K){
            cout << names[i] << " (" << scores[i] << ")"<< endl;
            find = true;
        }    
    }
    if(!find) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
