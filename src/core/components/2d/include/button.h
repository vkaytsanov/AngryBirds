#pragma once
#include <functional>

typedef std::function<void()> ClickListener;

struct Button {
	ClickListener clickListener;
};
