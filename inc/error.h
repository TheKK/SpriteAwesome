#ifndef ERROR_H
#define ERROR_H

#define ERROR_NO_ERROR		-0x00000000
#define ERROR_INVALID_OPTION	-0x00000001
#define ERROR_MULTI_OPERATION	-0x00000002

char* getError(int errorno);

#endif /* ERROR_H */
