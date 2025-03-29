// i felt like doing this because it was funny to me
#pragma once
#include <Geode/Geode.hpp>

#include <exception>
#include <string>

namespace NodeDataAPI {

    class MissingImplementationException : public std::exception {
    private:
        std::string m_unimplementedFunction;

    public:
        MissingImplementationException(std::string unimplementedFunction) : m_unimplementedFunction(unimplementedFunction) {
	        log::error("unimplemented function called! function is: {}", unimplementedFunction);
        }

        std::string what() const throw() { 
            return fmt::format("Implementation for {} missing! Please notify the developer of the mod.\n"
            "Note for developers of mods depending on Node Data API - please check what functions\n"
            "are implemented and which are not before you use any of them.\n", m_unimplementedFunction);
        }
    
    };

}
