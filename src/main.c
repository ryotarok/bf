#include "common.h"
#include "utils.h"
#include "vm.h"

static void print_usage();

int main(int argc, char** argv) {
  if (argc != 2) {
    print_usage();
    return EXIT_FAILURE;
  }

  uint8_t* data = NULL;
  uint16_t data_bytes = 0;

  bool ok = read_data(argv[1], &data, &data_bytes);
  if (!ok) {
    printf("error: ファイルの読込に失敗。\n");
    return EXIT_FAILURE;
  }

  vm_t* vm = vm_new();
  if (vm == NULL) {
    printf("error: vmの作成に失敗。\n");
    delete_data(data);
    return EXIT_FAILURE;
  }

  vm_setup(vm, data, data_bytes);
  vm_process(vm);

  vm_delete(vm);
  delete_data(data);
  return EXIT_SUCCESS;
}

static void print_usage() {
  printf("usage:\n");
  printf("  bf <filepath>\n");
}
