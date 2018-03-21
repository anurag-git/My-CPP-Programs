#include <iostream>
using namespace std;

class Single {
	public:
		static Single* getinstance() {
			if(instance == NULL) {
				instance = new Single();
				cout << "object returned" << endl;
			}
		
		    return instance;
		}
	
    void fun() {
			cout << "Single class" << endl;
	}
	
	private:
		static Single* instance;
		static int counter;
		Single() { };
		Single(const Single& obj);
	// need to comment it, to call getInstance() again to print address
		//Single& operator=(const Single& obj);
};

Single* Single::instance = NULL;


/* we should get same address everytime */

int main()
{
    Single *obj = Single::getinstance();
    cout << "obj address=" << hex << obj << endl;
 	obj->fun();
 	cout << "obj address=" << hex << Single::getinstance() << endl;
 	cout << "obj address=" << hex << Single::getinstance() << endl;
 	Single::getinstance()->fun();
}
