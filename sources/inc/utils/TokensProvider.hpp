#pragma once

namespace Amb
{
    namespace Utils
    {
        class TokensProvider
        {
        public:
            using Token = size_t;

            inline Token get()
            {
                return ++currentToken;
            }

        private:
            Token currentToken{ 0 };
        };
    }
}
