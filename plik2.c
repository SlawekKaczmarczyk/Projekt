// Stopieñ grafu skierowanego
// Data   : 26.04.2014
// (C)2014 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>

using namespace std;

// Definicja elementu listy s¹siedztwa

struct slistEl
{
  slistEl * next;                 // Nastêpny element listy
  int v;                          // Wierzcho³ek docelowy
};

int main()
{
  int n,m;                        // Liczba wierzcho³ków, liczba krawêdzi
  slistEl **G;                    // Graf
  int *DV;                        // Tablica stopni wierzcho³ków
  int d,i,v,u;
  slistEl *p,*r;

  cin >> n >> m;                  // Czytamy rozmiary grafu

  G = new slistEl * [n];          // Tworzymy zerowy graf G
  DV = new int [n];               // Tworzymy tablicê DV
  for(i = 0; i < n; i++)
  {
    G[i] = NULL;                  // Pusta lista
    DV[i] = 0;                    // Stopieñ zerowy
  }

  // Odczytujemy definicje krawêdzi grafu G

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;                // Czytamy wierzcho³ki
    p = new slistEl;              // Tworzymy rekord listy
    p->v = u;                     // Wype³niamy go danymi
    p->next = G[v];               // Rekord do³¹czamy do listy s¹siedztwa wierzcho³ka v
    G[v] = p;
  }

  // Wyznaczamy stopieñ grafu

  for(v = 0; v < n; v++)          // Przechodzimy przez kolejne wierzcho³ki grafu
    for(p = G[v]; p; p = p->next) // Przegl¹damy listê s¹siadów wierzcho³ka v
    {
      DV[v]++;                    // Zwiêkszamy stopieñ wyjœciowy v
      DV[p->v]++;                 // Zwiêkszamy stopieñ wejœciowy s¹siada v
    }

  // Szukamy najwiêkszego stopnia

  d = DV[0];
  for(v = 1; v < n; v++)
    if(DV[v] > d) d = DV[v];

  // Wyœwietlamy wynik

  cout << endl << d << endl << endl;

  // Usuwamy dynamiczne struktury

  for(i = 0; i < n; i++)
  {
    p = G[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [] G;
  delete [] DV;

  return 0;
}
