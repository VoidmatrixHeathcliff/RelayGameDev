#pragma once

#include <Windows.h>
#include <ctime>
#include <thread>
#include <conio.h>
#include <mutex>
#include <string>
#include <vector>

//#pragma comment(lib, "winmm.lib")

namespace NotPiano
{
	class PianoNote
	{
		friend class PianoChord;
		friend class Piano;

	public:

		enum Scale
		{
			Rest = 0,
			C8 = 108,
			B7 = 107, A7s = 106, A7 = 105, G7s = 104, G7 = 103, F7s = 102, F7 = 101, E7 = 100, D7s = 99, D7 = 98, C7s = 97, C7 = 96,
			B6 =  95, A6s =  94, A6 =  93, G6s =  92, G6 =  91, F6s =  90, F6 =  89, E6 =  88, D6s = 87, D6 = 86, C6s = 85, C6 = 84,
			B5 =  83, A5s =  82, A5 =  81, G5s =  80, G5 =  79, F5s =  78, F5 =  77, E5 =  76, D5s = 75, D5 = 74, C5s = 73, C5 = 72,
			B4 =  71, A4s =  70, A4 =  69, G4s =  68, G4 =  67, F4s =  66, F4 =  65, E4 =  64, D4s = 63, D4 = 62, C4s = 61, C4 = 60,
			B3 =  59, A3s =  58, A3 =  57, G3s =  56, G3 =  55, F3s =  54, F3 =  53, E3 =  52, D3s = 51, D3 = 50, C3s = 49, C3 = 48,
			B2 =  47, A2s =  46, A2 =  45, G2s =  44, G2 =  43, F2s =  42, F2 =  41, E2 =  40, D2s = 39, D2 = 38, C2s = 37, C2 = 36,
			B1 =  35, A1s =  34, A1 =  33, G1s =  32, G1 =  31, F1s =  30, F1 =  29, E1 =  28, D1s = 27, D1 = 26, C1s = 25, C1 = 24,
			B0 =  23, A0s =  22, A0 =  21
		};

		constexpr static const int C_Scale[2][7][7] =
		{
			{
				{C1,D1,E1,F1,G1,A1,B1},
				{C2,D2,E2,F2,G2,A2,B2},
				{C3,D3,E3,F3,G3,A3,B3},
				{C4,D4,E4,F4,G4,A4,B4}, //
				{C5,D5,E5,F5,G5,A5,B5},
				{C6,D6,E6,F6,G6,A6,B6},
				{C7,D7,E7,F7,G7,A7,B7}
			},
			{
				{C1s,D1s,-1,F1s,G1s,A1s,-1},
				{C2s,D2s,-1,F2s,G2s,A2s,-1},
				{C3s,D3s,-1,F3s,G3s,A3s,-1},
				{C4s,D4s,-1,F4s,G4s,A4s,-1},
				{C5s,D5s,-1,F5s,G5s,A5s,-1},
				{C6s,D6s,-1,F6s,G6s,A6s,-1},
				{C7s,D7s,-1,F7s,G7s,A7s,-1}
			}
		};

	public:

		virtual ~PianoNote() { }
		virtual void to_midi(HMIDIOUT handle, int volume);

	private:

		short note = 0;
		int level = 3;
		bool is_sharp = false;

	protected:

		int duration = 32 * 21;
	};

	class PianoChord : public PianoNote, public std::vector<PianoNote*>
	{
		friend class Piano;

	public:

		virtual ~PianoChord();
		virtual void to_midi(HMIDIOUT handle, int volume);
	};

	class Piano
	{
	public:

	public:

		Piano();
		~Piano();

	public:
		// Become a composer !
		static std::vector<PianoNote*> compose(const std::string& str);
		static void clearSheet(std::vector<PianoNote*>& sheet);
		void play(std::vector<PianoNote*>& sheet, int quarter_note_delay = 500, int volume = 0x7f);
		/*
		Allow you to play single note without load a sheet.
			note : [0, 7],
			level : [0, 6],
			is_sharp : { false, true },
			delay :  > 0
			volume : [0, 127]
		*/ 
		void play(unsigned char note, unsigned char level = 3, bool is_sharp = false, int delay = 500, int volume = 0x7f);
		bool loop(bool value);
		bool end();
		void stop();

	private:

		static size_t translate(std::string str, size_t index, PianoNote*& note);
		void thread_play(std::vector<PianoNote*> sheet, int delay, int volume);

	private:

		static bool initialized;
		static HMIDIOUT handle;

		bool playing = false;
		bool is_loop = false;
		
		std::mutex guard;
	};
}