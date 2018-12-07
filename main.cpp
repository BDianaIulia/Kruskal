///https://infoarena.ro/problema/apm

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <stdio.h>

using namespace std;

///Kruskal este un algoritm care rezolva problema arborelui minim de acoperire( dandu-se un graf conex, cu costuri pe muchii,
///alegeti muchiile astfel incat sa se alcatuiasca un arbore cu cost minim )
///Ideea acestui algoritm este a porni de la n grafuri conexe( fiecare continand doar cate un nod, fara nici o muchie ), urmand
///sa se aduage muchii( cu cost minim ) pana se formeaza arborele de cost minim.
///Acest algoritm trebuie sa testeze la fiecare adaugare de muchie daca se formeaza ciclu( in cazul afirmativ, muchia este ignorata,
///continandu-se cu urmatoarele muchii). Acest lucru se poate face cu DFS sau BFS, dar deoarece au o complexitate mai mare de timp,
///urmatoarea rezolvare propune sa ne folosim de --> disjoint-set data structure ( gasiti mai multe in documentatie ).


///Lista de adiacenta va fi, de data aceasta, un vector de tupluri de forma - cost -- nodPlecare -- nodSosire
vector<tuple<int,int,int>> adj_list;

///Vectorul de căi este stocat intr-un vector de perechi de forma -- nodPornire -- nodSosire
vector<pair<int,int>> way;
int n, m , x, y ,c , cost_total;

///Urmatorii 2 vectori sunt necesari pentru a aplica setul de uniuni disjuncte
vector<int> link;
vector<int> sizee;


///Aceasta functie returneaza reprezentativul pentru un x.
int findd(int x)
{
    while( x != link[x] )
        x = link[x];

    return x;
}

///Aceasta functie verifica daca cele 2 puncte fac parte din acelasi set disjunct.
bool same( int a , int b )
{
    return findd(a) == findd(b);
}

///Aceasta functie uneste 2 seturi disjuncte.
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
    ///Citim inputul din fisier. Ne folosim de citirea din C pentru a fi mai eficient.
    freopen( "apm.in", "r", stdin );
	freopen( "apm.out", "w", stdout );

    ///Citim n - numar de noduri ,  m - numar de muchii
    scanf( "%d %d\n", &n, &m );

    ///Citim m muchii sub forma - nodPlecare -- nodSosire -- cost muchie.
    ///In lista de adiacenta  memoram ca tuplu, deoarece pe noi ne intereseaza muchiile, nu si adiacenta fiecarui nod.
    for( int i = 0 ; i < m ; i++ )
    {
        scanf( "%d %d %d\n", &x, &y, &c );
        adj_list.push_back( make_tuple( c, x, y ) );
    }

    ///Deoarece vectorul incepe mereu de la indicele 0, iar pe noi ne intereseaza doar de la indicele 1, adaugam valori nule la
    ///primul indice.
    link.push_back(0);
    sizee.push_back(0);


    ///Initial, fiecare nod este legat doar de el insasi, fiecare set are size-ul 1.
    for( int i = 1 ; i <= n ; i++ )
    {
        link.push_back( i );
        sizee.push_back(1);
    }

    ///Sortam muchiile. Deoarece primul element din tuplu este costul, acesta va fi prioritar la sortare.
    sort( adj_list.begin() , adj_list.end() );

    ///Cost_total reprezinta costul total de pe muchiile arborelui, fiind initializat cu 0.
    cost_total = 0;


    ///Iteram prin vectorul de tupluri de muchii.
    ///Cu ajutorul functiei tie(), atribuim celor 3 intregi cele 3 valori dintr-un tuplu al vectorului.
    for( auto it : adj_list )
    {
        int nod_plecare , nod_sosire , cost;
        tie( cost , nod_plecare , nod_sosire ) = it;

        ///Daca cele 2 noduri fac parte din seturi dijuncte diferite, putem sa le unim, deoarece nu cream ciclu.
        ///Memoram muchia adaugata in vectorul way sub forma - nodPlecare -- nodSosire.
          ///Adaugam costul muchiei la costul total.
        if( !same( nod_plecare , nod_sosire ) )
        {
            unite( nod_plecare , nod_sosire );

            way.push_back( make_pair( nod_plecare , nod_sosire ) );
            cost_total += cost;

        }
    }

    ///Afisam urmatoarele:
    ///-suma muchiilor ce alcatuiesc arborele minim de acoperire
    ///-cate muchii alcatuiesc arborele minim de acoperire( din definitia arborelui, aceasta este egala cu n - 1 )
    ///-care sunt muchiile( afisate in arice ordine, in orice sens )
    printf( "%d\n", cost_total );
    printf( "%d\n" , way.size() );
    for( auto it : way )
    {
        printf( "%d %d\n" , it.first , it.second );
    }
    return 0;
}
