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
    template <typename T>
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

        DlLoader(std::string &path, std::string &entryPoint)
        {
            __handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!__handle)
                throw DlLoaderException(dlerror());
            _handle = (T(*)())dlsym(__handle, entryPoint.c_str());
            if (!_handle)
                throw DlLoaderException(dlerror());
        }

        template <typename... Args>
        void operator()(Args &&...args)
        {
            if (!_handle)
                throw DlLoaderException("Missing handle");
            _handle(std::forward<Args>(args)...);
        }

        ~DlLoader()
        {
            if (__handle)
                dlclose(__handle);
        }

      protected:
      private:
        void *__handle = nullptr;
        T (*_handle)();
    };
} // namespace ecs
