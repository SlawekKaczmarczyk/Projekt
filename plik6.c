// Algorytm LF kolorowania grafu nieskierowanego
// Data   : 24.05.2014
// (C)2014 mgr Jerzy Wa�aszek
//----------------------------------------------

#include <iostream>

using namespace std;

// Definicja elementu listy s�siedztwa

struct slistEl
{
  slistEl * next;                 // Nast�pny element listy;
  int v;                          // Wierzcho�ek docelowy
};

int main()
{
  int n,m,i,u,v,d,*CT,*DT,*VT;
  slistEl **graf,*p,*r;
  bool *C;

  cin >> n >> m;                  // Odczytujemy liczb� wierzcho�k�w i kraw�dzi grafu

  graf = new slistEl * [n];       // Tablica list s�siedztwa
  for(i = 0; i < n; i++) graf[i] = NULL;

  CT = new int [n];               // Tablica kolor�w wierzcho�k�w
  DT = new int [n];               // Tablica stopni wyj�ciowych wierzcho�k�w
  VT = new int [n];               // Tablica numer�w wierzcho�k�w
  C  = new bool [n];              // Tablica dost�pno�ci kolor�w

  // Odczytujemy kraw�dzie grafu

  for(i = 0; i < m; i++)
  {
    cin >> u >> v;                // Wierzcho�ki kraw�dzi
    p = new slistEl;              // Tworzymy element listy
    p->v = u;
    p->next = graf[v];            // Element do��czamy do listy s�siad�w v
    graf[v] = p;

    p = new slistEl;              // To samo dla kraw�dzi w drug� stron�
    p->v = v;
    p->next = graf[u];            // Element do��czamy do listy s�siad�w u
    graf[u] = p;
  }

  // Rozpoczynamy algorytm kolorowania grafu

  for(v = 0; v < n; v++)          // Przegl�damy kolejne wierzcho�ki grafu
  {
    VT[v] = v;                    // Zapami�tujemy numer wierzcho�ka
    DT[v] = 0;                    // Zerujemy jego stopie� wyj�ciowy

    for(p = graf[v]; p; p = p->next) // Przegl�damy kolejnych s�siad�w
      DT[v]++;                    // Obliczamy stopie� wyj�ciowy wierzcho�ka v

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

  // Teraz stosujemy algorytm zach�anny, lecz wierzcho�ki wybieramy wg VT

  for(i = 0; i < n; i++) CT[i] = -1;

  CT[VT[0]] = 0;                  // Wierzcho�ek startowy

  for(v = 1; v < n; v++)          // Przegl�damy reszt� grafu
  {
    for(i = 0; i < n; i++) C[i] = false;

    for(p = graf[VT[v]]; p; p = p->next) // Przegl�damy s�siad�w bie��cego wierzcho�ka
      if(CT[p->v] > -1) C[CT[p->v]] = true; // Oznaczamy kolor jako zaj�ty

    for(i = 0; C[i]; i++);        // Szukamy wolnego koloru

    CT[VT[v]] = i;                // Przypisujemy go bie��cemu wierzcho�kowi
  }

  // Wy�wietlamy wyniki

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
