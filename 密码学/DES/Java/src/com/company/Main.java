public static void main(String [] args) throws IOException{//main函数，输入主串和模式串
        System.out.print("请输入主串:");
        Scanner sn1 = new Scanner(System.in);
        String s1 = sn1.next();
        System.out.print("请输入模式串:");
        Scanner sn2 = new Scanner(System.in);
        String s2 = sn2.next();
        char [] s3 = s1.toCharArray();
        char [] s4 = s2.toCharArray();
        System.out.print(KMP_test(s3,s4));
        }

public static int KMP_test(char [] s, char [] t){// 主串顺序匹配
    int [] next = next(t);
        int i = 0, j = 0;
        while(i
        if(j == -1 || s[i] == t[j]){
        ++i;
        ++j;
        }else{
        j = next[j];
        }
        }
        System.out.println(i);
        if(j
        return 0;
        }else{
        return i-t.length;
        }
        }

public static int [] next(char [] t){// next函数求解
        int i = 0, j = -1;
        int [] next = new int[t.length];
        next[0] = -1;
        while(i
        if(j == -1 || t[i] == t[j]){
        ++i;
        ++j;
        next[i] = j;
        }
        else
        j = next[j];
        }
        System.out.println(Arrays.toString(next));
        return next;
        }
        对于改进的KMP算法，只需要把next函数换为nextval函数就行了
public static int [] next(char [] t){
        int i = 0, j = -1;
        int [] next = new int[t.length];
        next[0] = -1;
        while(i
        if(j == -1 || t[i] == t[j]){
        ++i;
        ++j;
        if (t[i] != t[j]) {
        next[i] = j;
        } else {
        next[i] = next[j];
        }
        }
        else
        j = next[j];
        }
        System.out.println(Arrays.toString(next));
        return next;
        }