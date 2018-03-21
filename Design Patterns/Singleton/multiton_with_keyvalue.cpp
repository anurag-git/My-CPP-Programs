#include <iostream>
#include <map>
using namespace std;

class Multi {
	public:
	// multiton
	static Multi* getinstance(int key) {
	    map<int, Multi*>::iterator it = instance.find(key);
	    
	    if(it != instance.end())
	        return (Multi*) (it->second);
	    
	    instance[key] = new Multi();
	    return (Multi*) instance[key];
	}
	
void fun() {
			cout << "Single class" << endl;
	}	

	private:
		static map<int, Multi*> instance;
		Multi() { };
		Multi(const Multi& obj);
		// need to comment it, to call getInstance() again to print address
		//Multi& operator=(const Multi& obj);
};

map<int, Multi*> Multi::instance; // static map initialization

//
int main()
{
Multi *obj1 = Multi::getinstance(1);
obj1->fun();
cout << "obj1 address=" << hex << obj1 << endl;	
cout << "obj2 address=" << hex << Multi::getinstance(2) << endl;	
cout << "obj3 address=" << hex << Multi::getinstance(1) << endl;
cout << "obj4 address=" << hex << Multi::getinstance(2) << endl;
cout << "obj5 address=" << hex << Multi::getinstance(1) << endl;
cout << "obj6 address=" << hex << Multi::getinstance(2) << endl;
}
