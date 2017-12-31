#ifndef __MY_STRING_H_
#define __MY_STRING_H_

#include <string.h> //
#include <iostream>

namespace myString //该逻辑注重对string pool的实现
{
	const int maxsize = 100;

	class Range{};
	
    struct Srep//string pool
    {
        char *s;
        int sz;
        int n;//作为指向同一个字符串对象个数的标记
        Srep(int nsz,const char* p)
        {
            n=1;
            sz=nsz;
            s=new char[sz+1];
            strcpy(s,p);
        }
        ~Srep()
        {
            delete[] s;
			s = 0;
        }
        Srep* get_own_copy()//返回副本
        {
            if(1==n)
                return this;
            n--;
            return new Srep(sz,s);
        }
        void assign(int nsz,const char* p)
        {
            if(sz!=nsz) //复制赋值时删除原内存，若赋值前后字符串长度相同则不需要开辟新内存
            {
                delete[] s;
                sz=nsz;
                s=new char[sz+1];
            }
            strcpy(s,p);
        }
    private:
        Srep(const Srep&);//禁止复制构造
        Srep& operator=(const Srep&);//禁止复制赋值
    };
    class String
    {
        Srep *rep;
    public:
        class Cref;
		friend class Cstr;
        //constructor
        String();
        String(const char*);
        String(const String&);

        //operator
        String& operator=(const char*);
        String& operator=(const String&);

        String& operator+=(const String&);
        String& operator+=(const char*);

        friend std::ostream& operator<<(std::ostream& out,const String& str)
        {
            out<<str.rep->s;
            return out;
        }
        friend std::istream& operator>>(std::istream& in,String& str)
        {
			in.getline(str.rep->s, maxsize);
			//str.rep->sz = strlen(str.rep->s);//非c风格的字符串故strlen无法获取str.rep->s的长度
			str.rep->sz = static_cast<int>(in.gcount()-1);
            return in;
        }

        friend bool operator==(const String& str1,const String& str2)
        {
			return (strcmp(str1.rep->s, str2.rep->s) == 0);
        }
        friend bool operator!=(const String& str1,const String& str2)
        {
			return (strcmp(str1.rep->s, str2.rep->s) != 0);
        }

        //deconstructor
        ~String();

        //[]
        void check(int i) const
        {
            if(i<0 || (rep->sz)<=i)
                throw Range();
        }
        char read(int i) const
        {
            return rep->s[i];
        }
        void write(int i,char c)
        {
            rep=rep->get_own_copy();
            rep->s[i]=c;
        }
		const char* my_c_str();

        Cref operator[](int i);
    };

    //assist function
    String operator+(const String&,const String&);
    //String operator+(const String&,const char*);//test function: String(const char*);

    class String::Cref
    {
        friend class String;//
        String& s;
        int i;
        Cref(String& ss,int ii):s(ss),i(ii) {} //const string& ss -- error
    public:
        operator char()
        {
            return s.read(i);   //隐式转换为char型
        }
        void operator=(char c)
        {
            s.write(i,c);
        }
    };


	class Cstr
	{
	public:
		//friend class String;
		char *pStr;
		Cstr(const String& str)
		{
			pStr = new char[str.rep->sz+1];
			pStr[str.rep->sz] = '\0';
		}
		~Cstr()
		{
			delete[] pStr;
		}
	};

};


#endif // __MY_STRING_H_
