// Wyszukiwanie punktów artykulacji w grafie nieskierowanym
// Data: 30.12.2013
// (C)2013 mgr Jerzy Wa³aszek
//---------------------------------------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i listy punktów artykulacji

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int n,m,dv;                   // Liczba wierzcho³ków, krawêdzi, numeracja
slistEl ** graf;              // Tablica list s¹siedztwa
int *D;                       // Numery DFS
slistEl * L;                  // Lista mostów

// Funkcja rekurencyjna wyszukuj¹ca punkty artykulacji
// v  - numer bie¿¹cego wierzcho³ka
// vf - ojciec bie¿¹cego wierzcho³ka na drzewie rozpinaj¹cym
// Reszta parametrów to zmienne globalne
//----------------------------------------------------------
int DFSap(int v, int vf)
{
  int Low,temp,u;
  bool test;
  slistEl * p;

  D[v] = Low = dv++;

  test = false;

  for(p = graf[v]; p; p = p->next) // Przegl¹damy listê s¹siadów
  {
    u = p->v;                 // u - numer wierzcho³ka s¹siada
    if(u != vf)               // u nie mo¿e byæ ojcem v
    {
      if(!D[u])               // Jeœli s¹siad u nie by³ odwiedzany, to
      {
        temp = DFSap(u,v);    // rekurencyjnie odwiedzamy go
        if(temp < Low) Low = temp;
        if(temp >= D[v]) test = true; // Test na punkt artykulacji
      }
      else if(D[u] < Low) Low = D[u];
    }
  }

  // Wszyscy s¹siedzi zostali odwiedzeni, sprawdzamy wynik testu

  if(test)
  {
    p = new slistEl;          // Mamy nowy punkt artykulacji
    p->v = v;
    p->next = L;
    L = p;
  }

  return Low;                // Wynik
}

// **********************
// *** Program g³ówny ***
// **********************

int main()
{
  int i,u,v,nc;              // Numery wierzcho³ków, licznik synów korzenia
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczbê wierzcho³ków i krawêdzi

  graf = new slistEl * [n];  // Tworzymy zmienne dynamiczne
  D = new int[n];
  L = NULL;

  for(i = 0; i < n; i++)
  {
    graf[i] = NULL;
    D[i]    = 0;
  }

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho³ki tworz¹ce krawêdŸ
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = graf[v];       // Dodajemy go na pocz¹tek listy graf[v]
    graf[v] = p;
    p = new slistEl;         // To samo dla krawêdzi w drug¹ stronê
    p->v = v;
    p->next = graf[u];
    graf[u] = p;
  }

  // Szukamy punktów artykulacji

  for(v = 0; v < n; v++)
    if(!D[v])               // Szukamy nieodwiedzonego wierzcho³ka
    {
      dv   = 2;             // Numer DFS dla pierwszego syna
      nc   = 0;             // Zerujemy licznik synów
      D[v] = 1;             // Korzeñ zawsze ma numer DFS 1
      for(p = graf[v]; p; p = p->next) // Przegl¹damy s¹siadów v
      {
        u = p->v;           // Numer wierzcho³ka s¹siedniego
        if(!D[u])           // Szukamy nieodwiedzonego s¹siada
        {
          nc++;             // Zwiêkszamy licznik synów
          DFSap(u,v);       // Szukamy punktów artykulacji w grafie
        }
      }

      if(nc > 1)            // Czy korzeñ jest punktem artykulacji?
      {
        p = new slistEl;    // Tak, dodajemy go do listy
        p->v = v;
        p->next = L;
        L = p;
      }
    }

  cout << endl;

  // Wypisujemy znalezione punkty artykulacji

  while(L)
  {
    cout << L->v << " ";
    p = L;
    L = L->next;
    delete p;
  }

  cout << endl;

  // Usuwamy struktury dynamiczne

  delete [] D;

  for(i = 0; i < n; i++)
  {
    p = graf[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete graf;

  return 0;
}
