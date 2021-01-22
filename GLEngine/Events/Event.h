#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

struct MouseMovedEvent
{
	using Func = std::function<void(double, double)>;

	inline static void OnEvent(double xpos, double ypos) 
	{
		for (auto&& f : funcs)
		{
			f(xpos, ypos);
		}
	}

	inline static void subscribe(Func f)
	{
		funcs.push_back(f);
	}


private:
	inline static std::vector<Func> funcs;
};


struct MouseScolledEvent
{
	using Func = std::function<void(double, double)>;

	inline static void OnEvent(double xpos, double ypos)
	{
		for (auto&& f : funcs)
		{
			f(xpos, ypos);
		}
	}

	inline static void subscribe(Func f)
	{
		funcs.push_back(f);
	}

private:
	inline static std::vector<Func> funcs;
};