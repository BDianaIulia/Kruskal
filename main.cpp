///https://infoarena.ro/problema/apm

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <stdio.h>

using namespace std;

//ifstream fin( "apm.in" );
//ofstream fout( "apm.out" );

vector<tuple<int,int,int>> adj_list;
vector<pair<int,int>> way;
int n, m , x, y ,c , cost_total;
vector<int> link;
vector<int> sizee;
vector<int> freq;

int findd(int x)
{
    while( x != link[x] )
        x = link[x];

    return x;
}

bool same( int a , int b )
{
    return findd(a) != findd(b);
}

void unite( int a, int b )
{
    a = findd( a );
    b = findd( b );
    if( sizee[a] < sizee[b] )
        swap(a , b);

    sizee[a] += sizee[b];
    link[b] = a;
}

int main()
{
    freopen( "apm.in", "r", stdin );
	freopen( "apm.out", "w", stdout );

    scanf( "%d %d\n", &n, &m );
    for( int i = 0 ; i < m ; i++ )
    {
        scanf( "%d %d %d\n", &x, &y, &c );
        adj_list.push_back( make_tuple( c, x, y ) );
    }

    link.push_back(0);
    sizee.push_back(0);
    freq.push_back(0);

    for( int i = 1 ; i <= n ; i++ )
    {
        link.push_back( i );
        sizee.push_back(1);
        freq.push_back(0);
    }

    sort( adj_list.begin() , adj_list.end() );
    cost_total = 0;

    for( auto it : adj_list )
    {
        int nod_plecare , nod_sosire , cost;
        tie( cost , nod_plecare , nod_sosire ) = it;

        if( same( nod_plecare , nod_sosire ) )
        {
            unite( nod_plecare , nod_sosire );
            way.push_back( make_pair( nod_plecare , nod_sosire ) );
            cost_total += cost;

            freq[nod_plecare]++;
            freq[nod_sosire]++;
        }
    }

    printf( "%d\n", cost_total );
    printf( "%d\n" , way.size() );
    for( auto it : way )
    {
        printf( "%d %d\n" , it.first , it.second );
    }
    return 0;
}
