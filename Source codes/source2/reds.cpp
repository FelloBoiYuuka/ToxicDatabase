#include <windows.h>
int main()
{
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    HDC hdc, hdcMem; HBITMAP hbm;
    for (int i = 0;; i++, i %= 6) {
        hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcMem, hbm);
        BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
        for (int i = 0; w * h > i; i++) {
            int x = i * w + i, y = i * h + i, f = (y | y + y + -1 + x + w / h);
            ((BYTE*)(data + i))[2] = (f / 1);
        }
        SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCERASE);
        DeleteObject(hbm); DeleteObject(hdcMem);
        DeleteObject(hdc);
        Sleep(rand() % 100);
    }
}
