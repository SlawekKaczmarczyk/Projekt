// Wyznaczanie silnie sp�jnych sk�adowych
// Algorytm Korsaraju
// Data: 26.01.2014
// (C)2014 mgr Jerzy Wa�aszek
//---------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj�ca stos

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

// Destruktor - zwalnia tablic� dynamiczn�
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

// Przechodzi graf algorytmem DFS, umieszczaj�c na stosie
// napotkane po drodze wierzcho�ki.
// v       - numer wierzcho�ka startowego
// visited - tablica odwiedzin
// S       - stos
// graf    - tablica list s�siedztwa
//--------------------------------------------------------
void DFSstack(int v, bool * visited, stack & S, slistEl ** graf)
{
  slistEl * p;

  visited[v] = true;             // Oznaczamy v jako odwiedzony

  // Przegl�damy s�siad�w v
  for(p = graf[v]; p; p = p->next)
    if(!visited[p->v]) DFSstack(p->v,visited,S,graf);

  S.push(v);
}

// Wy�wietla wierzcho�ki kolejno odwiedzane przez DFS
// v       - wierzcho�ek startowy
// visited - tablica odwiedzin
// graf    - tablica list s�siedztwa
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
// *** Program g��wny ***
// **********************

int main()
{
  int n,m;                       // Liczba wierzcho�k�w i kraw�dzi
  slistEl **A, **AT;             // Tablice list s�siedztwa
  bool * visited;
  stack S;
  int i,v,u,cn;
  slistEl *p,*r;

  cin >> n >> m;                 // Odczytujemy liczb� wierzcho�k�w i kraw�dzi

  A  = new slistEl * [n];        // Tworzymy tablice dynamiczne
  AT = new slistEl * [n];

  // Inicjujemy tablice

  for(i = 0; i < n; i++) A[i] = AT[i] = NULL;

  // Odczytujemy kolejne definicje kraw�dzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;               // Wierzcho�ki tworz�ce kraw�d�
    p = new slistEl;             // Tworzymy nowy element
    p->v = u;                    // Numerujemy go jako u
    p->next = A[v];              // i dodajemy na pocz�tek listy graf[v]
    A[v] = p;
  }

  cout << endl;

  // Wyznaczamy silnie sp�jne sk�adowe

  visited = new bool [n];        // Tworzymy tablic� odwiedzin
  for(i = 0; i < n; i++)         // i wype�niamy j� warto�ciami false
    visited[i] = false;

  for(v = 0; v < n; v++)         // Przegl�damy kolejne wierzcho�ki grafu
    if(!visited[v]) DFSstack(v,visited,S,A);

  // Transponujemy graf

  for(v = 0; v < n; v++)         // Przegl�damy kolejne wierzcho�ki
      // Przegl�damy s�siad�w v
    for(p = A[v]; p; p = p->next)
    {
      r = new slistEl;           // Tworzymy nowy element listy
      r->v = v;                  // Zapami�tujemy w nim wierzcho�ek v
      r->next = AT[p->v];        // i dodajemy do listy s�siada
      AT[p->v] = r;
    }

  for(v = 0; v < n; v++)         // Zerujemy tablic� odwiedzin
    visited[v] = false;

  cn = 0;                        // Inicjujemy licznik sk�adowych

  while(!S.empty())              // Przetwarzamy wierzcho�ki ze stosu
  {
    v = S.top(); S.pop();        // Pobieramy wierzcho�ek ze stosu
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
