6-1 函数指针（理科实验班）

```c++
bool s2(const Student &a,const Student &b)
{
    int sum1=a.score[0]+a.score[1];
    int sum2=b.score[0]+b.score[1];
    if(sum1>sum2) return true;
    if(sum1==sum2&&a.num<b.num) return true;
    return false;
}
bool s4(const Student& a,const Student& b)
{
    int sum1=a.score[0]+a.score[1]+a.score[2]+a.score[3];
    int sum2=b.score[0]+b.score[1]+b.score[2]+b.score[3];
    if(sum1>sum2) return true;
    if(sum1==sum2&&a.num<b.num) return true;
    return false;
}
int select(const Student s[],int n,bool(*p)(const Student&,const Student&))
{
    Student t=s[0];
    for(int i=1;i<n;i++)if(p(s[i],t))t=s[i];
    return t.num;
}
```

6-2 统计子串在母串出现的次数

```c++
int fun(char *str,char *substr)
{
	int n=0;
	char *strs=substr;
	while(*str!='\0')
	{
		if(*str!=*strs)
		{
			str++;
		}
		else
		{
			str++;strs++;
			if(*str==*strs)
			{
				str++;strs++;
				if(*str==*strs)
				{
					n++;
					strs=substr;
					str++;
				}
				else
				{
					strs=substr;
				}	
			}
			else
			{
				strs=substr;
			}
		}
		
	}
	return n;
 } 
```

6-3 拆分实数的整数与小数部分

```c++
void splitfloat( float x, int *intpart, float *fracpart )
{
    *intpart=(int)x;
    *fracpart=x-*intpart;
}
```

6-4 使用函数实现字符串部分复制

```c++
void strmcpy( char *t, int m, char *s )
{
	int i,flag=1;
	for(i=0;i<m-1;i++)
	{
		t++;
		if(*t=='\0')
		flag=0;
	}
	if(flag)
	while(*t!='\0')
	{
		*s=*t;
		t++;
		s++;
	}
	else
	*s='\0'; 
 } 
```

