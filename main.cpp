#include <iostream>

using namespace std;

class multime_perechi;

class pereche
 {

    public:

        pereche(int a,int b):x(a),y(b)
        {
        }

        pereche():x(0),y(0)
        {
        }

        pereche(const pereche &p);
        ~pereche(){}
        void set(int p1,int p2);
        friend istream & operator >>(istream &in,  pereche &p);
        friend ostream & operator <<(ostream &out,  pereche p);
        friend class multime_perechi;
        pereche & operator =(const pereche &ob);

   private:
        int x;
        int y;
 };


pereche::pereche(const pereche &p)
{
    x=p.x;
    y=p.y;
}
void pereche::set(int p1,int p2)
 {
     x=p1;
     y=p2;
 }

 istream & operator >>(istream &in,  pereche &p)
 {

     in>>p.x>>p.y;
     return in;

 }

 ostream & operator <<(ostream &out,  pereche p)
 {

     out<<"("<<p.x<<","<<p.y<<")"<<'\n';
     return out;

}

  pereche & pereche::operator =(const pereche &a)
 {
     x=a.x;
     y=a.y;
     return *this;
 }


class multime_perechi
{

    private:
        int n, dim_max;
        pereche *q;

    public:
        multime_perechi(int max)
        {
            n=0;
            dim_max=max;
            q=new pereche[max];

        }

        multime_perechi()
        {
            n=0;
            dim_max=0;
            q=NULL;
        }

        multime_perechi(const multime_perechi &v);
        ~multime_perechi();
        void inserare(int poz, pereche p);
        pereche stergere (int poz);
        friend istream & operator >>(istream &in,  multime_perechi &z);
        friend ostream & operator <<(ostream &out,  multime_perechi z);
        multime_perechi& operator =(const multime_perechi &ob);
        void set_dim(int lungime);
        int get_dim();

};

 multime_perechi::multime_perechi(const multime_perechi &v)
 {
    int i;
    this->n = v.n;
    this->q=new pereche[n];
    for (i = 0; i < n; i++){
        this->q[i] =v.q[i];
    }

 }

  multime_perechi& multime_perechi::operator=(const multime_perechi &ob)
 {
     if(this==&ob)
        return *this;

     delete[]q;

     n=ob.n;
     q=new pereche[ob.n];

     int i;
     for(i=0;i<ob.n;i++)
        this->q[i]=ob.q[i];

     return *this;
 }

multime_perechi::~multime_perechi()
{
    if(q!=NULL)
    delete[]q;
}

istream & operator >>(istream &in,  multime_perechi &z)
{
     int i,n;
     in>>n;
     z.n=n;
      for(i=0;i<z.n;i++)
        in>>z.q[i];

     return in;
}

ostream & operator <<(ostream &out,  multime_perechi z)
{
     int i;
      for(i=0;i<z.n;i++)
        out<<z.q[i];

     return out;
}

void multime_perechi::set_dim(int lungime)
{
    n=lungime;
}

int multime_perechi::get_dim()
{
    return n;
}

void multime_perechi::inserare(int poz,pereche p)
{
    int i;

    for(i=n;i>poz;i--)
            q[i]=q[i-1];

    q[poz]=p;
    n++;
}

pereche multime_perechi::stergere(int poz)
{
    int i;
    pereche x;
    x=q[poz];

    for(i=poz;i<n-1;i++)
        q[i]=q[i+1];

    n--;
    return x;
}

class stiva_pereche:public multime_perechi
{

    public:
        stiva_pereche(){}
        stiva_pereche(int dim):multime_perechi(dim){}
        stiva_pereche(const stiva_pereche &s):multime_perechi(s){}
        stiva_pereche operator =(const stiva_pereche &s){this->multime_perechi::operator =(s); return *this;}
        ~stiva_pereche(){}
        friend istream & operator >>(istream &in,  stiva_pereche &z);
        friend ostream & operator <<(ostream &out,  stiva_pereche z);
        void push(pereche val) {inserare(0,val);}
        pereche pop() {return stergere(0);}
};

istream & operator >>(istream &in,  stiva_pereche &s)
{
     int i,n;
     pereche p;

     cout<<"Introduceti numarul de elemente din stiva: ";
    in>>n;

    cout<<'\n'<<"Introduceti perechile de numere din stiva: "<<'\n';
    for(i=0;i<n;i++)
        {
            in>>p;
            s.push(p);
        }
    cout<<'\n';

    return in;
}

ostream & operator <<(ostream &out,  stiva_pereche s1)
{
     int i,l;

     l=s1.get_dim();

    out<<"Perechile de numere din stiva sunt: "<<'\n';
    for(i=0;i<l;i++)
        out<<s1.pop();
    out<<'\n';

    return out;
}

class coada_pereche:public multime_perechi
{
    public:
        coada_pereche(){}
        coada_pereche(int dim):multime_perechi(dim){}
        coada_pereche(const coada_pereche &c):multime_perechi(c){}
        coada_pereche operator =(const coada_pereche &c){this->multime_perechi::operator =(c); return *this;}
        ~coada_pereche(){}
        friend istream & operator >>(istream &in,  coada_pereche &z);
        friend ostream & operator <<(ostream &out,  coada_pereche z);
        void push(pereche val) {int l=get_dim(); inserare(l,val);}
        pereche pop() {return stergere(0);}
};

istream & operator >>(istream &in,  coada_pereche &c)
{
     int i,n;
     pereche p;

    cout<<"Introduceti numarul de elemente din coada: ";
    in>>n;

    cout<<'\n'<<"Introduceti perechile de numere din coada: "<<'\n';
    for(i=0;i<n;i++)
        {
            in>>p;
            c.push(p);
        }
    cout<<'\n';

    return in;
}

ostream & operator <<(ostream &out,  coada_pereche c)
{
     int i,l;
     coada_pereche c1;
     c1=c;
     l=c1.get_dim();

    out<<"Perechile de numere din coada sunt: "<<'\n';
    for(i=0;i<l;i++)
        out<<c1.pop();
    out<<'\n';

    return out;
}

void fct (int dim_max)
{
    coada_pereche c1(dim_max),c2(dim_max);
    int x,l,i,j;
    pereche nr;

    cin>>x;
    do
    {
        if(x==1) //se insereaza o pereche
        {
            cin>>nr;
            c1.push(nr);
        }
        else
            if(x==2) //se sterge o pereche
            {
                l=c1.get_dim();

                for(i=0;i<l;i++)
                    c2.push(c1.pop());

                for(i=0;i<l-1;i++)
                    c1.push(c2.pop());
                cout<<"S-a sters elementul: "<<c2.pop()<<'\n';
            }

        cin>>x;
    }
    while(x!=0);

        cout<<"Elementele ramase sunt: "<<'\n';
        l=c1.get_dim();

        for(j=l;j>=1;j--)
         {
             for(i=0;i<j;i++)
                c2.push(c1.pop());
             for(i=0;i<j-1;i++)
                c1.push(c2.pop());
             cout<<c2.pop();
         }

}

int main()
{
    int dim_max;
    pereche p,q;
    cout<<"Introduceti dimensiunea maxima: ";
    cin>>dim_max;
    cout<<'\n';

    coada_pereche c(dim_max);
    stiva_pereche s(dim_max);

    cin>>s;
    stiva_pereche s1(dim_max);
    s1=s;
    cin>>c;
    coada_pereche c1(dim_max);
    c1=c;
    cout<<s;
    cout<<c;
    cout<<s1;
    cout<<c1;

    fct(dim_max);

    return 0;
}
