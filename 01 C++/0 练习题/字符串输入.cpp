//////////////////////////////////////////////////////////////////////////
/*

输出某个日期的下一秒是哪一天

*/
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>
#include <string>

char s[100];

void main()
{	
	time_t tt;
	struct tm *tempP = (struct tm*)malloc(sizeof(struct tm));

	int year=0, month=0, day=0, hour=0, min=0, sec=0;
	printf("请输入：年月日时分秒 （例如： 2017-09-11-18-53-20)\n");
	scanf("%d-%d-%d-%d-%d-%d", &year, &month, &day, &hour, &min, &sec);

	//printf("year %d, month %d, day %d, %d:%d:%d\n", year, month, day, hour, min, sec);

	tempP->tm_year = year-1900;
	tempP->tm_mon  = month-1;
	tempP->tm_mday = day;
	tempP->tm_hour = hour;
	tempP->tm_min = min;
	tempP->tm_sec = sec;
	tempP->tm_isdst = 0;
	
	tt = mktime(tempP);
	tt += 1;
	tt += 28800; //时差

	struct tm *outPm = gmtime(&tt);
	strftime(s, sizeof(s), "%Y-%m-%d-%H-%M-%S", outPm);

	printf("%s", s);
}