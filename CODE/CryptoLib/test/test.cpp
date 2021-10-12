//
//  main.cpp
//  RSA
//
//  Created by liujan on 10/21/14.
//  Copyright (c) 2014 liujan. All rights reserved.
//
 
#include <iostream>
#include "cmath"
using namespace std;
 
long long p = 1949, q = 3413;
long long N = p * q;
long long e = 13007, d = 511;
 
//对a的b次幂取模 m（大数取模）
long long Mod(long long a, long long  b, long long m){
    long long r = 1;
    for (long long j = 0; j < b; j++){
        r = (r * a) % m;
        
    }
    return r;
}
 
//对输入信息进行rsa编码
long long * rsaEncode(string message){
    size_t length = message.length();
    long long *ascii = new long long[length]; //存储信息的每个字符
    long long *code = new long long[length];  //存储每个字符的rsa编码
    for (size_t i = 0; i < length; i++){
        ascii[i] = message[i];
    }
 
    for (size_t i = 0; i < length; i++){
        code[i] = Mod(ascii[i], e, N ); //C=M^e (modN)
    }
    
    return code;
}
 
//根据rsa编码得到原来的信息
string rsaDecode(long long code[], size_t n){
    long long  *ascii = new long long[n];
    string message = "";
    for (size_t i = 0; i < n; i++){
        ascii[i] = Mod(code[i], d, N); //M=C^d (modN)
        message += ((char)(ascii[i]));
    }
    return message;
}
 
int main(int argc, const char * argv[]) {
 //   string message = "Hello World!";
    string message;
    cin >> message;
    size_t length = message.length();
    long long *a = rsaEncode(message);
    
    
    string newmessage = rsaDecode(a, length);
    cout << newmessage << endl;
    
    return 0;
}
