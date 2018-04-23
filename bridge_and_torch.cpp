///Problem description: https://progcont.hu/progcont/100067/exercises.html?pid=10037
///Implemets this solution model: https://page.mi.fu-berlin.de/rote/Papers/pdf/Crossing+the+bridge+at+night.pdf
#include <iostream>
#include <algorithm>

using namespace std;

int until_now;

int get_optimal_k(int* t, int n){
    int i, k = 0, minim, mink = 0;
    int ck = (n-2)*t[1]+t[2];
    for(i=3; i<=n; i++)
        ck += t[i];
    minim = ck;
    for(k=1; k<n/2; k++){
        ck += 2*t[2]-t[1]-t[n-2*k+1];
        if(ck<minim){
            minim = ck;
            mink = k;
        }
    }
    return mink;
}

int get_optimal_crossing_time(int* t, int n){
    int i, k = 0, minim;
    int ck = (n-2)*t[1]+t[2];
    for(i=3; i<=n; i++)
        ck += t[i];
    minim = ck;
    for(k=1; k<n/2; k++){
        ck += 2*t[2]-t[1]-t[n-2*k+1];
        if(ck<minim){
            minim = ck;
        }
    }
    return minim;
}

void solve_k_zero(int* t, int n, int k){
    if(n<4){
        until_now = n;
        return;
    }
    cout<<t[1]<<" "<<t[n]<<endl<<t[1]<<endl<<t[1]<<" "<<t[n-1]<<endl<<t[1]<<endl;
    solve_k_zero(t,n-2,0);
}

void solve_k_not_zero(int* t, int n, int k){
    if(n<4){
        until_now = n;
        return;
    }
    cout<<t[1]<<" "<<t[2]<<endl<<t[1]<<endl<<t[n-1]<<" "<<t[n]<<endl<<t[2]<<endl;
    if(k==1)
        solve_k_zero(t,n-2,k-1);
    else
        solve_k_not_zero(t,n-2,k-1);
}

int main()
{
    int t,n,i,x[1005],ti;
    cin>>ti;
    for(t=1;t<=ti;t++)
    {
        cin>>n;
        for(i=1;i<=n;i++)
            cin>>x[i];
        if(n==1)
            cout<<x[1]<<endl<<x[1]<<endl;
        bool printed = false;
        until_now = n;
        if(n>3){
            sort(x+1,x+n+1);
            int k = get_optimal_k(x,n);
            int solution = get_optimal_crossing_time(x,n);
            printed = true;
            cout<<solution<<endl;
            if(k==0)
                solve_k_zero(x,n,k);
            else
                solve_k_not_zero(x,n,k);
        }
        n = until_now;
        if(n==2)
        {
            if(!printed){
                if(x[1]>x[2])
                    cout<<x[1]<<endl;
                else
                    cout<<x[2]<<endl;
            }
            cout<<x[1]<<" "<<x[2]<<endl;
        }
        if(n==3)
        {
            if(!printed){
                sort(x+1,x+n+1);
                cout<<x[1]+x[2]+x[3]<<endl;
            }
            cout<<x[1]<<" "<<x[2]<<endl<<x[1]<<endl<<x[1]<<" "<<x[3]<<endl;
        }
        if(ti!=t)
        cout<<endl;
    }
    return 0;
}
