#include <stdio.h>
#include "IOT_Query_web.h"

void IOT_Query_web(char* data) {
	char* sp, * ep;
	printf_s("Content-Type: text/html; charset=euc-kr\n\n");
	printf_s("<!DOCTYPE HTML PUBLIC \" -//W3C//DTD HTML 4.0//EN\">\n");
	printf_s("<html>\n");
	printf_s("	<head>\n");
	printf_s("		<title> IOT_query.exe(IOT) </title>\n");
	printf_s("	</head>\n");
	printf_s("	<body>\n");
	printf_s("		<h2> IOT : IOT_Query (using a fixed serial port) </h2>\n");
	printf_s("		<hr>\n");

	for (sp = ep = data; *ep; ep++) {
		if (*ep == '\n') {
			*ep = '\0';
			printf_s("%s\n<br>", sp);
			sp = ep + 1;
		}
	}

	printf_s("<br>\n");
	printf_s("	</body>\n");
	printf_s("</html>\n");
}