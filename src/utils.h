#ifndef BF_UTILS_H
#define BF_UTILS_H

#include "common.h"

bool read_data(char* filepath, uint8_t** data, uint16_t* data_bytes);
void delete_data(uint8_t* data);

#endif//BF_UTILS_H