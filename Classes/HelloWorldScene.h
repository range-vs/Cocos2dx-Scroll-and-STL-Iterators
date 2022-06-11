#pragma once

#include "cocos2d.h"
#include <ui/UIScrollView.h>

#include "CustomVector.h"

class HelloWorld : public cocos2d::Layer, std::basic_streambuf<char, std::char_traits<char>>
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();

    auto createVector()->custom_std::CustomVector<int>;
    void createConsole()const;


    CREATE_FUNC(HelloWorld);

    cocos2d::ui::ScrollView* getScrollView();
    auto getCurrentHeightScrollView()->std::size_t&;

private:
    cocos2d::ui::ScrollView* scrollView{ nullptr };
    std::size_t currentWidthScrollView{ 10 };
    std::size_t currentHeightScrollView{ 0 };
};

class HelloWorldOstream
{
public:
    HelloWorldOstream(HelloWorld* hw);
    HelloWorldOstream& operator<<(int val);
    HelloWorldOstream& operator<<(std::string& val);
    HelloWorldOstream& operator<<(char val);
    HelloWorldOstream& operator<<(char* val);

    template <class T>
    void createLabel(T& val)
    {
        auto label = cocos2d::Label::createWithTTF(std::to_string(val), "fonts/Marker Felt.ttf", 35);
        _createLabel(label);
    }
    template <class T>
    void createLabel(T*& val)
    {
        auto label = cocos2d::Label::createWithTTF(std::to_string(*val), "fonts/Marker Felt.ttf", 35);
        _createLabel(label);
    }

private:
    void _createLabel(cocos2d::Label* label);
private:
    HelloWorld* hw{nullptr};
};

template <>
inline void HelloWorldOstream::createLabel(char& val)
{
	auto label = cocos2d::Label::createWithTTF(std::string(1, val), "fonts/Marker Felt.ttf", 35);
	_createLabel(label);
}
template <>
inline void HelloWorldOstream::createLabel(std::string& val)
{
	auto label = cocos2d::Label::createWithTTF(val, "fonts/Marker Felt.ttf", 35);
	_createLabel(label);
}
template <>
inline void HelloWorldOstream::createLabel(char*& val)
{
	auto label = cocos2d::Label::createWithTTF(val, "fonts/Marker Felt.ttf", 35);
	_createLabel(label);
}
template <>
inline void HelloWorldOstream::createLabel(const char*& val)
{
	auto label = cocos2d::Label::createWithTTF(val, "fonts/Marker Felt.ttf", 35);
	_createLabel(label);
}


template <class T, class CharT = char,
    class Traits = std::char_traits<CharT> >
class HelloWorldOstreamIterator
{
public: // usings
    using value_type = void;
    using difference_type = std::ptrdiff_t;
    using reference = void;
    using pointer = void;
    using iterator_category = std::output_iterator_tag;
    using char_type = CharT;
    using traits_type = Traits;
    using ostream_type = HelloWorldOstream;

public: // methods
    HelloWorldOstreamIterator() :_ptr(nullptr), _delim(nullptr)
    {

    }
    HelloWorldOstreamIterator(ostream_type& vtp, char_type* delim = nullptr) :_ptr(std::addressof(vtp)), _delim(delim)
    {

    }
    HelloWorldOstreamIterator& operator=(const T& value)
    {
        *_ptr << value;
        if (_delim != 0)
            *_ptr << _delim;
        return *this;
    }
    HelloWorldOstreamIterator& operator* ()
    {
        return *this;
    }
    HelloWorldOstreamIterator& operator++()
    {
        return *this;
    }
    HelloWorldOstreamIterator& operator++(int)
    {
        return *this;
    }

private: // members
    ostream_type* _ptr;
    char_type* _delim;
};
