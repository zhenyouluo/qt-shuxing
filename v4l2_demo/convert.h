int mjpeg2bgr(unsigned char *in, int len, unsigned char *out, int out_len);
int mjpeg_info(unsigned char *in, int len, int *width, int *height);
void drawRectangle(unsigned char *bgr, int width, int height, int left, int top, int right, int bottom);
