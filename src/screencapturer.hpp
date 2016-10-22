#pragma once

namespace AMB
{
    namespace Readers
    {
        namespace details
        {
            struct Pos
            {
                int x, y;
            };

            struct Rgba
            {
                uint8_t r;
                uint8_t g;
                uint8_t b;
                uint8_t a;

                bool operator==(const Rgba& o) const
                {
                    return o.r == r &&o.g == g &&o.b == b &&o.a == a;
                }

                bool operator!=(const Rgba& o) const
                {
                    return !(*this == o);
                }
            };


            struct Image
            {
                size_t w, h;
                std::vector<Rgba> pixels;

                Rgba& pixel(size_t x, size_t y)
                {
                    return pixels[x + (h-1-y)*w];
                }

                const Rgba& cpixel(size_t x, size_t y) const
                {
                    return pixels[x + (h - 1 - y)*w];
                }

                bool operator==(const Image& other) const
                {
                    return w == other.w && h == other.h && pixels == other.pixels;
                }

                void toCb() const
                {
                    BITMAPINFOHEADER bmih;
                    bmih.biSize = sizeof(BITMAPINFOHEADER);
                    bmih.biWidth = w;
                    bmih.biHeight = h;
                    bmih.biPlanes = 1;
                    bmih.biBitCount = 32;
                    bmih.biCompression = BI_RGB;
                    bmih.biSizeImage = 0;
                    bmih.biXPelsPerMeter = 10;
                    bmih.biYPelsPerMeter = 10;
                    bmih.biClrUsed = 0;
                    bmih.biClrImportant = 0;

                    BITMAPINFO dbmi;
                    ZeroMemory(&dbmi, sizeof(dbmi));
                    dbmi.bmiHeader = bmih;
                    dbmi.bmiColors->rgbBlue = 0;
                    dbmi.bmiColors->rgbGreen = 0;
                    dbmi.bmiColors->rgbRed = 0;
                    dbmi.bmiColors->rgbReserved = 0;

                    HDC hdc = ::GetDC(NULL);

                    HBITMAP hbmp = CreateDIBitmap(hdc, &bmih, CBM_INIT, pixels.data(), &dbmi, DIB_RGB_COLORS);
                    if (hbmp == NULL) {
                        ::MessageBox(NULL, L"Could not load the desired image image", L"Error", MB_OK);
                        return;
                    }

                    ::ReleaseDC(NULL, hdc);

                    // a little test if everything is OK
                    OpenClipboard(NULL);
                    EmptyClipboard();
                    SetClipboardData(CF_BITMAP, hbmp);
                    CloseClipboard();

                    // cleanup
                    DeleteObject(hbmp);
                }

                std::vector<Rgba> getSprite(size_t reqx, size_t reqy, size_t reqw, size_t reqh) const
                {
                    std::vector<Rgba> ret;

                    ret.reserve(reqw*reqh);

                    auto it = ret.begin();
                    for (size_t y = reqy + reqh - 1; y >= reqy; --y)
                        for (size_t x = reqx; x < reqx + reqw; ++x)
                            ret.emplace_back(cpixel(x, y));

                    return ret;
                }
            };

            class ScreenCapturer
            {
            public:
                ScreenCapturer(Image &screen)
                    : hScreen{ GetDC(NULL) }
                    , hDC{ CreateCompatibleDC(hScreen) }
                    , screen{ screen }
                {}

                ~ScreenCapturer()
                {
                    DeleteDC(hDC);
                    ReleaseDC(NULL, hScreen);
                }

                std::vector<Rgba> capture(size_t x, size_t y, size_t w, size_t h)
                {
                    BITMAPINFO MyBMInfo = { 0 };
                    MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);

                    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
                    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
                    BOOL    bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x, y, SRCCOPY);

                    if (0 == GetDIBits(hDC, hBitmap, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS))
                    {
                        // error handling
                    }
                    std::vector<Rgba> ret(w*h);

                    MyBMInfo.bmiHeader.biBitCount = 32;
                    MyBMInfo.bmiHeader.biCompression = BI_RGB;  // no compression -> easier to use
                                                                // correct the bottom-up ordering of lines (abs is in cstdblib and stdlib.h)
                    MyBMInfo.bmiHeader.biHeight = abs(MyBMInfo.bmiHeader.biHeight);

                    // Call GetDIBits a second time, this time to (format and) store the actual
                    // bitmap data (the "pixels") in the buffer lpPixels
                    if (0 == GetDIBits(hDC, hBitmap, 0, MyBMInfo.bmiHeader.biHeight,
                        &ret[0], &MyBMInfo, DIB_RGB_COLORS))
                    {
                        // error handling
                    }

                    DeleteObject(hBitmap);
                    return ret;
                }

                Rgba& getPixel(int x, int y)
                {
                    return screen.pixel(x, y);
                }

                void toCb()
                {
                    screen.toCb();
                }

                void recapture()
                {
                    int x1, y1, x2, y2, w, h;
                    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
                    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
                    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
                    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
                    w = x2 - x1;
                    h = y2 - y1;

                    screen.w = w;
                    screen.h = h;

                    screen.pixels = capture(0, 0, w, h);
                }

            private:
                HDC     hScreen = GetDC(NULL);
                HDC     hDC = CreateCompatibleDC(hScreen);
                Image &screen;
            };
        }
    }
}
