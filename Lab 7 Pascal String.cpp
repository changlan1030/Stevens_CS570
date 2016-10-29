//
//  main.cpp
//  Pascal String
//
//  Created by lyu on 15/10/30.
//  Copyright © 2015年 lyuchulin. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include "String.h"

using namespace std;


int main(int argc, const char * argv[]) {
    
    
    int i = 123;
    char s[3];
    //itoa(i,s,10);
    String ss("123iii",true);
    //int len = ss.Length();
    String aa("5678");
    String oo ("",true);
    oo = aa + ss;
    cout << oo << endl;

	bool is = (aa > ss);
	cout << is << endl;

    return 0;
}
