#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class TwoInput {
public:
    int andd (int i , int j){
        return i && j;
    }
    int orr(int i , int j){
        return i || j;
    }
};
class OneInput{
public:
    int nott(int i){
        if (i == 1)
            return 0;
        else
            return 1;
    }
};
class property: public TwoInput, public OneInput{
public:
    string id;
    string type;

};
void getInfo(int x , property gate[100]){
    cout << "First enter type of gates (and ,or , not) then enter ID of gates"<<endl;
    //get info about gates
    for(int i=0;i<x;i++){
        cin >> gate[i].type;
        cin >> gate[i].id;
    }
    return;
}
int main()
{
    cout <<"Enter how much gates do you have"<<endl;
    int x;
    cin >> x;
    property gate[100];
    getInfo(x , gate);
    //get starters gates
    string start;
    cin.ignore();
    cout << "Enter primary gates and write (start gates)"<<endl;
    getline(cin , start);
    //erase comment in front of starters gates
    start.erase(start.find('(') , start.size());
    //separate starter gates
    stringstream iss(start);
    string starter[10];
    int l=0;
    while(iss >> starter[l])
        l++;
    //get end gate
    cout << "Enter ender gate and write (end gate)"<<endl;
    string ender;
    cin >> ender;
    //ignore comment in front of end gate
    cin.ignore(11,'/n');
    string connect[100];
    int j=0;
    cin.ignore();
    //get plan and connection between gates
    cout << "Enter plan"<<endl<<"(if you don't know how to set plan please read readme)"<<endl;
    while(getline(cin , connect[j])){
        if(connect[j].substr(0, connect[j].find(' '))==ender)
            break;
        j++;
    }
    // result save answer of gates
    int result[x];
    // input save input of starter gates
    char input[100];
    cin >> input;
    int m =0;
    //set input in starters gates and save answer in result
    for(int i=0;starter[i]!="\0";i++){
        for(int k=0;gate[k].id != "\0" ;k++){
            if (gate[k].id == starter[i]){
                if(gate[k].type == "not"){
                    result[k]=gate[k].nott(int(input[m])-48);
                    m++;
                }
                else if(gate[k].type == "and"){
                    result[k]=gate[k].andd(int(input[m])-48,int(input[m++])-48);
                    m++;
                }
                else if(gate[k].type == "or"){
                    result[k]=gate[k].orr(int(input[m])-48,int(input[m++])-48);
                    m++;
                }
            }
        }
    }
    // follow plan
    for(int n=0;n<=j;n++){
        //root is the gate that will get answer of other gate or gates
        stringstream con (connect[n]);
        string root;
        con >> root;
        int i;
        // detect with gate means to be root
        for(i=0;gate[i].id != root;i++){}
        //set answer of gates for input of root
        if(gate[i].type == "not"){
            string root1;
            con >> root1;
            int k;
            for(k=0;gate[k].id != root1;k++){}
            result[i]=gate[i].nott(result[k]);
        }
        else{
            string root1 , root2;
            int k , b;
            con >> root1;
            con >> root2;
            for(k=0;gate[k].id != root1;k++){}
            for(b=0;gate[b].id != root2;b++){}
            if(gate[i].type == "or")
                result[i]=gate[i].orr(result[k] , result[b]);
            else
                result[i]=gate[i].andd(result[k] , result[b]);
        }
    }
    cout << "your answer is : ";
    int i;
    for( i=0;gate[i].id !=  ender;i++){}
    cout <<result[i];
    return 0;
}
