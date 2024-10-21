/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** DlLoader
*/

#pragma once

#include <dlfcn.h>
#include <string>

namespace ecs {
    template <typename T, typename... Args>
    class DlLoader {
      public:
        class DlLoaderException : public std::exception {
          public:
            DlLoaderException(std::string const &message) : _message(message) {}

            const char *what() const noexcept override
            {
                return _message.c_str();
            }

          private:
            std::string _message;
        };

        DlLoader() {}

        DlLoader(std::string path, std::string entryPoint)
        {
            __handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!__handle)
                throw DlLoaderException(dlerror());
            _f = (T(*)(Args && ...)) dlsym(__handle, entryPoint.c_str());
            if (!_f)
                throw DlLoaderException(dlerror());
            name = path;
        }

        void call(Args &&...args)
        {
            if (!_f)
                throw DlLoaderException("Missing handle");
            _f(std::forward<Args>(args)...);
        }

        ~DlLoader()
        {
            if (__handle)
                dlclose(__handle);
        }

      protected:
      private:
        std::string name = "";
        void *__handle = nullptr;
        T (*_f)(Args...) = nullptr;
    };
} // namespace ecs
