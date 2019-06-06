#include<iostream>
#include<algorithm>
#include<string>
#include<stdio.h>
using namespace std;
struct student
{
	string name;
	int num;
	int c_score;
	int elscore;
	int mathscore;
};
int main()
{
	student a;
	cin >> a.name;
	cin >> a.name;
	cin >> a.c_score;
	cin >> a.elscore;
	cin >> a.mathscore;
	int all = a.c_score+a.elscore+a.mathscore;
	double pj = all/3.0;
	cout << all << endl;
	printf("%.3lf",pj);
	return 0;
}