// Wyszukiwanie cyklu lub œcie¿ki Eulera
// Algorytm Fleury'ego
// Data: 8.02.2014
// (C)2014 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Zmienne globalne

int n,m,cv,sptr;
char **A;                       // Macierz s¹siedztwa
int *S;                         // Stos w tablicy
int *D;                         // Tablica numerów wierzcho³ków

// Funkcja wyszukuj¹ca mosty w grafie
// We:
// v  - numer wierzcho³ka startowego
// vf - ojciec wierzcho³ka v na drzewie rozpinaj¹cym
// Wy:
// Parametr Low dla wierzcho³ka v
//---------------------------------------------------
int DFSb(int v,int vf)
{
  int Low,temp,i;

  D[v] = cv;                    // Numerujemy wierzcho³ek
  Low  = cv;                    // Wstêpna wartoœæ Low
  cv++;                         // Numer dla nastêpnego wierzcho³ka
  for(i = 0; i < n; i++)        // Przegl¹damy s¹siadów v
    if(A[v][i] && (i != vf))
    {
      if(!D[i])                 // Jeœli s¹siad nieodwiedzony, to
      {
        temp = DFSb(i,v);       // to wywo³ujemy rekurencyjnie DFSb()
        if(temp < Low) Low = temp; // Modyfikujemy Low
      }
      else if(D[i] < Low) Low = D[i];
    }

  if((vf > -1) && (Low == D[v])) // Mamy most?
    A[vf][v] = A[v][vf] = 2;    // Oznaczamy krawêdŸ vf-v jako most

  return Low;
}

// Procedura wyszukuje cykl lub œcie¿kê Eulera
// We:
// v - wierzcho³ek startowy
//--------------------------------------------
void findEuler(int v)
{
  int u,w,i;

  while(true)                   // W pêtli przetwarzamy graf
  {
    S[sptr++] = v;              // v umieszczamy na stosie

    for(u = 0;(u < n) && !A[v][u];u++); // Szukamy pierwszego s¹siada v

    if(u == n) break;           // Nie ma s¹siadów, koñczymy

    for(i = 0; i < n; i++) D[i] = 0; // Zerujemy tablicê D

    cv = 1;                     // Numer pierwszego wierzcho³ka dla DFS
    DFSb(v,-1);                 // Identyfikujemy krawêdzie-mosty

    // Szukamy krawêdzi nie bêd¹cej mostem

    for(w = u + 1;(A[v][u] == 2) && (w < n); w++)
      if(A[v][w]) u = w;

    A[v][u] = A[u][v] = 0;      // Usuwamy krawêdŸ v-u
    v = u;                      // Przechodzimy do u
  }
}

// **********************
// *** Program g³ówny ***
// **********************

int main()
{
  int i,j,v1,v2;
  int *VD;                      // Stopnie wierzcho³ków

  cin >> n >> m;                // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new char * [n];           // Tworzymy tablicê wskaŸników
  for(i = 0; i < n; i++)
    A[i] = new char [n];        // Tworzymy wiersze macierzy s¹siedztwa

  // Macierz wype³niamy zerami

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) A[i][j] = 0;

  VD = new int [n];             // Tworzymy tablicê stopni
  for(i = 0; i < n; i++)        // Zerujemy tablicê stopni
    VD[i] = 0;

  D = new int [n];              // Tworzymy tablicê numerów

  S = new int [m + 1];          // Tworzymy pusty stos
  sptr = 0;

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    A[v1][v2] = 1;      // KrawêdŸ v1->v2 obecna
    A[v2][v1] = 1;      // KrawêdŸ v2->v1 obecna
    VD[v1]++;
    VD[v2]++;           // Obliczamy stopnie v1 i v2
  }

  cout << endl;

  // Szukamy pozycji startowej v1

  for(v1 = 0; v1 < n; v1++)
    if(VD[v1]) break;

  for(i = v1; i < n; i++)
    if(VD[i] % 2)
    {
      v1 = i;
      break;
    }

  // Wyznaczamy cykl lub œcie¿kê Eulera

  findEuler(v1);

  // Wypisujemy zawartoœæ stosu

  if(VD[v1] % 2) cout << "EULERIAN PATH :"; else cout << "EULERIAN CYCLE :";

  for(i = 0; i < sptr; i++) cout << setw(3) << S[i];
  cout << endl;

 //To zmieni³em

  for(i = 0; i < n; i++) delete [] A[i];
  delete [] A;
  delete [] S;
  delete [] D;
  delete [] VD;

  return 0;
} 
