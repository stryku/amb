#pragma once

#include "utils/Structs.hpp"

#include <vector>
#include <array>

#include <Windows.h>

namespace AMB
{
    namespace Graphics
    {
        struct Image
        {
            size_t w{ 0 }, h{ 0 };
            std::vector<Rgba> pixels;

            Rgba& pixel(size_t x, size_t y)
            {
                return pixels[x + (h - 1 - y)*w];
            }

            const Rgba& cpixel(size_t x, size_t y) const
            {
                return pixels[x + (h - 1 - y)*w];
            }

            bool operator==(const Image& other) const
            {
                return w == other.w && h == other.h && pixels == other.pixels;
            }

            template <size_t N>
            bool operator==(const std::array<Rgba, N> &pixelsArray)
            {
                return N == pixels.size() &&
                    std::memcmp(pixels.data(), pixelsArray.data(), N * sizeof(Rgba)) == 0;
            }

            void resize()
            {
                pixels.resize(w*h);
            }

            void* pixelsPtr()
            {
                return &pixels[0];
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
                    ::MessageBox(NULL, "Could not load the desired image image", "Error", MB_OK);
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

            Image getSprite(size_t reqx, size_t reqy, size_t reqw, size_t reqh) const
            {
                Image img;

                img.w = reqw;
                img.h = reqh;

                img.pixels.reserve(reqw*reqh);

                auto it = img.pixels.begin();
                for (size_t y = reqy + reqh - 1; y >= reqy; --y)
                    for (size_t x = reqx; x < reqx + reqw; ++x)
                        img.pixels.emplace_back(cpixel(x, y));

                return img;
            }
        };
    }
}
