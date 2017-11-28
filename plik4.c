// Wyszukiwanie mostów w grafie nieskierowanym
// Data: 27.12.2013
// (C)2013 mgr Jerzy Wa³aszek
//--------------------------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa, stosu i listy mostów

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj¹ca stos

  public:
    stack();       // konstruktor
    ~stack();      // destruktor
    bool empty(void);
    int  top(void);
    void push(int v);
    void pop(void);
};

//---------------------
// Metody obiektu stack
//---------------------

// Konstruktor
//------------
stack::stack()
{
  S = NULL;
}

// Destruktor - zwalnia tablicê dynamiczn¹
//----------------------------------------
stack::~stack()
{
  while(S) pop();
}

// Sprawdza, czy stos jest pusty
//------------------------------
bool stack::empty(void)
{
  return !S;
}

// Zwraca szczyt stosu
//--------------------
int stack::top(void)
{
  return S->v;
}

// Zapisuje na stos
//-----------------
void stack::push(int v)
{
  slistEl * e = new slistEl;
  e->v    = v;
  e->next = S;
  S = e;
}

// Usuwa ze stosu
//---------------
void stack::pop(void)
{
  if(S)
  {
    slistEl * e = S;
    S = S->next;
    delete e;
  }
}

// Funkcja oblicza liczbê spójnych sk³adowych w grafie
// n    - liczba wierzcho³ków w grafie
// graf - tablica list s¹siedztwa
// VU   - tablica dostêpnoœci krawêdzi grafu
//----------------------------------------------------
int ccn(int n, slistEl ** graf, bool * VU)
{
  int * C,cc,i,v,u;
  stack S;
  slistEl * p;

  C = new int[n];            // Tworzymy tablicê spójnych sk³adowych

  for(i = 0; i < n; i++) C[i] = 0; // Zerujemy tablicê spójnych sk³adowych

  cc = 0;                    // Zerujemy licznik spójnych sk³adowych

  for(i = 0; i < n; i++)
    if(!C[i])                // Szukamy nieodwiedzonego jeszcze wierzcho³ka
    {
      cc++;                  // Zwiêkszamy licznik sk³adowych
      S.push(i);             // Na stosie umieszczamy numer bie¿¹cego wêz³a
      C[i] = cc;             // Wierzcho³ek numerujemy i oznaczamy jako odwiedzony
      while(!S.empty())      // Przechodzimy graf algorytmem DFS
      {
        v = S.top();         // Pobieramy wierzcho³ek
        S.pop();             // Usuwamy go ze stosu
        for(p = graf[v]; p; p = p->next) // Przegl¹damy s¹siadów wierzcho³ka v
        {
          u = p->v;
          if((VU[v] || VU[u]) && !C[u])
          {
            S.push(p->v);   // Na stos id¹ s¹siedzi nieodwiedzeni
            C[u] = cc;      // i ponumerowani
          }
        }
      }
    }

  delete [] C;               // Usuwamy tablicê C
  return cc;                 // Zwracamy wynik
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int n,m;                   // Liczba wierzcho³ków i krawêdzi
  slistEl ** A;              // Tablica list s¹siedztwa
  int nc,i,v,u;
  slistEl * L,* p,* r;
  bool * VU;

  cin >> n >> m;             // Czytamy liczbê wierzcho³ków i krawêdzi

  // Tworzymy zmienne dynamiczne

  VU = new bool[n];          // Krawêdzie aktywne
  A  = new slistEl * [n];    // Tablica list s¹siedztwa

  // Tablicê wype³niamy pustymi listami

  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
    VU[i] = true;
  }

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;
    p = new slistEl;
    p->v = u;
    p->next = A[v];
    A[v] = p;
    p = new slistEl;
    p->v = v;
    p->next = A[u];
    A[u] = p;
  }

  // Algorytm znajdowania mostów

  L = NULL;                  // Pusta lista mostów

  nc = ccn(n,A,VU);          // Zapamiêtujemy liczbê spójnych sk³adowych

  for(v = 0; v < n; v++)     // Przechodzimy przez kolejne wierzcho³ki grafu
  {
    p = A[v];                // Przegl¹damy listê s¹siedztwa wierzcho³ka v
    while(p)
    {
      u = p->v;              // u - numer wierzcho³ka s¹siedniego w grafie
      if(u > v)              // Interesuj¹ nas tylko krawêdzie w jedn¹ stronê
      {
        VU[v] = VU[u] = false; // Zaznaczamy krawêdŸ v-u jako usuniêt¹
        if(ccn(n,A,VU) > nc)
        {
          r = new slistEl;   // Znaleziony most dodajemy do listy L
          r->v = u;
          r->next = L;
          L = r;
          r = new slistEl;
          r->v = v;
          r->next = L;
          L = r;
        }
        VU[v] = VU[u] = true; // Kasujemy zaznaczenie krawêdzi jako usuniêtej
      }
      p = p->next;
    }
  }

  cout << endl;

  // Wypisujemy znalezione mosty, jednoczeœnie usuwaj¹c listê L

  v = 0;

  while(L)
  {
    cout << L->v << " ";
    v ^= 1;
    if(!v) cout << endl;
    p = L;
    L = L->next;
    delete [] p;
  }

  // Usuwamy dynamiczne struktury danych

  for(i = 0; i < n; i++)
  {
    p = A[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete [] A;
  delete [] VU;

  return 0;
}
