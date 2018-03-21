#include <iostream>
using namespace std;

class Single {
	public:
	// meyers singleton
	static Single& getInstance() {
	    static Single stat_instance;
	    return stat_instance;
	}
	
	void fun() {
			cout << "Single class" << endl;
	}
	
	private:
		Single() { };
		Single(const Single& obj);
		// need to comment it, to call getInstance() again to print address
		//Single& operator=(const Single& obj);
};

int main()
{
    Single& obj = Single::getInstance();
    obj.fun();
    cout << "obj address=" << hex << &obj << endl;
    obj = Single::getInstance();
    cout << "obj address=" << hex << &obj << endl;
}
