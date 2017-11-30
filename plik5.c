// Minimalne drzewo rozpinaj¹ce
// Algorytm Kruskala
// Data: 6.04.2014
// (C)2014 mgr Jerzy Wa³aszek
//--------------------------------

#include <iostream>
#include <iostream>
using namespace std;

// Definicja obiektu kolejki priorytetowej
//----------------------------------------
struct Edge
{
  int v1,v2,weight;               // Wierzcho³ki krawêdzi, waga krawêdzi
};

class Queue
{
  private:
    Edge * Heap;
    int hpos;
  public:
    Queue(int n);
    ~Queue();
    Edge front();
    void push(Edge e);
    void pop();
};

// Definicja obiektu struktury zbiorów roz³¹cznych
//------------------------------------------------
struct DSNode
{
  int up,rank;
};

class DSStruct
{
  private:
    DSNode * Z;
  public:
    DSStruct(int n);
    ~DSStruct();
    void MakeSet(int v);
    int FindSet(int v);
    void UnionSets(Edge e);
};

// Definicja obiektu minimalnego drzewa rozpinaj¹cego
//---------------------------------------------------
struct TNode
{
  TNode * next;
  int v,weight;
};

class MSTree
{
  private:
    TNode ** A;                   // Tablica list s¹siedztwa
    int Alen;                     // Liczba komórek w tablicy
    int weight;                   // Waga ca³ego drzewa
  public:
    MSTree(int n);
    ~MSTree();
    void addEdge(Edge e);
    void print();
};

// Definicje metod obiektu Queue
//------------------------------

// Konstruktor - tworzy n elementow¹ tablicê heap na kopiec
//---------------------------------------------------------
Queue::Queue(int n)
{
  Heap = new Edge [n];            // Tworzymy tablicê
  hpos = 0;                       // Pozycja w kopcu
}

// Destruktor - usuwa kopiec z pamiêci
//------------------------------------
Queue::~Queue()
{
  delete [] Heap;
}

// Zwraca krawêdŸ z pocz¹tku kopca
//--------------------------------
Edge Queue::front()
{
  return Heap[0];
}

// Umieszcza w kopcu now¹ krawêdŸ i odtwarza strukturê kopca
//----------------------------------------------------------
void Queue::push(Edge e)
{
  int i,j;

  i = hpos++;                     // i ustawiamy na koniec kopca
  j = (i - 1) >> 1;               // Obliczamy pozycjê rodzica

  // Szukamy miejsca w kopcu dla e

  while(i && (Heap[j].weight > e.weight))
  {
    Heap[i] = Heap[j];
    i = j;
    j = (i - 1) >> 1;
  }

  Heap[i] = e;                    // KrawêdŸ e wstawiamy do kopca
}

// Usuwa korzeñ z kopca i odtwarza jego strukturê
//-----------------------------------------------
void Queue::pop()
{
  int i,j;
  Edge e;

  if(hpos)
  {
    e = Heap[--hpos];

    i = 0;
    j = 1;

    while(j < hpos)
    {
      if((j + 1 < hpos) && (Heap[j + 1].weight < Heap[j].weight)) j++;
      if(e.weight <= Heap[j].weight) break;
      Heap[i] = Heap[j];
      i = j;
      j = (j << 1) + 1;
    }

    Heap[i] = e;
  }
}

// Definicje metod obiektu DSStruct
//---------------------------------

// Konstruktor
DSStruct::DSStruct(int n)
{
  Z = new DSNode [n];             // Tworzymy tablicê dla elementów zbiorów
}

// Destruktor
//-----------
DSStruct::~DSStruct()
{
  delete [] Z;                    // Usuwamy tablicê ze zbiorami
}

