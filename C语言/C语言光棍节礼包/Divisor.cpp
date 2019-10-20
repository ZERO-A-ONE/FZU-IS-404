#include <iostream> 
#include <algorithm> 
#include <iterator> 
#include <cstdio> 
#include <cstdlib> 
#include <cmath> 
#include <cstring> 
#include <vector> 
#include <queue> 
#include <set> 
using namespace std; 
#define ll long long 
int main() 
{ 
  // freopen("s.cpp","r",stdin); 
  ll n; 
  while(scanf("%lld",&n) != EOF) 
  { 
    if(!n) break; 
  
    ll sum = 1; 
    /* x = p1^a1*p2^a2*p3^a3...pk^ak 
    yueshu = (a1+1)*(a2+1)*...*(ak+1)*/
    for(ll i = 2; i*i <= n; i++){ 
      int cou = 0; 
      if(n%i==0){ 
        cou = 1; 
        n /= i; 
        while(n%i==0){ 
          cou++; 
          n /= i; 
        } 
      } 
      if(cou != 0){ 
        sum = sum*(cou+1); 
      } 
    } 
    if(n != 1){ 
      sum = sum*2; 
    } 
    if(sum==1 && n==1){ 
      sum = 1; 
    } 
    printf("%lld\n",sum); 
  } 
  return 0; 
} 
