// Stopieñ grafu nieskierowanego
// Data   : 26.04.2014
// (C)2014 mgr Jerzy Wa³aszek
//------------------------------

#include <iostream>

using namespace std;

// Definicja elementu listy s¹siedztwa

struct slistEl
{
  slistEl * next ;                // Nastêpny element listy
  int v;                          // Wierzcho³ek docelowy
};

int main()
{
  int n,m;                        // Liczba wierzcho³ków, liczba krawêdzi
  slistEl **G;                    // Graf
  int dg,dv,i,v,u;
  slistEl *p,*r;

  cin >> n >> m;                  // Czytamy rozmiary grafu

  G = new slistEl * [n];          // Tworzymy zerowy graf G
  for(i = 0; i < n; i++) G[i] = NULL;

  // Odczytujemy definicje krawêdzi grafu G

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;                // Czytamy wierzcho³ki
    p = new slistEl;              // Tworzymy rekord listy
    p->v = u;                     // Wype³niamy go danymi
    p->next = G[v];               // Rekord do³¹czamy do listy s¹siedztwa wierzcho³ka v
    G[v] = p;

    if(v != u)                    // To samo dla krawêdzi odwrotnej o ile nie jest to pêtla
    {
      p = new slistEl;
      p->v = v;
      p->next = G[u];
      G[u] = p;
    }
  }

  // Wyznaczamy stopieñ grafu

  dg = 0;

  for(v = 0; v < n; v++)          // Przechodzimy przez kolejne wierzcho³ki grafu
  {
    dv = 0;                       // Zerujemy stopieñ wierzcho³ka
    for(p = G[v]; p; p = p->next) // Przegl¹damy s¹siadów wierzcho³ka v
      if(p->v == v) dv += 2;      // Pêtle zliczamy za 2
      else          dv++;         // Zwyk³¹ krawêdŸ zliczamy za 1
    if(dv > dg) dg = dv;          // Jeœli stopieñ jest wiêkszy od dg, to uaktualniamy
  }

  // Wyœwietlamy wynik

  cout << endl << dg << endl << endl;

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

  return 0;
}
