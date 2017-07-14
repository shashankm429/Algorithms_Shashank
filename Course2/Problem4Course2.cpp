#include <iostream>
#include <fstream>
using namespace std;
int arr[10001] = {0};
int c = 0;
void read()
{
	ifstream fin("/Users/shashankmishra/Desktop/algo1-programming_prob-2sum.txt");
	int temp = 0;
	while(fin>>temp)
	{
		if(temp < 10000)
			arr[temp]++;
	}
}
bool hashMap(int n)
{
	if(n > 10000)
		return false;
	if(arr[n])
		return true;
	else
		return false;
}
int main()
{
	read();
	for(int i = -10000; i <= 10000; i++)
	{
		for(int j = -10000; j <= 10000; j++)
		{
			if(hashMap(j) && hashMap(i - j))
			{
				c++;
				break;
			}
		}
	}
	cout<<c<<endl;
	return 0;
}
