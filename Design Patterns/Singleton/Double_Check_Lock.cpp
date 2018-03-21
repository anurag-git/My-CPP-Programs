#include <iostream>
using namespace std;
#include <mutex>          // std::mutex, std::lock_guard
#include <stdexcept>      // std::logic_error
#include <thread>         // std::thread

std::mutex mtx;


class Single {
	public:
		static Single* getinstance() {
			if(instance == NULL) {
			    try {
			        std::lock_guard<std::mutex> lck (mtx);
			        if(instance == NULL) {
				        instance = new Single();
				        cout << "object returned" << endl;
			        }
			    }
			    catch (std::logic_error&) {
                    std::cout << "[exception caught]\n";
			    }
			}
		
		    return instance;
		}
	
    void fun() {
			cout << "Single class" << endl;
	}
	
	private:
		static Single* instance;
		Single() { };
		Single(const Single& obj);
	// need to comment it, to call getInstance() again to print address
		//Single& operator=(const Single& obj);
};

Single* Single::instance = NULL;


/* we should get same address everytime */

int main()
{
     std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i) {
    threads[i] = std::thread(Single::getinstance);
    //*threads[i]->fun();
  }

  for (auto& th : threads) th.join();
    
    /*
    Single *obj = Single::getinstance();
    cout << "obj address=" << hex << obj << endl;
 	obj->fun();
 	cout << "obj address=" << hex << Single::getinstance() << endl;
 	cout << "obj address=" << hex << Single::getinstance() << endl;
 	Single::getinstance()->fun();
    */
}
