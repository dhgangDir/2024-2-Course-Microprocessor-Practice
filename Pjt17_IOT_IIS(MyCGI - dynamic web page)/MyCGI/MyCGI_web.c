#include <stdio.h>
#include "MyCGI_web.h"

void MyCGI_web(char* data) {
	char* sp, * ep;
	printf("Content-Type: text/html; charset=euc-kr\n\n");
	printf("<!DOCTYPE HTML PUBLIC \" -//W3C//DTD HTML 4.0//EN\">\n");
	printf("<html>\n");
	printf("	<head>\n");
	printf("		<title>MyPage.exe(Dynamic WebPage)</title>\n");
	printf("	</head>\n");
	printf("	<body>\n");
	printf("		<h2> IOT Testing(MyPage - dynamic web page)</h2>\n");
	printf("		<hr>");
	
	for (sp = ep = data; *ep; ep++) {
		if (*ep == '\n') {
			*ep = '\0';
			printf("%s\n<br>\n", sp);
			sp = ep + 1;
		}
	}

	printf_s("%s </hr>\n", sp);
	printf("	</body>\n");
	printf("</html>\n");
}