// Example program
#include <iostream>
using namespace std;

class Window {
public:
    virtual void display() =0;
};

class DecoratedWindow : public Window {
  public:
    void display() {
        cout << "decorated window" << endl;
    }
};

class ScrollWindow : public Window {
public:
    void display() {
   	 cout << "Scroll Window";
    }
};

template <class T>
class Factory {
public:
  	static Window* create();
};

template <class T>
Window* Factory<T>::create() {
     return new T();
};


int main()
{
    Window* w;
       
    w=Factory<ScrollWindow>::create();
    w->display();
}
