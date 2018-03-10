//======================================================
// MR sieve - prime generator boolean
// Data: 10.2017
// (C) 2017 mgr inz. Marek Matusiak, mgr Pawel Rzechonek
//======================================================
#include <iostream>
#include <ctime>
#include<fstream>
#include <utility>
#include <algorithm>

using namespace std;

// ----------------------chooser---------------------
int nextPrime(int p, bool s[])
{
    int i = p;
    do
    {
        i++;
    }
    while (!s[i]);
    return i;
}
// ------------------- end chooser --------------------
// -----------------------generator----------------------------
void generator(int p, int e, int n, bool s[])
{
    int l = (e - p + 1);
    int start = e + 1;
    int end = (p) * l + nextPrime(p,s) - 1;
    if (end >= n || end < 0)
    {
        end = n;
    }
    for (int i = start; i <= end; i++)
    {
        s[i] = s[i - l];
    }
}
// -------------------end generator------------------------
unsigned int e, p, n;
// ---------------------cleaning---------------------------
void cleaning(int p, int e, bool s[])
{

    for (int i = e; i >= p; i--)
    {

        if (s[i])
        {

            s[i * p] = false;
        }

    }
}

// ----------------end cleaning------------------
int  main()
{
    bool *s;
    cout << "Enter the maximum number: ";
    cin >> n;
    clock_t start = clock();
    s= new bool[(max(n + 1u, 6u))];

    e = 2;
    p = 2;
    s[2] = true;
    s[3] = true;
    s[5] = true;
    do
    {

        generator(p, e, n, s);
        cleaning(p, e, s);
        e = p * (e - p + 1) + nextPrime(p, s) - 1;
        p = nextPrime(p, s);

    }
    while ((p * e <= n && p * e > 0));

    generator(p, e, n, s);

    do
    {
        cleaning(p, n/p, s);
        p = nextPrime(p, s);
    }
    while (p * p <= n);
    float timeA =(float)(clock() - start)/1000;
    cout << ( "Action time  = " );
    cout << timeA << " s";
    //----------------------------- RECODR TO FILE --------------------------
    ofstream record ("prime.txt");
    int k=0;
    for (int i=0; i<= n; i++)
    {
        if(s[i])
        {
            k+=1;
            record << i <<" ";
            if (k%25==0)
            {
                record << "\n";
            }
        }

    }
    record.close();

    delete [] s;
    return 0;
}
