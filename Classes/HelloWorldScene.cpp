#include "HelloWorldScene.h"

#include <CCFileUtils.h>

#include <iostream>
#include <algorithm>
#include <numeric>
#include <sstream>

#ifdef _WIN32
#include <tchar.h>
#endif // _WIN32

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
    createConsole();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setContentSize(Size(visibleSize.width - 10, visibleSize.height - 10));
    scrollView->setInnerContainerSize(Size(visibleSize.width - 10, visibleSize.height * 12));
    scrollView->setBounceEnabled(true);
    scrollView->setAnchorPoint(cocos2d::Vec2(0, 1));
    scrollView->setPosition(cocos2d::Vec2(origin.x + 10,
        origin.y + visibleSize.height - 10));

    //Vec2 worldPosition = label->convertToWorldSpace(label->getPosition());
    auto label = Label::createWithTTF("Hello Cocos 2dx", "fonts/Marker Felt.ttf", 35);
    label->setAnchorPoint(cocos2d::Vec2(0, 1));
    currentHeightScrollView = scrollView->getInnerContainerSize().height - 20;
    label->setPosition(cocos2d::Vec2(currentWidthScrollView,
        currentHeightScrollView));
    currentHeightScrollView -= (label->getContentSize().height + 20);
    scrollView->addChild(label);

    HelloWorldOstream hwOstream(this);
    auto iter_console_int = custom_std::CustomOstreamIterator<int>(std::cout, ";");
    auto iter_console_char = custom_std::CustomOstreamIterator<char>(std::cout);
    auto iter_hello_world_int = HelloWorldOstreamIterator<int>(hwOstream, ";");
    auto iter_hello_world_char = HelloWorldOstreamIterator<char>(hwOstream);

    custom_std::CustomVector<int> vec;
    vec = createVector();

    std::transform(std::begin(vec), std::end(vec), std::begin(vec), [](auto& elem)
        {
            return elem * 2;
        }
    );
    std::copy(std::cbegin(vec), std::cend(vec), iter_console_int);
    std::istringstream iss1("\n\n\n");
    std::copy(custom_std::CustomIstreamIterator<char, true>(iss1), custom_std::CustomIstreamIterator<char, true>(), iter_console_char);
    std::copy(std::cbegin(vec), std::cend(vec), iter_hello_world_int);
    std::istringstream iss2("\n\n\n");
    std::copy(custom_std::CustomIstreamIterator<char, true>(iss2), custom_std::CustomIstreamIterator<char, true>(), iter_hello_world_char);

    std::for_each(std::next(std::begin(vec), 10), std::end(vec), [](auto& elem)
        {
            ++elem;
        }
    );
    std::copy(std::cbegin(vec), std::cend(vec), iter_console_int);
    std::istringstream iss3("\n\n\n");
    std::copy(custom_std::CustomIstreamIterator<char, true>(iss3), custom_std::CustomIstreamIterator<char, true>(), iter_console_char);
    std::copy(std::cbegin(vec), std::cend(vec), iter_hello_world_int);
    std::istringstream iss4("\n\n\n");
    std::copy(custom_std::CustomIstreamIterator<char, true>(iss4), custom_std::CustomIstreamIterator<char, true>(), iter_hello_world_char);

    auto sum = std::accumulate(std::cbegin(vec), std::cend(vec), 0);
    std::istringstream iss6("Sum elements: " + std::to_string(sum) + "\n");
    std::copy(custom_std::CustomIstreamIterator<char, true>(iss6), custom_std::CustomIstreamIterator<char, true>(), iter_console_char);
    std::istringstream iss7("Sum elements: " + std::to_string(sum) + "\n");
    std::copy(custom_std::CustomIstreamIterator<char, true>(iss7), custom_std::CustomIstreamIterator<char, true>(), iter_hello_world_char);

    auto dist = std::distance(std::cbegin(vec), std::next(std::cbegin(vec), 10));
    std::istringstream iss8("Iterator distance: " + std::to_string(dist) + "\n");
    std::copy(custom_std::CustomIstreamIterator<char, true>(iss8), custom_std::CustomIstreamIterator<char, true>(), iter_console_char);
    std::istringstream iss9("Iterator distance: " + std::to_string(dist) + "\n");
    std::copy(custom_std::CustomIstreamIterator<char, true>(iss9), custom_std::CustomIstreamIterator<char, true>(), iter_hello_world_char);

    this->addChild(scrollView, 1);

    return true;
}

custom_std::CustomVector<int> HelloWorld::createVector()
{
    custom_std::CustomVector<int> vec; // {11, 58, 6, 111, 55};
    /*vec.push_back(5);
    vec.emplace_back(11);
    for(auto i = 0; i < 30; ++i)
        vec.push_back(i);
    for (auto&& it : vec)
        std::cout << it << std::endl;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
        std::cout << *it << std::endl;*/
    auto data = FileUtils::getInstance()->getDataFromFile("file.txt");
    if (data.isNull())
    {
        std::cerr << "error load file" << std::endl;
        return vec;
    }
    std::istringstream iss(std::string(data.getBytes(), data.getBytes() + data.getSize()));
    std::copy(custom_std::CustomIstreamIterator<int>(iss),
        custom_std::CustomIstreamIterator<int>(), custom_std::CustomBackInserter(vec));

    return vec;
}

void HelloWorld::createConsole()const
{
#ifdef _WIN32
    if (!AllocConsole())
    {
        // Add some error handling here.
        // You can call GetLastError() to get more info about the error.
        return;
    }

    // std::cout, std::clog, std::cerr, std::cin
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    // std::wcout, std::wclog, std::wcerr, std::wcin
    HANDLE hConOut = CreateFile(_T("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hConIn = CreateFile(_T("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
    SetStdHandle(STD_ERROR_HANDLE, hConOut);
    SetStdHandle(STD_INPUT_HANDLE, hConIn);
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();
#endif // _WIN32
}

ui::ScrollView* HelloWorld::getScrollView()
{
    return scrollView;
}

auto HelloWorld::getCurrentHeightScrollView() -> std::size_t&
{
    return currentHeightScrollView;
}

HelloWorldOstream::HelloWorldOstream(HelloWorld* hw): hw(hw)
{
}

HelloWorldOstream& HelloWorldOstream::operator<<(int val)
{
    createLabel(val);

    return *this;
}

HelloWorldOstream& HelloWorldOstream::operator<<(std::string& val)
{
    createLabel(val);

    return *this;
}

HelloWorldOstream& HelloWorldOstream::operator<<(char val)
{
    const char* _empty = "";
    if (val == '\n')
        createLabel(_empty);
    else
        createLabel(val);

    return *this;
}

HelloWorldOstream& HelloWorldOstream::operator<<(char* val)
{
    createLabel(val);

    return *this;
}

void HelloWorldOstream::_createLabel(cocos2d::Label * label)
{
    label->setAnchorPoint(cocos2d::Vec2(0, 1));
    label->setPosition(cocos2d::Vec2(10,
        hw->getCurrentHeightScrollView()));
    hw->getCurrentHeightScrollView() -= (label->getContentSize().height + 20);
    hw->getScrollView()->addChild(label);
}
