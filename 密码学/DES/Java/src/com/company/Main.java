package com.company;
import java.io.*;
import java.util.Scanner;
class HextoBin{
    public String thexString;
    public String outStr;
    public void set(String thex){
        thexString = thex;
        outStr = hexStr2BinStr(thexString);
    }
    public String out(){
        return outStr;
    }
    private static String hexStr =  "0123456789ABCDEF";
    private static String[] binaryArray =
            {"0000","0001","0010","0011",
                    "0100","0101","0110","0111",
                    "1000","1001","1010","1011",
                    "1100","1101","1110","1111"};
    public static String bytes2BinStr(byte[] bArray){
        String outStr = "";
        int pos = 0;
        for(byte b:bArray){
            pos = (b&0xF0)>>4;
            outStr+=binaryArray[pos];
            pos=b&0x0F;
            outStr+=binaryArray[pos];
        }
        return outStr;
    }
    public static String bin2HexStr(byte[] bytes){
        String result = "";
        String hex = "";
        for(int i=0;i<bytes.length;i++){
            hex = String.valueOf(hexStr.charAt((bytes[i]&0xF0)>>4));
            hex += String.valueOf(hexStr.charAt(bytes[i]&0x0F));
            result +=hex;
        }
        return result;
    }
    public static byte[] hexStr2BinArr(String hexString){
        int len = hexString.length()/2;
        byte[] bytes = new byte[len];
        byte high = 0;
        byte low = 0;
        for(int i=0;i<len;i++){
            high = (byte)((hexStr.indexOf(hexString.charAt(2*i)))<<4);
            low = (byte)hexStr.indexOf(hexString.charAt(2*i+1));
            bytes[i] = (byte) (high|low);
        }
        return bytes;
    }
    public static String hexStr2BinStr(String hexString){
        return bytes2BinStr(hexStr2BinArr(hexString));
    }
};
class Key{
    int[] Movetimes = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    int[] PC_1_LTABLE = {57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36};
    int[] PC_1_RTABLE = {63, 55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12, 4};
    int[] PC_2_TABLE = {14, 17, 11, 24, 1, 5,
            3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8,
            16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32};
    public int[] Binarykey = new int[64];
    public int[][] Sonkey = new int[16][48];
    public int len = 0;
    public void set()//(test pass) set Binarykey
    {
        Scanner scan = new Scanner(System.in);
        int[] tmp = new int[64];
        System.out.println("Please input your Key ： ");
        String tmpchar = scan.next();
        HextoBin hexto = new HextoBin();
        hexto.set(tmpchar);
        String str2 = hexto.out();
        for(int i = 0;i < 64;i++){
            Binarykey[i] = str2.charAt(i)-'0';
        }
    }
    public int[] result(int[] txt,int count){
        int lenth = txt.length;
        int[] tmptxt = new int[lenth];
        if(lenth > 28){
            System.out.println("Your Result length is Error");
        }
        else{
            int tmpnum = 0;
            for(int i = count;i < lenth ;i++){
                tmptxt[tmpnum] = txt[i];
                tmpnum ++;
            }
            for(int i = 0;i < count;i++){
                tmptxt[tmpnum+i] = txt[i];
            }
        }
        return tmptxt;
    }
    public int[][] Main(){
        int lenth = Binarykey.length;
        if(lenth != 64){
            System.out.println("Your  Key lenth is Error");
        }
        String BinarykeyST = "";
        for(int i =0;i < lenth;i++){
            BinarykeyST += Binarykey[i];
        }
        System.out.println("Your  Binary Key is : "+BinarykeyST);
        int[] L0 = new int[28];
        int[] R0 = new int[28];
        for(int i = 0;i < PC_1_LTABLE.length;i++){
            L0[i] = Binarykey[PC_1_LTABLE[i] - 1];
        }
        for(int i = 0;i < PC_1_LTABLE.length;i++){
            R0[i] = Binarykey[PC_1_RTABLE[i] - 1];
        }
        for(int i = 0;i < 16;i++){
            L0 = result(L0,Movetimes[i]);
            R0 = result(R0,Movetimes[i]);
            int[] mergedKey = new int[56];
            for(int j = 0;j < 28;j++){
                mergedKey[j] = L0[j];
            }
            for(int j = 28;j < 56;j++){
                mergedKey[j] = R0[j-28];
            }
            int[] tempkey = new int[48];
            for(int j = 0;j < PC_2_TABLE.length;j++){
                tempkey[j] = mergedKey[PC_2_TABLE[j]-1];
            }
            for(int j = 0;j<48;j++){
                Sonkey[i][j] = tempkey[j];
            }
        }
        return Sonkey;
    }
}
class DES{
    private static String intToHex(int n) {
        StringBuffer s = new StringBuffer();
        String a;
        char []b = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        while(n != 0){
            s = s.append(b[n%16]);
            n = n/16;
        }
        a = s.reverse().toString();
        return a;
    }
    private static String hexStr =  "0123456789ABCDEF";
    private static String[] binaryArray =
            {"0000","0001","0010","0011",
                    "0100","0101","0110","0111",
                    "1000","1001","1010","1011",
                    "1100","1101","1110","1111"};
    public static String bin2HexStr(byte[] bytes){
        String result = "";
        String hex = "";
        for(int i=0;i<bytes.length;i++){
            //字节高4位
            hex = String.valueOf(hexStr.charAt((bytes[i]&0xF0)>>4));
            //字节低4位
            hex += String.valueOf(hexStr.charAt(bytes[i]&0x0F));
            result +=hex;  //+" "
        }
        return result;
    }
    String ClearTxt = "";
    public int[] BinaryClearTxt = new int[64];
    public int[][] Sonkey = new int[16][48];
    int[] ret = new int[64];
    public int[] IP(int[] BinaryClearTxt){
        int[] IPTABLE = {58, 50, 42, 34, 26, 18, 10, 2,
                60, 52, 44, 36, 28, 20, 12, 4,
                62, 54, 46, 38, 30, 22, 14, 6,
                64, 56, 48, 40, 32, 24, 16, 8,
                57, 49, 41, 33, 25, 17, 9, 1,
                59, 51, 43, 35, 27, 19, 11, 3,
                61, 53, 45, 37, 29, 21, 13, 5,
                63, 55, 47, 39, 31, 23, 15, 7};
        if(BinaryClearTxt.length != 64){
            System.out.println("Your key Text lenth is Error!");
        }
        else {
            for (int i = 0;i < IPTABLE.length;i++){
                ret[i] = BinaryClearTxt[IPTABLE[i]-1];
            }
            System.out.print("Source ClearText : ");
            for(int i = 0;i<BinaryClearTxt.length;i++){
                System.out.print(BinaryClearTxt[i]);
            }
        }
        return ret;
    }
    public String expend(String Rn){
        int[] ETABLE = {32, 1, 2, 3, 4, 5,
                4, 5, 6, 7, 8, 9,
                8, 9, 10, 11, 12, 13,
                12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21,
                20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29,
                28, 29, 30, 31, 32, 1};
        String retRn = "";
        for(int i =0;i<ETABLE.length;i++){
            retRn += Rn.charAt(ETABLE[i]-1);
        }
        return retRn;
    }
    public String S_sub(String S_Input){
        int[][] STABLE = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
                {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
                {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
                {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
                {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
                {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
                {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
        String retstr = "";
        while (S_Input.length()<48){
            S_Input = "0" + S_Input;
        }
        int index = 0;
        for(int i = 0;i < 8;i++){
            int[] Slist = new int[64];
            for(int j = 0;j < 64;j++){
                Slist[j] = STABLE[i][j];
            }
            int row = (S_Input.charAt(index)-'0')*2+(S_Input.charAt(index+5)-'0');
            int col = (S_Input.charAt(index+1)-'0')*8 + (S_Input.charAt(index+2)-'0')*4+(S_Input.charAt(index+3)-'0')*2+(S_Input.charAt(index+4)-'0');



            String ret_single = Integer.toBinaryString(Slist[row*16+col]);
            while (ret_single.length() < 4){
                ret_single = "0" + ret_single;
            }
            retstr += ret_single;
            index += 6;
        }
        if (retstr.length() != 32){
            System.out.println("Your S_sub retstr lenth is erroe!\n");
        }
        return retstr;
    }
    public String[] P(String Ln,String S_sub_str,String Rn){
        int[] PTABLE = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
                2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
        String tmp = "";
        for(int i = 0;i < PTABLE.length;i++){
            tmp += S_sub_str.charAt(PTABLE[i]-1);
        }
        String Lnnew = "";
        for(int i = 0;i < tmp.length();i++){
            Lnnew += (tmp.charAt(i) - '0') ^ (Ln.charAt(i) - '0');
        }
        while (Lnnew.length()<32){
            Lnnew = "0" + Lnnew;
        }
        if (Lnnew.length()!=32){
            System.out.println("Your Lnnew lenth is error!\n");
        }
        Ln = Rn;
        Rn = Lnnew;
        String[] strstr = new String[2];
        strstr[0] = Ln;
        strstr[1] = Rn;
        return  strstr;
    }
    public String IP_inverse(String L16,String R16){
        int[] IPINVERSETABLE = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
        String tmp = L16 + R16;
        String retstr = "";
        for(int i = 0;i < IPINVERSETABLE.length;i++){
            retstr += tmp.charAt(IPINVERSETABLE[i] - 1);
        }
        if (retstr.length() != 64){
            System.out.println("Your IP_inverse is error!\n");
        }
        return retstr;
    }
    public void Main(){
        Scanner scan = new Scanner(System.in);
        ClearTxt = scan.next();
        HextoBin hexto = new HextoBin();
        hexto.set(ClearTxt);
        String str2 = hexto.out();
        for(int i = 0;i < 64;i++){
            BinaryClearTxt[i] = str2.charAt(i)-'0';
        }
        BinaryClearTxt = IP(BinaryClearTxt);
        int[] tmpLn = new int[32];
        int[] tmpRn = new int[32];
        String Ln = "";
        String Rn = "";

        for(int i = 0;i <32;i++){
            Ln += BinaryClearTxt[i];
        }
        for(int i = 32;i <64;i++){
            Rn += BinaryClearTxt[i];
        }


        Key Key = new Key();
        Key.set();

        Sonkey = Key.Main();


        for(int i = 0;i <16;i++){
            int[] tmpkey = new int[48];
            for(int j = 0;j < 48;j++){
                tmpkey[j] = Sonkey[i][j];
            }
            while (Rn.length() < 32){
                Rn = "0" + Rn;
            }
            while (Ln.length() < 32){
                Ln = "0" + Ln;
            }
            String Rn_expand = expend(Rn);
            String S_input = "";
            String S_sub_str = "";
            for(int j =0;j<48;j++){
                S_input += ((Rn_expand.charAt(j) - '0') ^ (tmpkey[j]));
            }
            S_sub_str = S_sub(S_input);
            String[] StrStr = new String[2];
            StrStr = P(Ln,S_sub_str,Rn);
            Ln = StrStr[0];
            Rn = StrStr[1];
        }
        String tmpp = "";
        tmpp = Ln;
        Ln = Rn;
        Rn = tmpp;
        String re_text = IP_inverse(Ln,Rn);
        int tmnum = 0;
        int tmindex = 0;
        int tmmindex = 3;
        String a = "";
        for(int i =0;i <64;i++){
            if(tmindex == 4){
                tmindex = 0;
                a += hexStr.charAt(tmnum);
                tmnum = 0;
                tmmindex = 3;
            }
            tmnum += Math.pow(2,tmmindex) * (re_text.charAt(i) - '0');
            tmmindex --;
            tmindex ++;
            if(i == 63){
                a += hexStr.charAt(tmnum);
            }
        }
        System.out.println("Your DES Result is : "+re_text);
        System.out.println("Your DES Result is : "+tmnum);
        System.out.println("Your DES Result is : "+a);
    }
}
public class Main {
    public static void main(String[] args) {
        DES des = new DES();
        des.Main();
    }
}
