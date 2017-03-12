#pragma once

#include <Windows.h>
#include <Psapi.h>

#include <random>
#include <mutex>
#include <fstream>

#include <QLineEdit>

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Utils
    {
        struct RandomBetween
        {
            size_t min, max;

            size_t get() const;
        };

        struct Pos
        {
            int x, y;
        };

        struct Rect
        {
            int x, y;
            size_t w, h;
        };

        void closeAndNullHandle(HANDLE &handle);

        void safeCloseAndNullHandle(HANDLE &handle);

        DWORD getModuleBase(DWORD pid, const char *sModuleName);

        template <typename T>
        auto getFromToFromEdits(const T &fromToEdits)
        {
            return FromTo{
                fromToEdits.from->text().toInt(),
                fromToEdits.to->text().toInt()
            };
        }

        std::string readWholeFileIntoString(const std::string &path);
        std::string wstringToString(const std::wstring &wstr);
        std::wstring stringToWstring(const std::string &str);
        std::string imageToSimpleString(const Graphics::Image& img);
    }
}
