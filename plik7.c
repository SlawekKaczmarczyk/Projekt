// Wyznaczanie silnie spójnych sk³adowych
// Algorytm Korsaraju
// Data: 26.01.2014
// (C)2014 mgr Jerzy Wa³aszek
//---------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i stosu

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

// Przechodzi graf algorytmem DFS, umieszczaj¹c na stosie
// napotkane po drodze wierzcho³ki.
// v       - numer wierzcho³ka startowego
// visited - tablica odwiedzin
// S       - stos
// graf    - tablica list s¹siedztwa
//--------------------------------------------------------
void DFSstack(int v, bool * visited, stack & S, slistEl ** graf)
{
  slistEl * p;

  visited[v] = true;             // Oznaczamy v jako odwiedzony

  // Przegl¹damy s¹siadów v
  for(p = graf[v]; p; p = p->next)
    if(!visited[p->v]) DFSstack(p->v,visited,S,graf);

  S.push(v);
}

// Wyœwietla wierzcho³ki kolejno odwiedzane przez DFS
// v       - wierzcho³ek startowy
// visited - tablica odwiedzin
// graf    - tablica list s¹siedztwa
//---------------------------------------------------
void DFSprint(int v, bool * visited, slistEl ** graf)
{
  slistEl * p;

  visited[v] = true;
  cout << setw(3) << v;
  for(p = graf[v]; p; p = p->next)
    if(!visited[p->v]) DFSprint(p->v,visited,graf);
}

// **********************
// *** Program g³ówny ***
// **********************

int main()
{
  int n,m;                       // Liczba wierzcho³ków i krawêdzi
  slistEl **A, **AT;             // Tablice list s¹siedztwa
  bool * visited;
  stack S;
  int i,v,u,cn;
  slistEl *p,*r;

  cin >> n >> m;                 // Odczytujemy liczbê wierzcho³ków i krawêdzi

  A  = new slistEl * [n];        // Tworzymy tablice dynamiczne
  AT = new slistEl * [n];

  // Inicjujemy tablice

  for(i = 0; i < n; i++) A[i] = AT[i] = NULL;

  // Odczytujemy kolejne definicje krawêdzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;               // Wierzcho³ki tworz¹ce krawêdŸ
    p = new slistEl;             // Tworzymy nowy element
    p->v = u;                    // Numerujemy go jako u
    p->next = A[v];              // i dodajemy na pocz¹tek listy graf[v]
    A[v] = p;
  }

  cout << endl;

  // Wyznaczamy silnie spójne sk³adowe

  visited = new bool [n];        // Tworzymy tablicê odwiedzin
  for(i = 0; i < n; i++)         // i wype³niamy j¹ wartoœciami false
    visited[i] = false;

  for(v = 0; v < n; v++)         // Przegl¹damy kolejne wierzcho³ki grafu
    if(!visited[v]) DFSstack(v,visited,S,A);

  // Transponujemy graf

  for(v = 0; v < n; v++)         // Przegl¹damy kolejne wierzcho³ki
      // Przegl¹damy s¹siadów v
    for(p = A[v]; p; p = p->next)
    {
      r = new slistEl;           // Tworzymy nowy element listy
      r->v = v;                  // Zapamiêtujemy w nim wierzcho³ek v
      r->next = AT[p->v];        // i dodajemy do listy s¹siada
      AT[p->v] = r;
    }

  for(v = 0; v < n; v++)         // Zerujemy tablicê odwiedzin
    visited[v] = false;

  cn = 0;                        // Inicjujemy licznik sk³adowych

  while(!S.empty())              // Przetwarzamy wierzcho³ki ze stosu
  {
    v = S.top(); S.pop();        // Pobieramy wierzcho³ek ze stosu
    if(!visited[v])
    {
      cout << "SCC" << setw(3) << ++cn << " :";
      DFSprint(v,visited,AT);
      cout << endl;
    }
  }

  // Usuwamy tablice dynamiczne

  for(i = 0; i < n; i++)
  {
    p = A[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
    p = AT[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [] A;
  delete [] AT;
  delete [] visited;

  return 0;
}
