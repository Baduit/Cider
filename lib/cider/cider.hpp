#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

namespace cider 
{

template <typename MF>
concept MemberFunction = std::is_member_function_pointer_v<MF>;

template <typename T, typename MF, typename... Args>
concept MemberFunctionArgs = 
	requires(T&& t, MF mf, Args&&... args)
	{
		(t.*mf(std::forward<Args...>(args)...));
	};


namespace helper
{

template <typename C, typename R, typename... Args>
struct DeduceClassTypeFromMemberFunction
{
	using Class = C;

	DeduceClassTypeFromMemberFunction(R (C::*)(Args...)){}
};

template <MemberFunction MF>
using ClassType = typename decltype(DeduceClassTypeFromMemberFunction(std::declval<MF>()))::Class;

} // namespace helper


template <MemberFunction MF>
class Wrapper
{
	public:
		Wrapper(MF member_function):
			_member_function(member_function)
		{}

		template <typename... Args>
		auto operator()(Args&&... args)
		{
			return [&]<typename T>(T&& t) { return (t.*_member_function)(std::forward<Args>(args)...); };
		}

	private:
		MF _member_function;
};

template <typename T, std::invocable<T> Proxy>
constexpr auto operator->*(T&& t, Proxy&& p)
{
	return p(std::forward<T>(t));
}

} // namespace cider 