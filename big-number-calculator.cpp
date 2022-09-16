#include <bits/stdc++.h>
using namespace std;
string clearZeros(string s);
string add(string num1, string num2);
string multiply(string num1, string num2);
bool compare(string num1, string num2);
string substract(string num1, string num2);
bool greaterThanZero(string num);
string divide(string num1, string num2);

string clearZeros(string s)
{
    if (s[0] != '0')
        return s;

    int last0pos=s.rfind('0');
    string res=s.substr(last0pos+1,s.size()-last0pos);
    if(res.size()==0)
        return "0";
    return res;
}
bool compare(string num1, string num2)
{
    if (num2.size() > num1.size())
    {
        return false;
    }
    else if (num2.size() < num1.size())
    {
        return true;
    }
    for (int i = 0; i < num1.size(); i++)
    {
        if (num1[i] != num2[i])
        {
            return num1[i] > num2[i];
        }
    }
    return true;
}
string add(string num1, string num2)
{
    bool isPos=true;
    if(num1[0]=='-'&&num2[0]=='-'){
        num1.erase(0,1);
        num2.erase(0,1);
        isPos=false;
    }
    else if(num1[0]=='-'){
        num1.erase(0,1);
        return substract(num2,num1);
    }
    else if(num2[0]=='-'){
        num2.erase(0,1);
        return substract(num1,num2);
    }

    string zeros="";
    for (int i = 0; i < abs(int(num1.size() - num2.size())); i++)
    {
        zeros += '0';
    }
    if (num1.size() > num2.size())
    {
        num2=zeros+num2;
    }
    else
    {
        num1=zeros+num1;
    }
    int carry = 0;
    string res = "";
    for (int i = num1.size() - 1; i >= 0; i--)
    {
        int num = (num1[i] - '0') + (num2[i] - '0') + carry;

        res=char(num % 10 + '0')+res;
        carry = num / 10;
    }
    if (carry > 0)
    {
        res=char(carry + '0')+res;
    }
    if(!isPos){
        res='-'+res;
    }
    return res;
}
string substract(string num1, string num2)
{
    if (num1 == num2)
        return "0";
    
    if(num1[0]=='-'&&num2[0]=='-'){
        num2.erase(0,1);
        return add(num1,num2);
    }
    if(num1[0]=='-'&&num2[0]!='-'){
        num1.erase(0,1);
        return '-'+add(num1,num2);
    }
    if(num2[0]=='-'){
        num2.erase(0,1);
        return add(num1,num2);
    }
    

    string res = "";
    bool isPos = compare(num1, num2);

    if (!isPos)
        swap(num1, num2);

    string zeros="";
    for (int i = 0; i < abs(int(num1.size() - num2.size())); i++)
    {
        zeros += '0';
    }
    if (num1.size() > num2.size())
    {
        num2=zeros+num2;
    }
    else
    {
        num1=zeros+num1;
    }

    int borrow = 0;
    for (int i = num1.size() - 1; i >= 0; i--)
    {
        int num = num1[i] - num2[i] - borrow;
        if (num < 0)
        {
            borrow = 1;
            num = num + 10;
        }
        else
        {
            borrow = 0;
        }
        res=char(num + '0')+res;
    }
    res = clearZeros(res);
    if (!isPos)
    {
        res='-'+res;
    }
    return res;
}
string multiply(string num1, string num2)
{
    bool isPos=true;
    if((num1[0]=='-'&&num2[0]!='-')||(num1[0]!='-'&&num2[0]=='-'))
        isPos=false;
    if(num1[0]=='-')
        num1.erase(0,1);
    if(num2[0]=='-')
        num2.erase(0,1);

    string res = "";
    for (int i = num1.size() - 1; i >= 0; i--)
    {
        string tempNum = "";
        int carry = 0;
        for (int j = num2.size() - 1; j >= 0; j--)
        {
            int num = (num1[i] - '0') * (num2[j] - '0') + carry;
            tempNum=char(num % 10 + '0')+tempNum;
            carry = num / 10;
        }
        if (carry > 0)
        {
            tempNum=char(carry + '0')+tempNum;
        }
        for (int j = 0; j < num1.size() - 1 - i; j++)
        {
            tempNum += '0';
        }
        res = add(res, tempNum);
    }
    res = clearZeros(res);
    if(!isPos)
        res='-'+res;
    if(res=="-0")
        return "0";
    return res;
}


bool greaterThanZero(string num)
{
    if (num[0] == '-')
        return false;
    return true;
}
string divide(string num1, string num2)
{
    if(num2=="0")
        return "error:divide by 0";

    bool isPos=true;
    if((num1[0]=='-'&&num2[0]!='-')||(num1[0]!='-'&&num2[0]=='-'))
        isPos=false;
    if(num1[0]=='-')
        num1.erase(0,1);
    if(num2[0]=='-')
        num2.erase(0,1);

    if (!compare(num1, num2))
        return "0";
    int zeros = 0;
    string res = "";
    string numMultZero = num2;

    while (greaterThanZero(substract(num1, numMultZero)))
    {
        zeros += 1;
        numMultZero += '0';
    }
    zeros--;
    numMultZero.pop_back();
    for (int i = zeros; i >= 0; i--)
    {
        int posNum = 0;
        while (greaterThanZero(substract(num1, numMultZero)))
        {
            num1 = substract(num1, numMultZero);
            posNum++;
        }
        numMultZero.pop_back();
        res += char(posNum + '0');
    }
    if(!isPos)
        res='-'+res;
    return res;
}

int main()
{
    string s1, s2, choose;
    cout << "1:add\n2:substract\n3:multiply\n4:divide\n";
    while (cin >> choose)
    {
        if (choose == "0")
            return 0;
        else if (choose == "1")
        {
            cin >> s1 >> s2;
            cout << add(s1, s2) << endl;
        }
        else if (choose == "2")
        {
            cin >> s1 >> s2;
            cout << substract(s1, s2) << endl;
        }
        else if (choose == "3")
        {
            cin >> s1 >> s2;
            cout << multiply(s1, s2) << endl;
        }
        else if (choose == "4")
        {
            cin >> s1 >> s2;
            cout << divide(s1, s2) << endl;
        }
        else
        {
            cout << "please enter again" << endl;
        }

        cout << "1:add\n2:substract\n3:multiply\n4:divide\n";
    }
}