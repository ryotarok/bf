#include "vm.h"

#define MEMORY_BYTES UINT16_MAX

struct vm_rec {
  struct {
    uint16_t instruction_pointer;
    uint16_t data_pointer;
    uint16_t bracket_depth;
  } regs;

  uint8_t instructions[MEMORY_BYTES];
  uint8_t data[MEMORY_BYTES];
};

static void vm_seek_left_bracket(vm_t* vm);
static void vm_seek_right_bracket(vm_t* vm);

vm_t* vm_new(void) {
  vm_t* vm = (vm_t*)malloc(sizeof(vm_t));
  if (vm == NULL) {
    return NULL;
  }
  memset(vm, 0, sizeof(vm_t));
  return vm;
}

void vm_delete(vm_t* vm) { free(vm); }

void vm_setup(vm_t* vm, uint8_t* instructions, uint16_t instructions_bytes) {
  memset(vm, 0, sizeof(vm_t));
  memcpy(vm->instructions, instructions, instructions_bytes);
}

void vm_process(vm_t* vm) {
  while (vm->instructions[vm->regs.instruction_pointer] != 0) {
    switch (vm->instructions[vm->regs.instruction_pointer]) {
      case '>':
        ++vm->regs.data_pointer;
        break;
      case '<':
        --vm->regs.data_pointer;
        break;
      case '+':
        ++vm->data[vm->regs.data_pointer];
        break;
      case '-':
        --vm->data[vm->regs.data_pointer];
        break;
      case '.':
        putchar(vm->data[vm->regs.data_pointer]);
        break;
      case ',':
        vm->data[vm->regs.data_pointer] = getchar();
        break;
      case '[':
        if (vm->data[vm->regs.data_pointer] != 0) {
          ++vm->regs.bracket_depth;
        } else {
          vm_seek_right_bracket(vm);
        }
        break;
      case ']':
        if (vm->data[vm->regs.data_pointer] != 0) {
          vm_seek_left_bracket(vm);
        } else {
          --vm->regs.bracket_depth;
        }
        break;
    }
    ++vm->regs.instruction_pointer;
  }
}

static void vm_seek_left_bracket(vm_t* vm) {
  uint16_t right_bracket_depth = vm->regs.bracket_depth;
  while ((0 <= vm->regs.bracket_depth) &&
         (vm->instructions[vm->regs.instruction_pointer] != 0)) {
    switch (vm->instructions[vm->regs.instruction_pointer]) {
      case '[':
        ++vm->regs.bracket_depth;
        if (vm->regs.bracket_depth == right_bracket_depth) {
          return;
        }
        break;
      case ']':
        --vm->regs.bracket_depth;
        break;
    }
    --vm->regs.instruction_pointer;
  }
}

static void vm_seek_right_bracket(vm_t* vm) {
  uint16_t left_bracket_depth = vm->regs.bracket_depth;
  while ((vm->regs.bracket_depth < UINT16_MAX) &&
         (vm->instructions[vm->regs.instruction_pointer] != 0)) {
    switch (vm->instructions[vm->regs.instruction_pointer]) {
      case '[':
        ++vm->regs.bracket_depth;
        break;
      case ']':
        --vm->regs.bracket_depth;
        if (vm->regs.bracket_depth == left_bracket_depth) {
          return;
        }
        break;
    }
    ++vm->regs.instruction_pointer;
  }
}

