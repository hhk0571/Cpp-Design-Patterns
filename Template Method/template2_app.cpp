#include "template2_lib.cpp"
#include <iostream>
#include <memory>

using namespace std;

//应用程序开发人员
class Application : public Library
{
  protected:
	virtual bool Step2() override
	{
		//... 子类重写实现
		cout << "override Step2" << endl;
		return true;
	}

	virtual void Step4() override
	{
		//... 子类重写实现
		cout << "override Step4" << endl;
	}
};

int main()
{
	// auto pLib = make_unique<Application>();
	unique_ptr<Library> pLib = make_unique<Application>();
	// Library *pLib = new Application();
	pLib->Run();
	// delete pLib;
}
