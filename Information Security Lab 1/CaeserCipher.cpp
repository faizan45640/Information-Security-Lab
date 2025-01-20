#include<iostream>
#include<string>
using namespace std;

string CaeserCipher(string text , int key){
    string result = "";
     if(key<0){
            key = 26 + key;
        }
    for(int i=0;i<text.length();i++){
       
        if(isupper(text[i])){
            result += char(int(text[i]+key-65)%26 +65);
        }
        else{
            result += char(int(text[i]+key-97)%26 +97);
        }
    }
   
    return result;

    
}

int main(){

    string text;
    int key;
    cout<<"Enter Text"<<endl;
    
    getline(cin,text);

    cout<<"Enter key: ";
    cin>>key;

    cout<<CaeserCipher(text,key);


}