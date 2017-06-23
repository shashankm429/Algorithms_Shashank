#include<bits/stdc++.h>
using namespace std;
string multiply(string,string);
int main()
{
    string s1 = "3141592653589793238462643383279502884197169399375105820974944592";
    string s2 = "2718281828459045235360287471352662497757247093699959574966967627";
    cout << multiply(s1, s2);
    return 0;
}
string multiply(string num1, string num2)
{
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0)
       return "0";
    vector<int> output(n1 + n2, 0);
    int c1 = 0;
    int c2 = 0;
    for (int i=n1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
        c2 = 0;
        for (int j=n2-1; j>=0; j--)
        {
            int n2 = num2[j] - '0';
            int sum = n1*n2 + output[c1 + c2] + carry;
            carry = sum/10;
            output[c1 + c2] = sum % 10;

            c2++;
        }
        if (carry > 0)
            output[c1 + c2] += carry;
        c1++;
    }
    int i = output.size() - 1;
    while (i>=0 && output[i] == 0)
       i--;
    if (i == -1)
       return "0";
    string s = "";
    while (i >= 0)
        s += to_string(output[i--]);

    return s;
}

