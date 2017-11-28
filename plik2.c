// Stopie� grafu skierowanego
// Data   : 26.04.2014
// (C)2014 mgr Jerzy Wa�aszek
//---------------------------

#include <iostream>

using namespace std;

// Definicja elementu listy s�siedztwa

struct slistEl
{
  slistEl * next;                 // Nast�pny element listy
  int v;                          // Wierzcho�ek docelowy
};

int main()
{
  int n,m;                        // Liczba wierzcho�k�w, liczba kraw�dzi
  slistEl **G;                    // Graf
  int *DV;                        // Tablica stopni wierzcho�k�w
  int d,i,v,u;
  slistEl *p,*r;

  cin >> n >> m;                  // Czytamy rozmiary grafu

  G = new slistEl * [n];          // Tworzymy zerowy graf G
  DV = new int [n];               // Tworzymy tablic� DV
  for(i = 0; i < n; i++)
  {
    G[i] = NULL;                  // Pusta lista
    DV[i] = 0;                    // Stopie� zerowy
  }

  // Odczytujemy definicje kraw�dzi grafu G

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;                // Czytamy wierzcho�ki
    p = new slistEl;              // Tworzymy rekord listy
    p->v = u;                     // Wype�niamy go danymi
    p->next = G[v];               // Rekord do��czamy do listy s�siedztwa wierzcho�ka v
    G[v] = p;
  }

  // Wyznaczamy stopie� grafu

  for(v = 0; v < n; v++)          // Przechodzimy przez kolejne wierzcho�ki grafu
    for(p = G[v]; p; p = p->next) // Przegl�damy list� s�siad�w wierzcho�ka v
    {
      DV[v]++;                    // Zwi�kszamy stopie� wyj�ciowy v
      DV[p->v]++;                 // Zwi�kszamy stopie� wej�ciowy s�siada v
    }

  // Szukamy najwi�kszego stopnia

  d = DV[0];
  for(v = 1; v < n; v++)
    if(DV[v] > d) d = DV[v];

  // Wy�wietlamy wynik

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
