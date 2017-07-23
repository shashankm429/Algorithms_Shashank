#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
int main()
{
    long int total,n;
    cin>>total;
    vector<pair<long double,long double> > values;
    vector<bool> visited(total,false);
    for(int i=0;i<total;i++){
        double a,b;
        cin>>n>>a>>b;
        values.push_back({a,b});
        visited[i]=false;
    }
    long int s =0;
    visited[s] = true;
    long double sum = 0 ;
    for(int i=0;i<total-1;i++)
    {
        long double mini=1000000000.0;
         visited[s] = true;
         long int s1=s;
        for(int j=0;j<total;j++)
        {

            long double yo = pow(values[s1].first - values[j].first,2);
            long double yo2 = pow(values[s1].second - values[j].second,2);

            long double temp = yo+yo2;
            if(temp<mini && visited[j]==false )
            {
                s = j;
                mini = temp;
            }
        }
        sum += sqrt(mini);
    }
    sum += sqrt(pow(values[0].first - values[s].first,2) + pow(values[0].second - values[s].second,2));
    cout<<(long long int)sum;
}
