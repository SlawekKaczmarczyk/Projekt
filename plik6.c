// Algorytm LF kolorowania grafu nieskierowanego
// Data   : 24.05.2014
// (C)2014 mgr Jerzy Wa³aszek
//----------------------------------------------

#include <iostream>

using namespace std;

// Definicja elementu listy s¹siedztwa

struct slistEl
{
  slistEl * next;                 // Nastêpny element listy;
  int v;                          // Wierzcho³ek docelowy
};

int main()
{
  int n,m,i,u,v,d,*CT,*DT,*VT;
  slistEl **graf,*p,*r;
  bool *C;

  cin >> n >> m;                  // Odczytujemy liczbê wierzcho³ków i krawêdzi grafu

  graf = new slistEl * [n];       // Tablica list s¹siedztwa
  for(i = 0; i < n; i++) graf[i] = NULL;

  CT = new int [n];               // Tablica kolorów wierzcho³ków
  DT = new int [n];               // Tablica stopni wyjœciowych wierzcho³ków
  VT = new int [n];               // Tablica numerów wierzcho³ków
  C  = new bool [n];              // Tablica dostêpnoœci kolorów

  // Odczytujemy krawêdzie grafu

  for(i = 0; i < m; i++)
  {
    cin >> u >> v;                // Wierzcho³ki krawêdzi
    p = new slistEl;              // Tworzymy element listy
    p->v = u;
    p->next = graf[v];            // Element do³¹czamy do listy s¹siadów v
    graf[v] = p;

    p = new slistEl;              // To samo dla krawêdzi w drug¹ stronê
    p->v = v;
    p->next = graf[u];            // Element do³¹czamy do listy s¹siadów u
    graf[u] = p;
  }

  // Rozpoczynamy algorytm kolorowania grafu

  for(v = 0; v < n; v++)          // Przegl¹damy kolejne wierzcho³ki grafu
  {
    VT[v] = v;                    // Zapamiêtujemy numer wierzcho³ka
    DT[v] = 0;                    // Zerujemy jego stopieñ wyjœciowy

    for(p = graf[v]; p; p = p->next) // Przegl¹damy kolejnych s¹siadów
      DT[v]++;                    // Obliczamy stopieñ wyjœciowy wierzcho³ka v

    // Sortujemy DT i VT

    d = DT[v];

    for(i = v; (i > 0) && (DT[i-1] < d); i--)
    {
      DT[i] = DT[i - 1];
      VT[i] = VT[i - 1];
    }

    DT[i] = d;
    VT[i] = v;
  }

  // Teraz stosujemy algorytm zach³anny, lecz wierzcho³ki wybieramy wg VT

  for(i = 0; i < n; i++) CT[i] = -1;

  CT[VT[0]] = 0;                  // Wierzcho³ek startowy

  for(v = 1; v < n; v++)          // Przegl¹damy resztê grafu
  {
    for(i = 0; i < n; i++) C[i] = false;

    for(p = graf[VT[v]]; p; p = p->next) // Przegl¹damy s¹siadów bie¿¹cego wierzcho³ka
      if(CT[p->v] > -1) C[CT[p->v]] = true; // Oznaczamy kolor jako zajêty

    for(i = 0; C[i]; i++);        // Szukamy wolnego koloru

    CT[VT[v]] = i;                // Przypisujemy go bie¿¹cemu wierzcho³kowi
  }

  // Wyœwietlamy wyniki

  cout << endl;
  for(v = 0; v < n; v++)
    cout << "vertex " << v << " has color " << CT[v] << endl;
  cout << endl;

  // Usuwamy tablice dynamiczne

  for(v = 0; v < n; v++)
  {
    p = graf[v];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete [] graf;
  delete [] CT;
  delete [] DT;
  delete [] VT;
  delete [] C;

  return 0;
}
