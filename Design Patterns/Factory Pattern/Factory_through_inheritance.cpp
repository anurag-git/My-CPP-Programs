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

class WindowFactory {
public:
  	virtual Window* create() = 0;
};

class BorderedWindowFactory : public WindowFactory {
    public:
        Window* create() {
            return new BorderedWindow();   
        }
};

class ScrollWindowFactory : public WindowFactory {
    public:
        Window* create() {
            return new ScrollWindow();
        }
};

int main()
{
    Window* w = NULL;
    WindowFactory *winFact = NULL;
    int input;
    cout << " Enter 1 for BorderedWindow, 2 for ScrollWindow";
    cin >> input;
    
    if(input == 1)  
        winFact=new BorderedWindowFactory();
    else if(input == 2)
        winFact=new ScrollWindowFactory();
    
    w = winFact->create();
    
    w->display();
}

