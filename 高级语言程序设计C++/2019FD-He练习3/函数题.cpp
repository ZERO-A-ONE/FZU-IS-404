//6-1 2017final友元函数之全班同学的平均绩点 
double averagegrade(student *stu, int count)
{
  int i,j;
  double sum1=0,sum2=0,sum;
  for(i==0;i<count;i++)
    for(j=0;stu[i].score[j]!=-1;j++)
      {
      	sum1+=stu[i].score[j]*(stu[i].grade[j]/10-5);
      	sum2+=stu[i].score[j];
      }
  if(sum2==0||sum1==0)
   return 0;
  return sum1/sum2;
}
//6-2 输出较大或较小值（函数模板）
template <class T>
T m(T x,int task)
{
	T a,b;
	cin>>a>>b;
	if(task==1)
	{
		return a>b?a:b;
	}
	else 
	{
		return a>b?b:a;
	}
}
//6-3 有序数组（类模板）
template<class T>
class MyArray{
private:
    T *data;
    int size;
public:
    MyArray(int s);
    ~MyArray();
    void sort();
    void display();
    bool check();
};
template<class T>
MyArray<T>::MyArray(int s){
        size = s;
        data = new T[size];
        for(int i=0;i<size;i++)
            cin>>data[i];
    }
template<class T>
void MyArray<T>::display(){
    for(int i=0;i<size;i++){
        cout<<data[i];
        if(i<size-1)
            cout<<" ";
    }
    cout<<endl;
}
template<class T>
void MyArray<T>::sort(){
        for(int i=0;i<size-1;i++)
            for(int j=0;j<size-i-1;j++)
                if(data[j]>data[j+1]){
                    T temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
}
//6-4 数组排序输出（函数模板）
template <class A>
void sort(A *a, int size){
	A tmp;
	for(int i = 0;i < size;i++)
	{
		cin >> a[i];
	}
	for(int i = 0;i<size-1;i++)
	{
		for(int j = i;j < size;j++)
		{
			if(a[i]>a[j])
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}
//6-5 单目运算符重载（时钟类）
Clock operator++(Clock& op) {
	op.Second++;
	if (op.Second == 60) {
		op.Second = 0;
		op.Minute++;
	}
	if (op.Minute == 60) {
		op.Minute = 0;
		op.Hour++;
	}
	if (op.Hour == 24) {
		op.Hour = 0;
	}
	return op;
}
Clock operator++(Clock& op, int) {
	Clock t = op;
	op.Second++;
	if (op.Second == 60) {
		op.Second = 0;
		op.Minute++;
	}
	if (op.Minute == 60) {
		op.Minute = 0;
		op.Hour++;
	}
	if (op.Hour == 24) {
		op.Hour = 0;
	}
	return t;
}
//6-6 大整数乘法（运算符重载）
class BigInteger
{
private:
    string str;
public:
    BigInteger() {}
    BigInteger(string s)
    {
        str=s;
    }
    friend ostream&operator<<(ostream &os, BigInteger &bigint)
    {
        os<<bigint.str;
        return os;
    }
    friend istream&operator>>(istream &is,BigInteger &bigint)
    {
        is>>bigint.str;
        return is;
    }
    friend BigInteger operator*( BigInteger &bigint1, BigInteger &bigint2);
};
string reserve(string s)
{
    int l=s.length();
    int j=l-1;
    char temp;
    for(int i=0; i<l/2; i++,j--)
    {
        temp=s[i];
        s[i]=s[j];
        s[j]=temp;
    }
    return s;
}
BigInteger operator*( BigInteger &bigint1, BigInteger &bigint2)
{
    string a=reserve(bigint1.str);
    string b=reserve(bigint2.str);
    if(bigint1.str[0]=='0' || bigint2.str[0]=='0')
    {
        string st="0";
        return BigInteger(st);
    }
    int m,n;
    int *c=new int[a.length()+b.length()+2]();
    for(m=0; m<a.length(); m++)
    {
        for(n=0; n<b.length(); n++)
        {
            c[m+n]+=(a[m]-'0')*(b[n]-'0');
        }
    }
    m--;
    n--;
    int carry=0;
    char *ch=new char[a.length()+b.length()+5];
    int p;
    for( p=0; p<=m+n; p++)
    {
        if(c[p]>9)
        {
            ch[p]=(c[p]+carry)%10+'0';
            carry=(c[p]+carry)/10;
        }
        else
        {
            if(carry+c[p]>9)
            {
                ch[p]=(carry+c[p])%10+'0';
                carry=(carry+c[p])/10;
            }
            else
            {
                ch[p]=carry+c[p]+'0';
                carry=0;
            }
        }
    }
    if(carry>0)
    {
        ch[p]=carry+'0';
        ch[++p]='\0';
    }
    else
        ch[p]='\0';
    string st(ch);
    string s =reserve(st);
    return BigInteger(s);
}