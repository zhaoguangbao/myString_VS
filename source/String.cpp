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
    str.rep->n++; //���ƹ�����n++ / const ??
    rep=str.rep;//rep.operator=(str.rep);
}

//String str("char_str");
String::String(const char* cstr)//��Ϊ��ʽת�����캯����ʵ��"char_str"��Ϊ������
{
    rep=new Srep(strlen(cstr),cstr);
}

String::~String()
{
	/*if (--rep->n == 0)//�Ե�ǰ�ַ���ֻ��һ������ʱ���뿪������ʱ����ɾ��
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
	str.rep->n++;//ͬ���ƹ�����ͬ�����Ƹ�ֵʱ���n++
    if(--rep->n==0)
        delete rep; //����ֵǰָ����ַ�����ֻ��һ���������ڸ�ֵ��ɾ��ԭ����
    rep=str.rep;
    return *this;
}

//String str="char_str";
String& String::operator=(const char* cstr)
{
    if(rep->n==1) //����ǰָ����ڴ��ֻ��һ��������ɶԸ������������޸�
        rep->assign(strlen(cstr),cstr);
    else//��ָ����ڴ�Ĳ�ֹһ���������¿����ڴ�洢�µ��ַ�����
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

//friend function/��class�ⲿʱҲ���ܷ������˽�г�Ա
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


