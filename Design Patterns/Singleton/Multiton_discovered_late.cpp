#include <iostream>
#include <stdlib.h>
#include <map>
using namespace std;

class Multi {
	public:

	static void* operator new(size_t size, int key) {
	    map<int, Multi*>::iterator it = instance.find(key);
	    if(it != instance.end())
	        return (Multi*) (it->second);
	    
	    //instance[key] = (Multi *) malloc(size); OR
	    instance[key] = (Multi *) ::operator new(size);
	    return (Multi*) instance[key];
	}
	
	void fun() {
			cout << "Single class" << endl;
	}
	
	Multi() { };
	Multi(const Multi& obj);
	Multi& operator=(const Multi& obj);
		
	private:
		static map<int, Multi*> instance;
};

map<int, Multi*> Multi::instance;


int main()
{
    Multi *obj = new (1) Multi();
    obj->fun();
    cout << "obj address=" << hex << obj << endl;
    cout << "obj address=" << hex << new (2) Multi() << endl;
    cout << "obj address=" << hex << new (1) Multi() << endl;
    cout << "obj address=" << hex << new (2) Multi() << endl;
}

