#include<iostream>
using namespace std;
static const char* font[] = {
	"AppleGothic",
	"HiraKakuProN-W6",
	"HiraKakuProN-W3",
	"MarkerFelt-Thin",
	"STHeitiK-Medium",
	"STHeitiK-Light"
};
char const * _font[] = {
	"S",
	"STt"
};
int main()
{
	cout<<sizeof(font)<<endl;
	cout<<sizeof(*font)<<endl;
	cout<<sizeof(font)/(sizeof(*font))<<endl;
	
	cout<<sizeof(_font)<<endl;
	cout<<sizeof(*_font)<<endl;
	
	char const * dong = "hello";
	cout<<"dong  =  "<<sizeof(dong)<<endl;
	
	char *dong2 = "";
	cout<<"dong2 =  "<<sizeof(dong2)<<endl;
	
}
