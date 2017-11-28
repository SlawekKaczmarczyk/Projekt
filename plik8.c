// Wyszukiwanie punkt�w artykulacji w grafie nieskierowanym
// Data: 30.12.2013
// (C)2013 mgr Jerzy Wa�aszek
//---------------------------------------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa i listy punkt�w artykulacji

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int n,m,dv;                   // Liczba wierzcho�k�w, kraw�dzi, numeracja
slistEl ** graf;              // Tablica list s�siedztwa
int *D;                       // Numery DFS
slistEl * L;                  // Lista most�w

// Funkcja rekurencyjna wyszukuj�ca punkty artykulacji
// v  - numer bie��cego wierzcho�ka
// vf - ojciec bie��cego wierzcho�ka na drzewie rozpinaj�cym
// Reszta parametr�w to zmienne globalne
//----------------------------------------------------------
int DFSap(int v, int vf)
{
  int Low,temp,u;
  bool test;
  slistEl * p;

  D[v] = Low = dv++;

  test = false;

  for(p = graf[v]; p; p = p->next) // Przegl�damy list� s�siad�w
  {
    u = p->v;                 // u - numer wierzcho�ka s�siada
    if(u != vf)               // u nie mo�e by� ojcem v
    {
      if(!D[u])               // Je�li s�siad u nie by� odwiedzany, to
      {
        temp = DFSap(u,v);    // rekurencyjnie odwiedzamy go
        if(temp < Low) Low = temp;
        if(temp >= D[v]) test = true; // Test na punkt artykulacji
      }
      else if(D[u] < Low) Low = D[u];
    }
  }

  // Wszyscy s�siedzi zostali odwiedzeni, sprawdzamy wynik testu

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
// *** Program g��wny ***
// **********************

int main()
{
  int i,u,v,nc;              // Numery wierzcho�k�w, licznik syn�w korzenia
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczb� wierzcho�k�w i kraw�dzi

  graf = new slistEl * [n];  // Tworzymy zmienne dynamiczne
  D = new int[n];
  L = NULL;

  for(i = 0; i < n; i++)
  {
    graf[i] = NULL;
    D[i]    = 0;
  }

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho�ki tworz�ce kraw�d�
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = graf[v];       // Dodajemy go na pocz�tek listy graf[v]
    graf[v] = p;
    p = new slistEl;         // To samo dla kraw�dzi w drug� stron�
    p->v = v;
    p->next = graf[u];
    graf[u] = p;
  }

  // Szukamy punkt�w artykulacji

  for(v = 0; v < n; v++)
    if(!D[v])               // Szukamy nieodwiedzonego wierzcho�ka
    {
      dv   = 2;             // Numer DFS dla pierwszego syna
      nc   = 0;             // Zerujemy licznik syn�w
      D[v] = 1;             // Korze� zawsze ma numer DFS 1
      for(p = graf[v]; p; p = p->next) // Przegl�damy s�siad�w v
      {
        u = p->v;           // Numer wierzcho�ka s�siedniego
        if(!D[u])           // Szukamy nieodwiedzonego s�siada
        {
          nc++;             // Zwi�kszamy licznik syn�w
          DFSap(u,v);       // Szukamy punkt�w artykulacji w grafie
        }
      }

      if(nc > 1)            // Czy korze� jest punktem artykulacji?
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
