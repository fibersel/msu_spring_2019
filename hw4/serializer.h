#pragma once
#include <type_traits>
#include <iostream>
#include <string>

enum class Error
{
    NoError,
    CorruptedArchive
};


template <typename T>
struct boolTraits
{
    static constexpr bool value = false;
};

template <>
struct boolTraits<bool>
{
    static constexpr bool value = true;
};


class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out): out_(out) {
    };

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    };

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return process(std::forward<ArgsT>(args)...);
    };

private:
    std::ostream& out_;

    template<class T>
    Error send_(T& val) {
        if (boolTraits<T>::value)
            out_ << (val == true ? "true" : "false") << Separator;
        else if(std::is_same<uint64_t, T>::value)
            out_ << val << Separator;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    };

    template <class T>
    Error process(T&& val) {
        if(send_(val) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        return Error::NoError;
    };

    template <class T, class... ArgsT>
    Error process(T&& val, ArgsT&&... args) {
        if(send_(val) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        return process(std::forward<ArgsT>(args)...);
    };
};


class Deserializer
{
public:
    explicit Deserializer(std::istream& in)
        : in_(in) {
    }

    template <class T>
    Error load(T& object) {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    std::istream& in_;

    template<class T>
    Error recieve_(T& val) {
        std::string text;
        in_ >> text;
        if (boolTraits<T>::value) {
            if(text == "true" || text == "false")
                val = (text == "true" ? true : false);
            else
                return Error::CorruptedArchive;
        } else if(std::is_same<uint64_t, T>::value) {
            if(text.rfind("-", 0) == 0)
                return Error::CorruptedArchive;
            else
            {
                std::istringstream iss(text);
                iss >> val;
            }
        } else
            return Error::CorruptedArchive;
        return Error::NoError;
    };

    template <class T>
    Error process(T&& val) {
        if(recieve_(val) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        return Error::NoError;
    };


    template <class T, class... ArgsT>
    Error process(T&& val, ArgsT&&... args) {
        if(recieve_(val) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        return process(std::forward<ArgsT>(args)...);
    };

};
