//
// queryGet.h
//

#ifndef __QUERYGET_H__
#define __QUERYGET_H__

int queryGet(char* port, char* cmd, char* msg);
char* getEnv(char* en);
void decode(char* bfp, char* qp);

#endif