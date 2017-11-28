// Wyszukiwanie cyklu lub ścieżki Eulera//YU BYL DOMINIK
// Algorytm Fleury'ego
// Data: 8.02.2014
// (C)2014 mgr Jerzy Wałaszek
//---------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Zmienne globalne
//tu BYL DOM OMIRFJSTYTGeregartharh
int n,m,cv,sptr;
char **A;                       // Macierz sąsiedztwa
int *S;                         // Stos w tablicy
int *D;                         // Tablica numerów wierzchołków

// Funkcja wyszukująca mosty w grafie
// We:
// v  - numer wierzchołka startowego
// vf - ojciec wierzchołka v na drzewie rozpinającym
// Wy:
// Parametr Low dla wierzchołka v
//---------------------------------------------------
int DFSb(int v,int vf)
{
  int Low,temp,i;

  D[v] = cv;                    // Numerujemy wierzchołek
  Low  = cv;                    // Wstępna wartość Low
  cv++;                         // Numer dla następnego wierzchołka
  for(i = 0; i < n; i++)        // Przeglądamy sąsiadów v
    if(A[v][i] && (i != vf))
    {
      if(!D[i])                 // Jeśli sąsiad nieodwiedzony, to
      {
        temp = DFSb(i,v);       // to wywołujemy rekurencyjnie DFSb()
        if(temp < Low) Low = temp; // Modyfikujemy Low
      }
      else if(D[i] < Low) Low = D[i];
    }

  if((vf > -1) && (Low == D[v])) // Mamy most?
    A[vf][v] = A[v][vf] = 2;    // Oznaczamy krawędź vf-v jako most

  return Low;
}

// Procedura wyszukuje cykl lub ścieżkę Eulera
// We:
// v - wierzchołek startowy
//--------------------------------------------
void findEuler(int v)
{
  int u,w,i;

  while(true)                   // W pętli przetwarzamy graf
  {
    S[sptr++] = v;              // v umieszczamy na stosie

    for(u = 0;(u < n) && !A[v][u];u++); // Szukamy pierwszego sąsiada v

    if(u == n) break;           // Nie ma sąsiadów, kończymy

    for(i = 0; i < n; i++) D[i] = 0; // Zerujemy tablicę D

    cv = 1;                     // Numer pierwszego wierzchołka dla DFS
    DFSb(v,-1);                 // Identyfikujemy krawędzie-mosty

    // Szukamy krawędzi nie będącej mostem

    for(w = u + 1;(A[v][u] == 2) && (w < n); w++)
      if(A[v][w]) u = w;

    A[v][u] = A[u][v] = 0;      // Usuwamy krawędź v-u
    v = u;                      // Przechodzimy do u
  }
}

// **********************
// *** Program główny ***
// **********************

int main()
{
  int i,j,v1,v2;
  int *VD;                      // Stopnie wierzchołków

  cin >> n >> m;                // Czytamy liczbę wierzchołków i krawędzi

  A = new char * [n];           // Tworzymy tablicę wskaźników
  for(i = 0; i < n; i++)
    A[i] = new char [n];        // Tworzymy wiersze macierzy sąsiedztwa

  // Macierz wypełniamy zerami

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) A[i][j] = 0;

  VD = new int [n];             // Tworzymy tablicę stopni
  for(i = 0; i < n; i++)        // Zerujemy tablicę stopni
    VD[i] = 0;

  D = new int [n];              // Tworzymy tablicę numerów

  S = new int [m + 1];          // Tworzymy pusty stos
  sptr = 0;

  // Odczytujemy kolejne definicje krawędzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzchołek startowy i końcowy krawędzi
    A[v1][v2] = 1;      // Krawędź v1->v2 obecna
    A[v2][v1] = 1;      // Krawędź v2->v1 obecna
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

  // Wyznaczamy cykl lub ścieżkę Eulera

  findEuler(v1);

  // Wypisujemy zawartość stosu

  if(VD[v1] % 2) cout << "EULERIAN PATH :"; else cout << "EULERIAN CYCLE :";

  for(i = 0; i < sptr; i++) cout << setw(3) << S[i];
  cout << endl;

 //To zmieniłem

  for(i = 0; i < n; i++) delete [] A[i];
  delete [] A;
  delete [] S;
  delete [] D;
  delete [] VD;

  return 0;
} 
