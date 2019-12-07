#ifndef BF_VM_H
#define BF_VM_H

#include "common.h"

typedef struct vm_rec vm_t;

vm_t* vm_new(void);
void vm_delete(vm_t* vm);
void vm_setup(vm_t* vm, uint8_t* instrutions, uint16_t instructions_bytes);
void vm_process(vm_t* vm);

#endif//BF_VM_H
