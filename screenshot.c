#include <windows.h>

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height);

bool ScreenCapture(int x, int y, int width, int height, char *filename){
  // get a DC compat. w/ the screen
  HDC hDc = CreateCompatibleDC(0);

  // make a bmp in memory to store the capture in
  HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);

  // join em up
  SelectObject(hDc, hBmp);

  // copy from the screen to my bitmap
  BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);

  // save my bitmap
  bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);

  // free the bitmap memory
  DeleteObject(hBmp);

  return ret;
}

main(){
  ScreenCapture(500, 200, 300, 300, "testScreenCap.bmp");
  system("pause");
}