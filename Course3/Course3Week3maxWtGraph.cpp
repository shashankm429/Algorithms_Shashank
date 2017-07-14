#include<bits/stdc++.h>
using namespace std;
int main()
{

    int n;
    cin >> n;
    int arr[n + 1];
    arr[0] = 0;
    for(int i = 1 ; i < n + 1; ++i)
    {
        cin >> arr[i];
    }
    int arr1[n + 1];
    arr1[0] = 0;
    arr1[1] = arr[1];
    for(int i = 2 ; i < n + 1; ++i)
    {
        arr1[i] = max( arr1[i-1] , arr1[i-2] + arr[i] );
    }
    cout <<"\n" << arr1[n] << endl;
    int i = n;
    cout <<"The vertices of maximum weight independent set of the path graph are ";
    while( i > 1 )
	{
        if( arr1[i-2] + arr[i] > arr1[i-1] ){
            cout << i <<" , ";
            i -=2;

            if( i == 1){
                cout << 1 << " , ";
                break;
            }
        }

        else{
            i--;
        }
    }

    return 0;
}
