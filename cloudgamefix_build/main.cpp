#include"cloudgamefix.hpp"

int main()
{
	std::string text = cloudgameZero::Foundation::Tool::function::getDataFromUrl("https://api.xygeng.cn/one");
	std::cout << text << "\n";
	system("pause");
	return 0;
}