#pragma once

#include <graphics.h>
#include <functional>
#include <bitset>

namespace NotKeyBoard
{
	enum NotVK
	{
		N0 = 48, N1, N2, N3, N4, N5, N6, N7, N8, N9,
		A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
	};

	class KeyBoardControl
	{
	public:

		static KeyBoardControl* manager();
		static void quit();
		bool OnMessage(ExMessage& msg);
		bool isDown(NotVK vk);
		bool isUp(NotVK vk);

	private:

		KeyBoardControl();
		~KeyBoardControl();

	protected:

		std::bitset<32> isLetterKeyDown;
		std::bitset<32> isLetterKeyUp;
		std::bitset<16> isNumberKeyDown;
		std::bitset<16> isNumberKeyUp;

	private:

		static bool initialized;
		static KeyBoardControl* instance;
	};
}