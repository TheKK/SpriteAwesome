#ifndef ERROR_H
#define ERROR_H

#include <cstdint>

enum ErrorNos {
	ERROR_NO_ERROR = 0x00000000,
	ERROR_INVALID_OPTION ,
	ERROR_MULTI_OPERATION,
	ERROR_NOT_ENOUGH_INPUT,
	ERROR_TOO_MUCH_INPUT,
	ERROR_TEX_LOAD_FAILED
};

char* getError(uint32_t errorno);

#endif /* ERROR_H */
