//////////////////////////////////////////////////////////////////////////
/*

从界面输入并存储在string中

*/
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string saying[10];
	char tempchr[100];

	for(int i = 0; i< 10 ; i++)
	{
		cout<< (i+1) <<": ";
		cin.get(tempchr, 100);
	
		if (cin)
		{
			printf("cin\n");
		}

		if (cin.get() != '\n')
		{
			printf("cin.get()\n");
		}

		while(cin  && cin.get() != '\n')
			continue;

		if(!cin || tempchr[0] == '\0')
			break;
		else
			saying[i] = tempchr;		
	}

}