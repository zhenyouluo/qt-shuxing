#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <sys/stat.h>

struct error_mgr {
  struct jpeg_error_mgr super;
  jmp_buf jmp;
};

static void _error_exit(j_common_ptr dinfo) {
  struct error_mgr *myerr = (struct error_mgr *)dinfo->err;
  (*dinfo->err->output_message)(dinfo);
  longjmp(myerr->jmp, 1);
}

/* ISO/IEC 10918-1:1993(E) K.3.3. Default Huffman tables used by MJPEG UVC devices
   which don't specify a Huffman table in the JPEG stream. */
static const unsigned char dc_lumi_len[] = 
  {0, 0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
static const unsigned char dc_lumi_val[] = 
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

static const unsigned char dc_chromi_len[] = 
  {0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
static const unsigned char dc_chromi_val[] = 
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

static const unsigned char ac_lumi_len[] = 
  {0, 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d};
static const unsigned char ac_lumi_val[] = 
  {0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21,
   0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71,
   0x14, 0x32, 0x81, 0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1,
   0xc1, 0x15, 0x52, 0xd1, 0xf0, 0x24, 0x33, 0x62, 0x72,
   0x82, 0x09, 0x0a, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x25,
   0x26, 0x27, 0x28, 0x29, 0x2a, 0x34, 0x35, 0x36, 0x37,
   0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
   0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
   0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
   0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x83,
   0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93,
   0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3,
   0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3,
   0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
   0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3,
   0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
   0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf1,
   0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa};
static const unsigned char ac_chromi_len[] = 
  {0, 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77};
static const unsigned char ac_chromi_val[] = 
  {0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31,
   0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22,
   0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1,
   0x09, 0x23, 0x33, 0x52, 0xf0, 0x15, 0x62, 0x72, 0xd1,
   0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25, 0xf1, 0x17, 0x18,
   0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36,
   0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47,
   0x48, 0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
   0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
   0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
   0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a,
   0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a,
   0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
   0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba,
   0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca,
   0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
   0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
   0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa};

#define COPY_HUFF_TABLE(dinfo,tbl,name) do { \
  if(dinfo->tbl == NULL) dinfo->tbl = jpeg_alloc_huff_table((j_common_ptr)dinfo); \
  memcpy(dinfo->tbl->bits, name##_len, sizeof(name##_len)); \
  memset(dinfo->tbl->huffval, 0, sizeof(dinfo->tbl->huffval)); \
  memcpy(dinfo->tbl->huffval, name##_val, sizeof(name##_val)); \
} while(0)

static void insert_huff_tables(j_decompress_ptr dinfo) {
  COPY_HUFF_TABLE(dinfo, dc_huff_tbl_ptrs[0], dc_lumi);
  COPY_HUFF_TABLE(dinfo, dc_huff_tbl_ptrs[1], dc_chromi);
  COPY_HUFF_TABLE(dinfo, ac_huff_tbl_ptrs[0], ac_lumi);
  COPY_HUFF_TABLE(dinfo, ac_huff_tbl_ptrs[1], ac_chromi);
}

// mjpeg frame to rgb
int mjpeg_info(unsigned char *in, int len, int *width, int *height) {
  int i;
  int position = -1;

  for(i = 0;i < len; i++) {
    if((in[i] == 0xFF) && (in[i+1] == 0xc0) ) {
        position = i;
    }
  }
  if(position < 0) {
    return -1;
  }
  position += 5;
  *height = (in[position+0]<<8) | in[position+1];
  *width =  (in[position+2]<<8) | in[position+3];
  return 0;
}


// mjpeg frame to rgb
int mjpeg2bgr(unsigned char *in, int len, unsigned char *out, int out_len) {
  struct jpeg_decompress_struct dinfo;
  struct error_mgr jerr;
  size_t lines_read;
  int step;

  dinfo.err = jpeg_std_error(&jerr.super);
  jerr.super.error_exit = _error_exit;

  if (setjmp(jerr.jmp)) {
    goto fail;
  }

  jpeg_create_decompress(&dinfo);
  jpeg_mem_src(&dinfo, in, len);
  jpeg_read_header(&dinfo, TRUE);

  if (dinfo.dc_huff_tbl_ptrs[0] == NULL) {
    /* This frame is missing the Huffman tables: fill in the standard ones */
    insert_huff_tables(&dinfo);
  }

  dinfo.out_color_space = JCS_EXT_BGR; //JCS_EXT_BGR  JCS_RGB
  dinfo.dct_method = JDCT_IFAST; //JDCT_IFAST JDCT_DEFAULT

  jpeg_start_decompress(&dinfo);
  step = dinfo.output_width * dinfo.output_components;
  if(out_len < dinfo.output_width * dinfo.output_components * dinfo.output_height) {
    return -2;
  }

  lines_read = 0;
  while (dinfo.output_scanline < dinfo.output_height) {
    unsigned char *buffer[1] = { out + lines_read * step };
    int num_scanlines;

    num_scanlines = jpeg_read_scanlines(&dinfo, buffer, 1);
    lines_read += num_scanlines;
  }

  jpeg_finish_decompress(&dinfo);
  jpeg_destroy_decompress(&dinfo);
  return 0;

fail:
  jpeg_destroy_decompress(&dinfo);
  return -1;
}

void rgb2gray(const unsigned char *rgb, int len, unsigned char *gray)
{
  int i, j;
  for(i = 0, j = 0; i < len; i += 3, j++) {
    unsigned char r, g, b;
    r = rgb[i]; g  = rgb[i+1]; b = rgb[i+2];
    gray[j] = (r*38 + g*75 + b*15) >> 7;
    //gray[j] = r*0.299 + g*0.587 + b*0.114;
  }
}

void bgr2gray(const unsigned char *bgr, int len, unsigned char *gray)
{
  int i, j;
  for(i = 0, j = 0; i < len; i += 3, j++) {
    unsigned char r, g, b;
    r = bgr[i+2]; g  = bgr[i+1]; b = bgr[i];
    gray[j] = (r*38 + g*75 + b*15) >> 7;
    //gray[j] = r*0.299 + g*0.587 + b*0.114;
  }
}


int sign3 = 0;
int yuvtorgb(int y, int u, int v)
{
  unsigned int pixel24 = 0;
  unsigned char *pixel = (unsigned char *)&pixel24;
  int r, g, b;
  static long int ruv, guv, buv;

  if(sign3)
  {
    sign3 = 0;
    ruv = 1159*(v-128);
    guv = 380*(u-128) + 813*(v-128);
    buv = 2018*(u-128);
  }

  r = (1164*(y-16) + ruv) / 1000;
  g = (1164*(y-16) - guv) / 1000;
  b = (1164*(y-16) + buv) / 1000;

  if(r > 255) r = 255;
  if(g > 255) g = 255;
  if(b > 255) b = 255;
  if(r < 0) r = 0;
  if(g < 0) g = 0;
  if(b < 0) b = 0;

  pixel[0] = r;
  pixel[1] = g;
  pixel[2] = b;

  return pixel24;
}

int yuvtorgb0(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height)
{
  unsigned int in, out;
  int y0, u, y1, v;
  unsigned int pixel24;
  unsigned char *pixel = (unsigned char *)&pixel24;
  unsigned int size = width*height*2;

  for(in = 0, out = 0; in < size; in += 4, out += 6)
  {
    y0 = yuv[in+0];
    u  = yuv[in+1];
    y1 = yuv[in+2];
    v  = yuv[in+3];

    sign3 = 1;
    pixel24 = yuvtorgb(y0, u, v);
    rgb[out+0] = pixel[0];
    rgb[out+1] = pixel[1];
    rgb[out+2] = pixel[2];

    //sign3 = true;
    pixel24 = yuvtorgb(y1, u, v);
    rgb[out+3] = pixel[0];
    rgb[out+4] = pixel[1];
    rgb[out+5] = pixel[2];
  }
  return 0;
}


#define WIDTH 360
#define HEIGHT 360
#define WORD uint16_t
#define DWORD uint32_t
#define LONG uint32_t

typedef struct tagBITMAPFILEHEADER {
  WORD    bfType;
  DWORD   bfSize;
  WORD    bfReserved1;
  WORD    bfReserved2;
  DWORD   bfOffBits;
} __attribute__((packed)) BMPFILEHEADER_T;

typedef struct tagBITMAPINFOHEADER {
  DWORD      biSize;
  LONG       biWidth;
  LONG       biHeight;
  WORD       biPlanes;
  WORD       biBitCount;
  DWORD      biCompression;
  DWORD      biSizeImage;
  LONG       biXPelsPerMeter;
  LONG       biYPelsPerMeter;
  DWORD      biClrUsed;
  DWORD      biClrImportant;
} __attribute__((packed)) BMPINFOHEADER_T;

// void rgb_to_bmp(unsigned char* pdata, int fd)
// {
//   //分别为rgb数据，要保存的bmp文件名   
//   int size = WIDTH * HEIGHT * 3 * sizeof(char); // 每个像素点3个字节
//   // 位图第一部分，文件信息
//   BMPFILEHEADER_T bfh;
//   memset(&bfh, 0, sizeof(BMPFILEHEADER_T));
//   bfh.bfType = (unsigned short)0x4d42;  //bm
//   bfh.bfSize = size  // data size
//       + sizeof(BMPFILEHEADER_T) // first section size
//       + sizeof(BMPINFOHEADER_T) // second section size
//       ;
//   bfh.bfReserved1 = 0; // reserved
//   bfh.bfReserved2 = 0; // reserved
//   bfh.bfOffBits = sizeof(BMPFILEHEADER_T)+ sizeof(BMPINFOHEADER_T);//真正的数据的位置   
//   //printf("bmp_head== %ld\n", bfh.bfOffBits);   
//   // 位图第二部分，数据信息
//   BMPINFOHEADER_T bih;
//   memset(&bih, 0, sizeof(BMPINFOHEADER_T));
//   bih.biSize = sizeof(BMPINFOHEADER_T);
//   bih.biWidth = WIDTH;
//   bih.biHeight = -HEIGHT;//BMP图片从最后一个点开始扫描，显示时图片是倒着的，所以用-height，这样图片就正了
//   bih.biPlanes = 1;//为1，不用改
//   bih.biBitCount = 24;
//   bih.biCompression = 0;//不压缩
//   bih.biSizeImage = 0;

//   bih.biXPelsPerMeter = 0;//像素每米

//   bih.biYPelsPerMeter = 0;
//   bih.biClrUsed = 0;//已用过的颜色，为0,与bitcount相同
//   bih.biClrImportant = 0;//每个像素都重要

//   write(fd, &bfh, 8);
//   write(fd, &bfh.bfReserved2, sizeof(bfh.bfReserved2));
//   write(fd, &bfh.bfOffBits, sizeof(bfh.bfOffBits));
//   write(fd, &bih, sizeof(BMPINFOHEADER_T));
//   write(fd, pdata, size);
//   printf("size %d \n", 8 + sizeof(bfh.bfReserved2) + sizeof(bfh.bfOffBits) + sizeof(BMPINFOHEADER_T) +size);
// }
