//Code by Bente Tamás Ferencz
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdlib.h>

using namespace std;

ifstream be("bemenet.txt");
ifstream ki("kimenet.txt");
ofstream res("eredmeny.txt");



int peoplecheck(int atm1, int atm2, int vis, int x[], int n)
{
    int ok1=0,ok2=0,ok3=0,i;
    for(i=0;i<n;i++)
    {
        if(x[i]==atm1)
            ok1=1;
        if(x[i]==atm2)
            ok2=1;
        if(x[i]==vis)
            ok3=1;
    }
    if(ok1+ok2+ok3==3)
        return 1;
    return 0;
}
int sorcheck(int atm1, int atm2, int vis, int x[], int oldal[], int n,int db,bool last)
{
    int k=0;
    if(!peoplecheck(atm1,atm2,vis,x,n))
    {
        res<<db<<".atmenesnel olyan koltsegu szemely szerepel a kimenetben, amilyen nincs a bemenetben";
        return 0;
    }
    if(oldal[atm1])
    {
        res<<db<<".atmenesnel az "<<atm1<<" koltsegu szemely nem a baloldalon van";
        return 0;
    }
    if(oldal[atm2])
    {
        res<<db<<".atmenesnel az "<<atm2<<" koltsegu szemely nem a baloldalon van";
        return 0;
    }
    if(!oldal[vis] && !last)
    {
        res<<db<<".atmenesnel az "<<vis<<" koltsegu szemely nem a jobb oldalon van";
        return 0;
    }
    oldal[atm1]=1;
    oldal[atm2]=1;
    if(!last)
    oldal[vis]=0;
    if(atm1>atm2)
        k=atm1;
    else
        k=atm2;
    if(!last)
        k+=vis;
        return k;


}

int atmenes(int n, int x[])
{
    int res;
    if(n==1)
            return x[0];
    if(n==2)
    {
        if(x[0]>x[1])
            return x[0];
        else
            return x[1];
    }
    if(n==3)
        return x[0]+x[1]+x[2];
    if(n>3)
        {
            if(2*x[1]<x[0]+x[n-2])
                res=x[0]+2*x[1]+x[n-1];
            else
                res=2*x[0]+x[n-2]+x[n-1];
            //Ha 2b<a+c=>res=a+2b+d
            //Kulonben res=2a+c+d
            return res+atmenes(n-2,x);

        }

}

int main()
{
    int t0,t,i,n,x[100005],oldal[100005],sum,opt,db,check,koltseg,space,atm1,atm2,vis;
    string s;
    be>>t0;
    for(t=0;t<t0;t++)
    {
        res<<t<<".reszeset:\n";
        be>>n;
        for(i=0;i<n;i++)
            {
                be>>x[i];
                oldal[i]=0;
            }
        sort(x,x+n);
        ki>>sum;
        opt=atmenes(n,x);
        if(opt!=sum)
            {

                if(opt<sum)
                res<<"Az eredmeny nem megfelelo, mivel kevesebb koltseggel is at tudnak jutni!";
                else
                res<<"Hibas eredmeny: A koltseg nem lehet ennyire keves erre a bemenetre";
                while(getline(ki,s))
                    if(s.empty())
                    break;

            }
        else
            {
                res<<"A koltseg optimalis, elso reszpont teljesitve\n";
                db=0;
                koltseg=0;
                while(getline(ki,s) && check)
                {
                    if(s.empty())
                        break;

                    space=s.find(' ');
                    atm1=atoi(s.substr(0,space).c_str());
                    atm2=atoi(s.substr(space+1,s.length()-space-1).c_str());
                    getline(ki,s);
                    vis=atoi(s.c_str());
                    if(s.empty())
                        break;
                    db++;
                    check=sorcheck(atm1,atm2,vis,x,oldal,n,db,false);
                    koltseg+=check;
                }
                if(check)
                {
                    getline(ki,s);
                    space=s.find(' ');
                    atm1=atoi(s.substr(0,space).c_str());
                    atm2=atoi(s.substr(space+1,s.length()-space-1).c_str());
                    check=sorcheck(atm1,atm2,vis,x,oldal,n,db,true);
                    koltseg+=check;
                    for(i=0;i<n;i++)
                        if(!oldal[i])
                        res<<i<<".szemely nincs a jobb oldalon\n";
                    if(koltseg!=opt && i==n)
                        res<<"A visszaadott atmenesi sorrend nem felel meg a megadott koltsegnek";
                    else
                        res<<"Az atmenes sorrendje megfelelo, masodik reszpont teljesitve";
                    cout<<koltseg;
                }
            }
    }




    return 0;
}
