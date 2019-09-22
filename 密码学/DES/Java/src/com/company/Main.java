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
        System.out.print("L0 : ");
        for(int i = 0;i < 28;i++){
            System.out.print(L0[i]);
        }
        System.out.print("\n");
        for(int i = 0;i < PC_1_LTABLE.length;i++){
            R0[i] = Binarykey[PC_1_RTABLE[i] - 1];
        }
        System.out.print("R0 : ");
        for(int i = 0;i < 28;i++){
            System.out.print(R0[i]);
        }
        System.out.println("\n");
        for(int i = 0;i < 16;i++){
            System.out.println("Movetimes : "+i+"\n");
            L0 = result(L0,Movetimes[i]);
            R0 = result(R0,Movetimes[i]);
            int[] mergedKey = new int[56];
            for(int j = 0;j < 28;j++){
                mergedKey[j] = L0[j];
            }
            for(int j = 28;j < 56;j++){
                mergedKey[j] = R0[j-28];
            }
            System.out.print("L0 : ");
            for(int j = 0;j < 28;j++){
                System.out.print(L0[j]);
            }
            System.out.print("\n");
            System.out.print("R0 : ");
            for(int j = 0;j < 28;j++){
                System.out.print(R0[j]);
            }
            System.out.println("\n");

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
    String ClearTxt = "";
    public int[][] Sonkey = new int[16][48];
    public void Main(){
        Key Key = new Key();
        Key.set();
    }
}
public class Main {
    public static void main(String[] args) {
        int[][] Sonkey = new int[16][48];
	    Key Key = new Key();
        Key.set();
        Sonkey = Key.Main();
        System.out.print("\n");
        for(int i = 0;i < 16;i++){
            for(int j = 0;j<48;j++){
                System.out.print(Sonkey[i][j]);
            }
            System.out.print("\n");
        }
    }
}
