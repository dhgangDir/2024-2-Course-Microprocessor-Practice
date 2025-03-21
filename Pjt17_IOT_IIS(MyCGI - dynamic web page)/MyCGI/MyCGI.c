// MyCGI.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include "MyCGI_web.h"

int main()
{
    char data[64];

    sprintf_s(data, 64, "Current temperature is 10 degree.");
    MyCGI_web(data);

    return 0;
}
