#include <iostream>
using namespace std;

class Multi {
	public:
	// multiton
	static Multi* getinstance() {
	if (counter < 2) {
			instance = new Multi();
		++counter;
		cout << "counter:" << counter << endl;
	}
		return instance;
	}
	
void fun() {
			cout << "Single class" << endl;
	}
	
	private:
		static Multi* instance;
		static int counter;
		Multi() { };
		Multi(const Multi& obj);
		// need to comment it, to call getInstance() again to print address
		//Multi& operator=(const Multi& obj);
};

Multi* Multi::instance = NULL;
int Multi::counter = 0;

int main()
{
Multi *obj = Multi::getinstance();
obj->fun();
cout << "obj address=" << hex << obj << endl;	

Multi *obj1 = Multi::getinstance();
cout << "obj1 address=" << hex << obj1 << endl;	

Multi *obj2 = Multi::getinstance();
cout << "obj2 address=" << hex << &obj2 << endl;

Multi *obj3 = Multi::getinstance();
cout << "obj3 address=" << hex << &obj3 << endl;
}
