#include <stdio.h>
#include "TC1047_COM3_web.h"

void TC1047_CGI_web(char* data) {
	char* sp, * ep;
	printf_s("Content-Type: text/html; charset=euc-kr\n\n");
	printf_s("<!DOCTYPE HTML PUBLIC \" -//W3C//DTD HTML 4.0//EN\">\n");
	printf_s("<html>\n");
	printf_s("	<head>\n");
	printf_s("		<title> TC1047_COM3.exe(IOT) </title>\n");
	printf_s("	</head>\n");
	printf_s("	<body>\n");
	printf_s("		<h2> IOT : TC1047_COM3 (using a fixed serial port) </h2>\n");
	printf_s("		<hr>\n");

	for (sp = ep = data; *ep; ep++) {
		if (*ep == '\n') {
			*ep = '\0';
			printf_s("%s\n<br>\n", sp);
			sp = ep + 1;
		}
	}

	printf_s("%s \n<br>\n", sp);
	printf_s("	</body>\n");
	printf_s("</html>\n");
}