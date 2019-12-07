#include "utils.h"

static uint16_t get_file_bytes(const char* filepath);
static bool read_file(const char* filepath, uint16_t data_bytes, uint8_t** data);

bool read_data(char* filepath, uint8_t** data, uint16_t* data_bytes) {
  *data_bytes = get_file_bytes(filepath);
  if (*data_bytes == 0) {
    return false;
  }
  *data = (uint8_t*)malloc(sizeof(uint8_t) * (*data_bytes));
  if (*data == NULL) {
    return false;
  }

  memset(*data, 0, sizeof(uint8_t) * (*data_bytes));
  return read_file(filepath, *data_bytes, data);
}

void delete_data(uint8_t* data) {
  free(data);
}

// 読み込むファイルサイズがuint16_tに納まっていろ
static uint16_t get_file_bytes(const char* filepath) {
  FILE* fp = fopen(filepath, "rb");
  if (fp == NULL) {
    return 0;
  }
  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return 0;
  }

  fpos_t pos = 0;
  int16_t getpos_res = fgetpos(fp, &pos);
  fclose(fp);

  return (getpos_res != 0) ? 0 : (uint16_t)pos;
}

// dataはすでにメモリが確保されていろ
static bool read_file(const char* filepath, uint16_t data_bytes, uint8_t** data) {
  FILE* fp = fopen(filepath, "rb");
  if (fp == NULL) {
    return false;
  }

  uint16_t read_bytes = fread(*data, sizeof(uint8_t), data_bytes, fp);
  fclose(fp);

  return (read_bytes == data_bytes);
}
