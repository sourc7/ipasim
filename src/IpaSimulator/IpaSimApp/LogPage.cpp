#include "pch.h"

#include "LogPage.h"
#if __has_include("LogPage.g.cpp")
#include "LogPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::IpaSimApp::implementation {

LogPage::LogPage() { InitializeComponent(); }

void LogPage::Log(const hstring &) {}

} // namespace winrt::IpaSimApp::implementation