//
//  String.h
//  Pascal String
//
//  Created by lyu on 15/10/30.
//  Copyright © 2015年 lyuchulin. All rights reserved.
//
#include <iostream>
#include <cassert>
#include <stdlib.h>
#ifndef String_h
#define String_h

using namespace std;

class String {
public:
	friend bool getType(const String tmp) {
		return tmp.pascal;
	}
    String(){
        rep = new char[1];
        rep[0] = static_cast<char> ('/0');
        len = 0;
    }
    
    String( const char *s){

        len = 0;
        const char *tmp = s;
        while (*tmp) {
            ++len;
            ++tmp;
        }
        
        rep = new char[len + 1];
        for (int i = 0; i <= len; i++) {
            rep[i] = s[i];
        }
    }
    
    String( const String &obj){
        len = 0;
        char *tmp = obj.rep;
        while (*tmp) {
            ++len;
            ++tmp;
        }
        
        rep = new char [len + 1];
        for (int i = 0; i <= len; i++) {
            rep[i] = obj.rep[i];
        }
    }
    
    String(const char *str, bool pascal){
		this->pascal = pascal;
        if (!pascal) {
			len = 0;
			const char *tmp = str;
			while (*tmp) {
				++len;
				++tmp;
			}

			rep = new char[len + 1];
			for (int i = 0; i <= len; i++) {
				rep[i] = str[i];
			}
        }else{
            len = 0;
            const char *tmp = str;
            while (*tmp) {
                ++len;
                ++tmp;
            }
            char num = static_cast<char> (len);
           // cout << len << endl;
            rep = new char[len + 1];
            rep[0] = num;
            //cout << rep[0] << endl;
            for (int i = 1; i <= len; ++i) {
                rep[i] = str[i-1];
            }
        }
        
    }
    
    ~String(){
        //delete [] rep;
        len = 0;
    }
    
    const String& operator=( const String &rhs ){
		if (this->pascal != rhs.pascal)
			this->pascal = rhs.pascal;
		len = rhs.len;
		//delete[] rep;
		rep = new char[len + 1];
		for (int i = 0; i <= len; i++) 
			rep[i] = rhs.rep[i];
        return *this;
    }
    
    char& operator[]( int index){
        assert(index < len && index >= 0);
        return rep[index];
    }
    
    char operator[]( int index) const{
        assert(index < len && index >= 0);
        return rep[index];
    }
    
    int Length() const{
        
        return len;
    }
    
    friend bool operator==(const String &lhs, const String &rhs){
        if (lhs.Length() == 0) {
            if (rhs.Length() == 0) {
                return true;
            }else{
                return false;
            }
        }else{
            
            int shorter = lhs.Length();
            if (rhs.Length() < shorter) {
                shorter = rhs.Length();
            }
            for (int i = 0;  i < shorter; i++) {
                if (lhs.rep[i] == rhs.rep[i]) {
                    continue;
                }else{
                    return false;
                }
            }
            if (lhs.Length() == rhs.Length()) {
                return true;
            }else{
                return false;
            }
        }
    }
    
    
    
    friend bool operator<(const String &lhs, const String &rhs){
        if (lhs.Length() == 0) {
            if (rhs.Length() == 0) {
                return false;
            }else{
                return true;
            }
        }else{
            int shorter = lhs.Length();
            if (rhs.Length() < shorter) {
                shorter = rhs.Length();
            }
            for (int i = 1; i < shorter; i++) {
                if (lhs.rep[i] == rhs.rep[i]) {
                    continue;
                }else if (lhs.rep[i] < rhs.rep[i]){
                    return true;  ///????true?
                }else{
                    return false;
                }
            }
            if (lhs.Length() == rhs.Length()) {
                return false;
            }else if (lhs.Length() < rhs.Length()){
                return true;
            }else{
                return false;
            }
        }
    }
    
    friend bool operator>(const String &lhs, const String &rhs){
        return (rhs < lhs);
    }
    
    friend bool operator<=(const String &lhs, const String &rhs){
        return !(rhs < lhs);
    }
    
    friend bool operator>=(const String &lhs, const String &rhs){
        return !(lhs < rhs);
    }
    
    friend bool operator!=(const String &lhs, const String &rhs){
        return !(lhs == rhs);
    }
    

    friend String operator+(String &lhs, String &rhs){
			
		String left, right;
		bool tmp = false;

		if (lhs.pascal) {
			left = lhs.convert_to_str(lhs);
			tmp = true;
		}
		else
			left = lhs;
		if (rhs.pascal)
			right = lhs.convert_to_str(rhs);
		else
			right = rhs;

            int strLength = left.len + right.len + 1;
            char *temStr = new char[strLength];
            for (int i = 0; i <= left.len; ++i) {
                temStr[i] = left.rep[i];
            }
            for (int i = 0; i <= right.len; ++i) {
                temStr[left.len + i] = right.rep[i];
            }

			String retStr(temStr, tmp);

            //delete [] temStr;
            return String(temStr, tmp);
        
        
        
        
    }
    
    const char* C_StyleString() const{
        return rep;
    }
    
    friend ostream& operator<<( ostream &out, String &obj){
		if (obj.pascal)
			obj = obj.convert_to_str(obj);
        return out << obj.C_StyleString();
    }
    
private:
    
    char *rep;
    int len;
    bool pascal = false;

	String convert_to_str(String & pascalStr) {
		if (!pascalStr.pascal)
			return pascalStr;
		else {
			int num = static_cast<int> (pascalStr[0]);
			int strLength = num;
			char *temStr = new char[strLength];
			for (int i = 1; i <= num; ++i) {
				temStr[i-1] = pascalStr.rep[i];
			}
			temStr[strLength] = '\0';
			String retStr(temStr);
			//delete[] temStr;
			return retStr;
		}
		
	}

	String convert_to_pascal(const String & Str) {
		if (Str.pascal)
			return Str;
		else {
			String retStr(Str.rep, true);
			return retStr;
		}

	}
};


#endif /* String_h */
