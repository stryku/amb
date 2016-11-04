#pragma once

#include <utils/ToString.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <string>

namespace AMB
{
    namespace Utils
    {
        template <typename T = std::string>
        struct PtreeElement
        {
            PtreeElement() = default;
            PtreeElement(const std::string &path, const T &value)
                : path(path)
                , value(value)
            {}

            std::string path;
            T value;
        };

        class PropertyTreeBuilder
        {
        public:
            template <typename T>
            PropertyTreeBuilder& addElement(const PtreeElement<T> &elem)
            {
                tree.put(elem.path, utils::toString(elem.value));
                return *this;
            }

            template <typename Container>
            PropertyTreeBuilder& addElements(const Container &elements)
            {
                for (const auto &element : elements)
                    addElement(element);

                return *this;
            }

            std::string build() const
            {
                std::ostringstream oss;
                boost::property_tree::write_xml(oss, tree);
                return oss.str();
            }

        private:
            boost::property_tree::ptree tree;
        };
    }
}
