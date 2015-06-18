#include<stack>
#include<fstream>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<queue>
#include "double_linked_list.cpp"
using namespace std;
int number;



template<typename T>

class Container
{
protected:
    T a[1024];
public:

    int type;
    Container()
    {
        type=0;
    }
    virtual int size() =0;
    virtual bool empty() =0;
    virtual void pop() =0;
    virtual void push(T ) =0;
    virtual T top() =0;
    virtual T back() =0;
    virtual T  front() =0;
    void print()
    {
        int br=-1;
        while (!empty())
        {
            br++;
            a[br]=top();
            pop();
        }
        if(type!=2)
            for(int i=0; i<=br; i++)
                cout<<a[i]<<' ';
        else
            for(int i=br; i>=0; i--)
                cout<<a[i]<<' ';
        cout<<endl;

        for(int i=br; i>=0; i--)
            push(a[i]);
        return;

    }


    bool member(T const& x)
    {
        int br=-1;
        while (!empty())
        {
            br++;
            a[br]=top();
            cout<<a[br]<<' ';
            pop();
        }
        cout<<endl;
        bool fl=0;
        for(int i=0; i<=br; i++)
            if(a[i] == x)
                fl=1;
        for(int i=br; i>=0; i--)
            push(a[i]);
        return fl;

    }



    void sortc()
    {
        int br=-1,rq;
        while (!empty())
        {
            br++;
            a[br]=top();
            pop();
        }
        bool fl=0;
        for(int i=br; i>=0; i--)
            for(int j=0; j<i; j++)
                if( a[j] > a[j+1])
                {
                    rq=a[j];
                    a[j]=a[j+1];
                    a[j+1]=rq;
                }

        for(int i=br; i>=0; i--)
            push(a[i]);
        return;
    }

    bool prop( bool (*condition)(T const& x) )
    {
        int br=-1;
        while (!empty())
        {
            br++;
            a[br]=top();
            pop();
        }
        bool fl=0;
        for(int i=0; i<=br; i++)
            if( condition(a[i]) )
            {
                fl=1;
                break;
            }

         for(int i=br; i>=0; i--)
            push(a[i]);

        return fl;

    }



};


class Stack : public Container<int>
{
    stack <int> st;
public:
    Stack()
    {
        type=1;
    }
    int size()
    {
        return st.size();
    }
    bool empty()
    {
        return st.empty();
    }
    void pop()
    {
        st.pop();
    }
    int  top()
    {
        return st.top();
    }
    void push(int x)
    {
        st.push(x);
    }

    int  back()
    {
        return st.top();
    }
    int   front() {}



};

class Queue : public Container<int>
{
    queue <int> qq;
public:
    Queue()
    {
        type=2;
    }
    int size()
    {
        return qq.size();
    }
    bool empty()
    {
        return qq.empty();
    }
    int  front()
    {
        return qq.front();
    }
    int  back()
    {
        return qq.back();
    }
    void push(int x)
    {
        qq.push(x);
    }
    void pop()
    {
        qq.pop();
    }
    int  top()
    {
        return qq.front();
    }

};



class Dlist : public Container<int>
{

    DoubleLinkedList <int> dl;
    DoubleLinkedListIterator <int> uk;
    int k;
public:
    Dlist()
    {
        type=3;
    }
    int size() { }
    bool empty()
    {
        return dl.empty();
    }
    int  front() {  }
    int  back() { }
    void push(int x)
    {
        dl.insertAfter(x, dl.end());
    }
    void pop()
    {
        uk=dl.end();
        dl.deleteAt(k,uk);
    }
    int  top()
    {
        return (*dl.end());
    }

};




Container<int>* c[128];



void filter( bool (*condition)(int const& x))
{
  bool f[128];

  int nc[128],newn=0;
  for(int i=0;i<number;i++)
    if(c[i]->prop(condition) == 0)
     {
        nc[newn]=i;
        newn++;
     }

  for(int i=0;i<newn;i++)
    c[i]=c[ nc[i] ];

  number=newn;

  for(int i=0;i<number;i++)
        c[i]->print();


  return;


}


void sortall()
{
    for(int i=0; i<number; i++)
        c[i]->sortc();
    for(int i=0; i<number; i++)
        c[i]->print();
    return;
}


bool cc(const int& x)
{
    if(x%10==0)
        return true;
    return false;


}




int main()
{
    int x;
    cout<<"number of containers= ";
    cin>>number;
    ifstream in ("input.txt");
    srand(time (NULL));
    Stack y[number];
    Queue z[number];
    Dlist w[number];
    for(int i=0; i<number; i++)
    {
        switch(rand() %3)
        {
        case 0:
            c[i]=&(y[i]);
            break;
        case 1:
            c[i]=&(z[i]);
            break;
        case 2:
            c[i]=&(w[i]);
            break;

        }



        do
        {
            in>>x;
            c[i]->push(x);
            //cout<<c[i]->back()<<' ';
        }
        while ( in.get() != '\n' );
    }

cout<<"Start:"<<endl;
  for(int i =0;i<number;i++)
    c[i]->print();
cout<<endl;

cout<<"x= ";
cin>>x;
    for(int i =0;i<number;i++)
    {
cout<<"Is "<<x<<" a member of container no." << i<< " ?"<<endl;
  if(c[i]->member(x)) cout<<"yes"<< endl;
  else
    cout<<"no"<<endl;
 cout<<endl;
    }


 for(int i =0;i<number;i++)
    {
cout<<"Does container no." << i<< " have the property (an element with condition- if x%10 == 0)"<<endl;
  if(c[i]->prop(cc)) cout<<"yes"<< endl;
  else
    cout<<"no"<<endl;
 cout<<endl;
    }


//    for(int i =0;i<number;i++)
  //   cout<<c[i]->type;
    //cout<<endl;
cout<<"Sort all containers"<<endl;

    sortall();
cout<<endl;
     cout<<"Filter containers with condition cc - if x%10 == 0"<<endl;

// cout<<c[0]->prop(cc);

   filter(cc);


    return 0;
}
