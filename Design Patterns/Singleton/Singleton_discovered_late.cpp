#include <iostream>
#include <stdlib.h>
using namespace std;

class Single {
	public:
	
	void* operator new(size_t size) {
	    if (!instance) {
	        instance = (Single *) malloc(size);
	    }
	  return instance;
	}
	
void fun() {
			cout << "Single class" << endl;
 	}
	
	Single() {};
	Single(const Single& obj);
	Single& operator=(const Single& obj);
		
	private:
		static Single* instance;
};

Single* Single::instance = NULL;

int main()
{
    Single *obj = new Single();
    obj->fun();
    cout << "obj address=" << hex << obj << endl;
    cout << "obj address=" << hex << new Single() << endl;
    cout << "obj address=" << hex << new Single() << endl;
}
