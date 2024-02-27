#pragma once
#include <SFML/Graphics.hpp>


class Math
{
public:

	static constexpr float Pi = 3.1415926535f;
	static constexpr float Half = 0.5f;
	static constexpr float RadianConversionConstant = 180.0f;

	template<typename T>
	static T LengthSq(const sf::Vector2<T>& v)
	{
		return static_cast<T>((v.x * v.x) + (v.y * v.y));
	}

	template<typename T>
	static T Length(const sf::Vector2<T>& v)
	{
		return sqrt(LengthSq(v));
	}

	template<typename T>
	static sf::Vector2<T> Normalised(const sf::Vector2<T>& v)
	{
		const float len = Length(v);
		return sf::Vector2<T>(v.x / len, v.y / len);
	}

	static constexpr float RadiansToDegrees(float rad) { return rad * (RadianConversionConstant / Pi); }

	static constexpr float DegreesToRadians(float deg) { return deg * (Pi / RadianConversionConstant); }

	template<typename T>
	static float ToRadians(const sf::Vector2<T>& v)
	{
		return atan2f(v.y, v.x);
	}

	template<typename T>
	static float ToDegrees(const sf::Vector2<T>& v)
	{
		return RadiansToDegrees(ToRadians(v));
	}

	template<typename T>
	static sf::Vector2<T> Rotate(const sf::Vector2<T>& v, float rads)
	{
		return sf::Vector2<T>(v.x * cos(rads) - v.y * sin(rads), v.x * sin(rads) + v.y * cos(rads));
	}

	static constexpr float ClampF(float val, float min, float max) { return std::min(max, std::max(val, min)); }

	template<typename T>
	static T Lerp(T from, T to, float val)
	{
		return static_cast<T>(from + ((to - from) * val));
	}

	static float FRand() { return (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)); }

	static int IRandRange(int min, int max) { return min + (std::rand() % ((max + 1) - min)); }

	static float FRandRange(float min, float max) { return Lerp(min, max, FRand()); }

	static sf::IntRect FToIRect(const sf::FloatRect& f)
	{
		return sf::IntRect(static_cast<int>(f.left), static_cast<int>(f.top), static_cast<int>(f.width), static_cast<int>(f.height));
	}
};