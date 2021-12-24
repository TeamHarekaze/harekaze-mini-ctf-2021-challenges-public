#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base64.h"

#define N 256   // 2^8

#ifdef b64_USE_CUSTOM_MALLOC
extern void* b64_malloc(size_t);
#endif

#ifdef b64_USE_CUSTOM_REALLOC
extern void* b64_realloc(void*, size_t);
#endif

// The number of buffers we need
int bufc = 0;

char* b64_buf_malloc()
{
	char* buf = b64_malloc(B64_BUFFER_SIZE);
	bufc = 1;
	return buf;
}

char* b64_buf_realloc(unsigned char* ptr, size_t size)
{
	if (size > bufc * B64_BUFFER_SIZE)
	{
		while (size > bufc * B64_BUFFER_SIZE) bufc++;
		char* buf = b64_realloc(ptr, B64_BUFFER_SIZE * bufc);
		if (!buf) return NULL;
		return buf;
	}

	return ptr;
}

unsigned char *
b64_decode (const char *src, size_t len) {
  return b64_decode_ex(src, len, NULL);
}

unsigned char *
b64_decode_ex (const char *src, size_t len, size_t *decsize) {
  int i = 0;
  int j = 0;
  int l = 0;
  size_t size = 0;
  unsigned char *dec = NULL;
  unsigned char buf[3];
  unsigned char tmp[4];

  // alloc
  dec = (unsigned char *) b64_buf_malloc();
  if (NULL == dec) { return NULL; }

  // parse until end of source
  while (len--) {
    // break if char is `=' or not base64 char
    if ('=' == src[j]) { break; }
    if (!(isalnum(src[j]) || '+' == src[j] || '/' == src[j])) { break; }

    // read up to 4 bytes at a time into `tmp'
    tmp[i++] = src[j++];

    // if 4 bytes read then decode into `buf'
    if (4 == i) {
      // translate values in `tmp' from table
      for (i = 0; i < 4; ++i) {
        // find translation char in `b64_table'
        for (l = 0; l < 64; ++l) {
          if (tmp[i] == b64_table[l]) {
            tmp[i] = l;
            break;
          }
        }
      }

      // decode
      buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
      buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
      buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

      // write decoded buffer to `dec'
      dec = (unsigned char *) b64_buf_realloc(dec, size + 3);
      if (dec != NULL){
        for (i = 0; i < 3; ++i) {
          dec[size++] = buf[i];
        }
      } else {
        return NULL;
      }

      // reset
      i = 0;
    }
  }

  // remainder
  if (i > 0) {
    // fill `tmp' with `\0' at most 4 times
    for (j = i; j < 4; ++j) {
      tmp[j] = '\0';
    }

    // translate remainder
    for (j = 0; j < 4; ++j) {
        // find translation char in `b64_table'
        for (l = 0; l < 64; ++l) {
          if (tmp[j] == b64_table[l]) {
            tmp[j] = l;
            break;
          }
        }
    }

    // decode remainder
    buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
    buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
    buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

    // write remainer decoded buffer to `dec'
    dec = (unsigned char *)b64_buf_realloc(dec, size + (i - 1));
    if (dec != NULL){
      for (j = 0; (j < i - 1); ++j) {
        dec[size++] = buf[j];
      }
    } else {
      return NULL;
    }
  }

  // Make sure we have enough space to add '\0' character at end.
  dec = (unsigned char *)b64_buf_realloc(dec, size + 1);
  if (dec != NULL){
    dec[size] = '\0';
  } else {
    return NULL;
  }

  // Return back the size of decoded string if demanded.
  if (decsize != NULL) {
    *decsize = size;
  }

  return dec;
}

void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int KSA(char *key, unsigned char *S) {

    int len = strlen(key);
    int j = 0;

    for(int i = 0; i < N; i++)
        S[i] = i;

    for(int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;

        swap(&S[i], &S[j]);
    }

    return 0;
}


int RC4(char *key, char *plaintext, unsigned char *ciphertext) {

    unsigned char S[N];
    KSA(key, S);

    //PRGA(S, plaintext, ciphertext);
    int i = 0;
    int j = 0;

    for(size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % N];

        ciphertext[n] = rnd ^ plaintext[n];

    }

    return 0;
}


int main(void){
    char *key = "n96t6tPFEElhk0uSjcoeJasW";
    char *false_text = malloc(sizeof(int) * 16);
    memset(false_text, '\0', 16);
    char *false_enc_text = "6jTJ+b/RSJZxBLGcVcbglt==";
    int r = RC4(key, b64_decode(false_enc_text, strlen(false_enc_text)), false_text);
    if(r == 0){
        printf("%.16s", false_text);
    }else{
        char *flag_text = malloc(sizeof(int) * 30);
        char *flag_enc_text = "5jqb5bvFEphcP4DHcvWM9rr46tVjjpxX4tMJImtyvoNhfIQazYJ4Z7a7oJo=";
        int r = RC4(key, b64_decode(flag_enc_text, strlen(flag_enc_text)), flag_text);
        printf("flag is %s",flag_text);
    }
    return 0;
}