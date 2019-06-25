#include <iostream>
using namespace std;
const int N=200;
void delchar(char* a, char ch){
      char *p, *q;
      p=q=a;
      while(*p!='\0'){
              if(*p!=ch){
                   *q=*p;
                   q++;
              }
              p++;
        }
        *q='\0';
}
int main(){
      int repeat, i;
      char a[N], ch;
      cin>>repeat;
       for(i=0; i<repeat; i++){
              cin.get(ch);
              cin.getline(a,N);
              cin.get(ch);
              delchar(a, ch);
              cout<<"result: "<<a<<endl;
       }
      return 0;
}
