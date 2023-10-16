#include "HelloWorld.h"

STDMETHODIMP CHelloWorld::SayHello(LPCSTR message)
{
	std::cout << "Hello" << "\n";
	return S_OK;
}