// Example program
#include <iostream>
using namespace std;

class Window {
  public:
    virtual void display() = 0;
};

class BorderedWindow : public Window {
public:
    void display() {
   	 cout << "Bordered Window";
    }
};

class ScrollWindow : public Window {
public:
    void display() {
   	 cout << "Scroll Window";
    }
};

class Factory {
public:
  	static Window* create(int);
};

Window* Factory::create(int input) {
    if(input == 1)  
   	 return new BorderedWindow();
    else if(input == 2)     
   	 return new ScrollWindow();
}

int main()
{
    Window* w;
    int input;
    cout << " Enter 1 for BorderedWindow, 2 for ScrollWindow";
    cin >> input;
    
    //if(input == 1)  w=new BorderedWindow();
    //else if(input == 2)     w=new ScrollWindow();
    //OR
    // instead use factory
    w=Factory::create(input);
  
    w->display();
}
