#include "client/reader/TibiaClientMemoryReader.hpp"
#include "memory/Addresses.hpp"

#include <cstdint>

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            TibiaClientMemoryReader::TibiaClientMemoryReader(DWORD pid)
                : processMemoryReader{ pid }
            {}

            void TibiaClientMemoryReader::attachToNewProcess(DWORD pid)
            {
                processMemoryReader.attachNewProcess(pid);
            }

            size_t TibiaClientMemoryReader::readCap()
            {
                const auto xor = processMemoryReader.read<uint32_t>(Memory::Addresses::kXor);
                const auto cap = processMemoryReader.read<uint32_t>(Memory::Addresses::kCap);

                return (xor ^ cap) / 100;
            }
        }
    }
}
