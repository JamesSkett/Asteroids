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

	static float RadiansToDegrees(float rad) { return rad * (RadianConversionConstant / Pi); }

	static float DegreesToRadians(float deg) { return deg * (Pi / RadianConversionConstant); }

	template<typename T>
	static T Lerp(T from, T to, float val)
	{
		return static_cast<T>(from + ((to - from) * val));
	}

	static float FRand() { return (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)); }

	static int IRandRange(int min, int max) { return min + (std::rand() % ((max + 1) - min)); }

	static float FRandRange(float min, float max) { return Lerp(min, max, FRand()); }
};