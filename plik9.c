// Kojarzenie ma³¿eñstw
// Data: 23.12.2013
// (C)2013 mgr Jerzy Wa³aszek
//----------------------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i kolejki

struct slistEl
{
  slistEl * next;
  int v;
};

const int MAXINT = -2147483647;

// Definicja typu obiektowego queue
//---------------------------------
class queue
{
  private:
    slistEl * head;
    slistEl * tail;

  public:
    queue();      // konstruktor
    ~queue();     // destruktor
    bool empty(void);
    int  front(void);
    void push(int x);
    void pop(void);
};

//---------------------
// Metody obiektu queue
//---------------------

// Konstruktor - tworzy pust¹ listê
//---------------------------------
queue::queue()
{
  head = tail = NULL;
}

// Destruktor - usuwa listê z pamiêci
//-----------------------------------
queue::~queue()
{
  while(head) pop();
}

// Sprawdza, czy kolejka jest pusta
//---------------------------------
bool queue::empty(void)
{
  return !head;
}

// Zwraca pocz¹tek kolejki.
// Wartoœæ specjalna to -MAXINT
//-----------------------------
int queue::front(void)
{
  if(head) return head->v;
  else     return -MAXINT;
}

// Zapisuje do kolejki
//--------------------
void queue::push(int x)
{
  slistEl * p = new slistEl;
  p->next = NULL;
  p->v    = x;
  if(tail) tail->next = p;
  else     head = p;
  tail = p;
}

// Usuwa z kolejki
//----------------
void queue::pop(void)
{
  if(head)
  {
    slistEl * p = head;
    head = head->next;
    if(!head) tail = NULL;
    delete p;
  }
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int n,m,i,v,x,y, * matching, * augment;
  slistEl * p,* r, ** graf;
  bool * visited, * color;
  queue Q;

  cin >> n >> m;                // Czytamy liczbê wierzcho³ków i krawêdzi

  // Tworzymy zmienne dynamiczne

  color    = new bool[n];       // Kawalerowie (true), panny (false)
  matching = new int[n];        // Skojarzenia
  augment  = new int[n];        // Œcie¿ka rozszerzaj¹ca
  visited  = new bool[n];       // Odwiedziny
  graf     = new slistEl * [n]; // Tworzymy tablicê list s¹siedztwa

  // Tablicê wype³niamy pustymi listami

  for(i = 0; i < n; i++) graf[i] = NULL;

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> x >> y;              // KrawêdŸ panna --- kawaler
    p = new slistEl;            // Tworzymy nowy element
    p->v = y;                   // Numerujemy go jako kawaler
    p->next = graf[x];          // Dodajemy go na pocz¹tek listy panny
    graf[x] = p;
    p = new slistEl;            // Tworzymy nowy element
    p->v = x;                   // Numerujemy go jako pannê
    p->next = graf[y];          // Dodajemy go na pocz¹tek listy kawalera
    graf[y] = p;
    color[x] = false;           // Panna
    color[y] = true;            // Kawaler
  }

  cout << endl;

  // Algorytm znajdowania maksymalnego skojarzenia

  for(i = 0; i < n; i++)        // Elementy tablicy matching ustawiamy na -1
    matching[i] = -1;           // Co oznacza brak skojarzenia

  for(v = 0; v < n; v++)        // Przechodzimy przez kolejne wierzcho³ki
    if((matching[v] == -1) && !color[v])
    {
      for(i = 0; i < n; i++)
        visited[i] = false;     // Zerujemy tablicê odwiedzin

      while(!Q.empty()) Q.pop();// Zerujemy kolejkê

      visited[v] = true;        // Oznaczamy v jako wierzcho³ek odwiedzony
      augment[v] = -1;          // Poprzednikiem v jest korzeñ drzewa rozpinaj¹cego
      Q.push(v);                // Umieszczamy v w kolejce

      while(!Q.empty())         // Uruchamiamy BFS
      {
        x = Q.front();          // Pobieramy x z kolejki
        Q.pop();                // Pobrany wierzcho³ek usuwamy z kolejki

        if(color[x])
        {                       // Kawalerowie
          if(matching[x] == -1)
          {                     // Kawaler wolny
            while(augment[x] > -1)
            {
              if(color[x])
              {                 // Zamieniamy krawêdzie skojarzone z nieskojarzonymi
                matching[x] = augment[x];
                matching[augment[x]] = x;
              }
              x = augment[x];   // Cofamy siê po œcie¿ce rozszerzaj¹cej
            }
            break;              // Wracamy do pêtli g³ównej
          }
          else
          {                     // Kawaler skojarzony
            augment[matching[x]] = x;
            visited[matching[x]] = true;
            Q.push(matching[x]);// W kolejce umieszczamy skojarzon¹ pannê
          }
        }
        else
        {                       // Panny
          p = graf[x];          // Przegl¹damy kawalerów
          while(p)
          {
            y = p->v;           // Numer kawalera
            if(!visited[y])     // Tylko kawalerowie nieskojarzeni
            {                   // s¹ umieszczani w kolejce
              visited[y] = true;
              augment[y] = x;   // Tworzymy œcie¿kê rozszerzaj¹c¹
              Q.push(y);
            }
            p = p->next;
          }
        }
      }
    }

  // Wyœwietlamy skojarzenia panna --- kawaler

  for(i = 0; i < n; i++)
    if(!color[i]) cout << i << " --- " << matching[i] << endl;

  // Usuwamy dynamiczne struktury danych

  delete [] color;
  delete [] matching;
  delete [] augment;
  delete [] visited;

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

  delete [] graf;

  return 0;
}
