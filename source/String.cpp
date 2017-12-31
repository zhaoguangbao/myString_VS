#include "stdafx.h"
#include "String.h"
#include <string.h>
#include <iostream>

using namespace myString;

String::String()
{
    rep=new Srep(0," ");
}

//String str1("char_str");
//String str2(str1);
String::String(const String& str)
{
    str.rep->n++; //复制构造标记n++ / const ??
    rep=str.rep;//rep.operator=(str.rep);
}

//String str("char_str");
String::String(const char* cstr)//作为隐式转换构造函数，实现"char_str"作为文字量
{
    rep=new Srep(strlen(cstr),cstr);
}

String::~String()
{
	/*if (--rep->n == 0)//对当前字符串只有一个引用时，离开作用域时析构删除
	{
		delete rep;
		rep = 0;
	}*/
    rep->n--;
    if(rep->n==0)
        delete rep;
}

//String str1="char_str1";
//String str2("char_str2");
//String str2=str1;
String& String::operator=(const String& str)
{
	//if ((*this) == str)
		//throw Assign("Forbit assinment from self!");
	str.rep->n++;//同复制构造相同，复制赋值时标记n++
    if(--rep->n==0)
        delete rep; //若赋值前指向该字符串的只有一个对象，则在赋值后删除原对象
    rep=str.rep;
    return *this;
}

//String str="char_str";
String& String::operator=(const char* cstr)
{
    if(rep->n==1) //若当前指向该内存的只有一个对象则可对该区域做任意修改
        rep->assign(strlen(cstr),cstr);
    else//若指向该内存的不止一个对象则新开辟内存存储新的字符串量
    {
        rep->n--;
        rep=new Srep(strlen(cstr),cstr);
    }
    return *this;
}

String& String::operator+=(const String& str)
{
    strcat(rep->s,str.rep->s);
    return *this;
}
String& String::operator+=(const char* cstr)
{
    strcat(rep->s,cstr);
    return *this;
}

//friend function/在class外部时也不能访问类的私有成员
String operator+(const String& str1,const String& str2)
{
    String strTemp=str1;
    strTemp+=str2;
    return strTemp;
}
/*String operator+(const String& str1,const char* cstr)
{
    String strTemp=str1;
    strTemp+=cstr;
    return strTemp;
}*/

/*extern std::ostream cout;
extern std::istream cin;*/

String::Cref String::operator[](int i)
{
    check(i);
    return Cref(*this,i);
}

const char* String::my_c_str()
{
	Cstr* cstr = new Cstr(*this);
	for (int i = 0; i < rep->sz; i++)
		cstr->pStr[i] = rep->s[i];
	return cstr->pStr;
}


