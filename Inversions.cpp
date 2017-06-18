#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;
const int MAX = 100000;
int arr[MAX];
long ans;
void read();
void merge(int *,int,int);
void merge_sort(int *,int,int);
int main()
{
read();
merge_sort(arr, 0, MAX-1);
cout<<ans<<endl;
return 0;
}
void read()
{
freopen("/Users/shashankmishra/Desktop/IntegerArray.txt","r",stdin);
for (int i=0;i<MAX;i++)
cin >> arr[i];
}
void merge(int* input, int low, int high)
{
int mid = ((low + high)/2);
int i = 0;
int left = low;
int right = mid + 1;
int t=high - low + 1;
int temp[t];
while(left <= mid && right <= high)
{
if(input[left] < input[right])
temp[i++] = input[left++];
else
{
temp[i++] = input[right++];
ans += (mid - left + 1);
}
}
while(left <= mid)
temp[i++] = input[left++];
while(right <= high)
temp[i++] = input[right++];
for(i = low; i < high + 1; ++i)
input[i] = temp[i - low];
}
void merge_sort(int* input, int low, int high)
{
if ( low < high )
{
int mid = ((low + high) / 2);
merge_sort(input, low, mid);
merge_sort(input, mid + 1, high);
merge(input, low, high);
}
}



