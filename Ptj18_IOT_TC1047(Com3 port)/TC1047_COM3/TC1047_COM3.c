// TC1047_COM3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdlib.h>
#include "TC1047_COM3_web.h"
#include "CGI_get_data.h"

int main()
{
    char* data;

    data = (char*)malloc((DFL_N_HEAD + DFL_N_TAIL) * CHR_P_LINE);

    CGI_get_data("COM3", "tc1047", DFL_N_HEAD, DFL_N_TAIL, data);
    TC1047_CGI_web(data);

    
    return 0;
}