// Tworzy wpis w tablicy Z
//------------------------
void DSStruct::MakeSet(int v)
{
  Z[v].up   = v;
  Z[v].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w którym jest wierzcho³ek v
//----------------------------------------------------------------
int DSStruct::FindSet(int v)
{
  if(Z[v].up != v) Z[v].up = FindSet(Z[v].up);
  return Z[v].up;
}

// £¹czy ze sob¹ zbiory z v i u
//-----------------------------
void DSStruct::UnionSets(Edge e)
{
  int ru,rv;

  ru = FindSet(e.v1);             // Wyznaczamy korzeñ drzewa z wêz³em u
  rv = FindSet(e.v2);             // Wyznaczamy korzeñ drzewa z wêz³em v
  if(ru != rv)                    // Korzenie musz¹ byæ ró¿ne
  {
    if(Z[ru].rank > Z[rv].rank)   // Porównujemy rangi drzew
      Z[rv].up = ru;              // ru wiêksze, do³¹czamy rv
    else
    {
      Z[ru].up = rv;              // równe lub rv wiêksze, do³¹czamy ru
      if(Z[ru].rank == Z[rv].rank) Z[rv].rank++;
    }
  }
}

// Definicje metod obiektu MSTree
//-------------------------------

// Konstruktor - tworzy tablicê pustych list s¹siedztwa
//-----------------------------------------------------
MSTree::MSTree(int n)
{
  int i;

  A = new TNode * [n];            // Tworzymy tablicê dynamiczn¹
  for(i = 0; i < n; i++) A[i] = NULL; // i wype³niamy j¹ pustymi listami
  Alen = n - 1;                   // Zapamiêtujemy d³ugoœæ tablicy
  weight = 0;                     // Zerujemy wagê drzewa
}

// Destruktor - usuwa listy oraz tablicê s¹siedztwa
//-------------------------------------------------
MSTree::~MSTree()
{
  int i;
  TNode *p,*r;

  for(i = 0; i <= Alen; i++)
  {
    p = A[i];
    while(p)
    {
      r = p;                      // Zapamiêtujemy wskazanie
      p = p->next;                // Przesuwamy siê do nastêpnego elementu listy
      delete r;                   // Usuwamy element
    }
  }

  delete [] A;                    // Usuwamy tablicê list s¹siedztwa
}

// Dodaje krawêdŸ do drzewa
//-------------------------
void MSTree::addEdge(Edge e)
{
  TNode *p;

  weight += e.weight;             // Do wagi drzewa dodajemy wagê krawêdzi
  p = new TNode;                  // Tworzymy nowy wêze³
  p->v = e.v2;                    // Wierzcho³ek koñcowy
  p->weight = e.weight;           // Waga krawêdzi
  p->next = A[e.v1];              // Dodajemy p do listy wierzcho³ka v1
  A[e.v1] = p;

  p = new TNode;                  // To samo dla krawêdzi odwrotnej
  p->v = e.v1;                    // Wierzcho³ek koñcowy
  p->weight = e.weight;           // Waga krawêdzi
  p->next = A[e.v2];              // Dodajemy p do listy wierzcho³ka v2
  A[e.v2] = p;
}

// Wyœwietla zawartoœæ drzewa oraz jego wagê
//------------------------------------------
void MSTree::print()
{
  int i;
  TNode *p;

  cout << endl;
  for(i = 0; i <= Alen; i++)
  {
    cout << "Vertex " << i << " - ";
    for(p = A[i]; p; p = p->next) cout << p->v << ":" << p->weight << " ";
    cout << endl;
  }
  cout << endl << endl << "Minimal Spanning Tree Weight = " << weight << endl << endl;
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int n,m;                        // Liczba wierzcho³ków i krawêdzi
  Edge e;
  int i;

  cin >> n >> m;                  // Czytamy liczbê wierzcho³ków i krawêdzi

  DSStruct Z(n);                  // Struktura zbiorów roz³¹cznych
  Queue Q(m);                     // Kolejka priorytetowa oparta na kopcu
  MSTree T(n);                    // Minimalne drzewo rozpinaj¹ce

  for(i = 0; i < n; i++)
    Z.MakeSet(i);                 // Dla ka¿dego wierzcho³ka tworzymy osobny zbiór

  for(i = 0; i < m; i++)
  {
    cin >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne krawêdzie grafu
    Q.push(e);                    // i umieszczamy je w kolejce priorytetowej
  }

  for(i = 1; i < n; i++)          // Pêtla wykonuje siê n - 1 razy !!!
  {
    do
    {
      e = Q.front();              // Pobieramy z kolejki krawêdŸ
      Q.pop();                    // KrawêdŸ usuwamy z kolejki
    } while(Z.FindSet(e.v1) == Z.FindSet(e.v2));
    T.addEdge(e);                 // Dodajemy krawêdŸ do drzewa
    Z.UnionSets(e);               // Zbiory z wierzcho³kami ³¹czymy ze sob¹
  }

  // Wyœwietlamy wyniki

  T.print();

  return 0;
}
