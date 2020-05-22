
#include <Steel.hpp>

class Test : public Steel::Application
{
public:
	Test()
	{
	}
	~Test()
	{

	}
private:

};

Steel::Application* Steel::CreateApplication()
{
	return new Test();
}