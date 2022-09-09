
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 1e5+1;
const int MxK = 1e9;
const int inf = INT_MAX;
#define REP0(i,n) for(int i=0; i<n; i++)
#define REP1(i,n) for(int i=1; i<=n; i++)
#define REP(i,a,b) for(int i=a; i<=b; i++)
#define pb push_back
#define fi first
#define se second
#define reset(X) memset(X, 0, sizeof(X))
#define pii pair<int, int>
#define endl "\n"
#define vint vector<int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define LOG 18



// using complex number class for geometry problems
typedef long double C;   //or use long double. but whenever we use float, the equality(==) should be checked by comparison(|a-b|<eps).
typedef complex<C> Point;
#define X real()
#define Y imag()

C cross_product(Point a, Point b)
{
    return (conj(a)*b).Y;
}

int orientation(Point l1, Point l2, Point p)
{
    C val = cross_product(p-l1, p-l2); //양수면 l1->l2 선분에 대해 왼쪽, 음수면 오른쪽, 0이면 선분위
    if(val>0)return 1;
    if(val==0)return 0;
    return -1;
}


bool online(Point l1, Point l2, Point p)  //collinear 한 세점이 주어졌을때 p는 l1, l2 사이에 있는가?
{
    C left = l1.X; C right=l2.X;
    C down =l1.Y; C up =l2.Y;
    if(left>right)swap(left, right);
    if(down>up)swap(down, up);
    return (left<=p.X && p.X<=right && down<=p.Y && p.Y<=up);
}

bool intersect(Point p1, Point q1, Point p2, Point q2)   //does line segments intersect with each other??
{
    if(orientation(p1,q1,p2)!=orientation(p1,q1,q2) && orientation(p2,q2,p1)!=orientation(p2,q2,q1))return true;
    else{
        if(orientation(p1,q1,p2)==0 && orientation(p1,q1,q2)==0)//네점 collinear
        {
            if (online(p1, q1, p2) || online(p1,q1,q2) || online(p2,q2,p1) || online(p2,q2,q1))return true; //네점 일직선이면서 겹치는경우
        }
        return false;
    }
}


C dist_line_to_point(Point l1, Point l2, Point p)
{
    return cross_product(l1-p, l2-p)/abs(l1-l2);
}


//Point indside polygon : 점으로부터 반직선을 쏘고 polygon과의 교점을 센다. 홀수개면 내부점, 짝수개면 외부점

C shoelace(vector<Point> & v)   //calculate the area of polygon using shoelace formula
{
    C ans=0;
    for (int i=0; i<v.size(); i++)
    {
        ans += cross_product(v[i], v[(i+1)%v.size()]);
    }
    return abs(ans)/2;
}

//Pick's theorem : 모든 꼭지점이 정수 격자점에 놓인 polygon에 대하여, area = 내부 격자점 개수 + 경계격자점/2 +1

//Manhattan distance 문제 (x,y)->(x',y')=(x+y, y-x) : 45도 회전시 dist = (|x1-x2|+|y1-y2|) = max(|x1'-x2'|,|y1'-y2'|) 로 x,y 분리 가능.





int main()
{
    Point p1 ={3,4}; cout<<p1.X<<" "<<p1.Y<<endl;
    Point p2={6,7};
    Point p3 = p1+p2; cout<<p3.X<<" "<<p3.Y<<endl;
    
    cout<<abs(p1-p2)<<endl;
    cout<<arg(p1)<<endl;  //in radian
    Point vec = polar(1.0, 0.5);  //길이가 1이고 방향이 0.5rad인 벡터
    p1 *= vec;
    cout<<arg(p1)<<endl;
    cout<<cross_product(Point{1,1}, Point{2,3})<<endl;
    
}

