#include "../../include/notPiano/notPiano.h"

using namespace std;
using namespace NotPiano;

bool Piano::initialized = false;
HMIDIOUT NotPiano::Piano::handle;

void NotPiano::PianoNote::to_midi(HMIDIOUT handle, int volume)
{
	if (note)
		midiOutShortMsg(handle,
			0x90 | (volume << 16) | (C_Scale[is_sharp][level][note-1] << 8));
}

NotPiano::PianoChord::~PianoChord()
{
	for (size_t i = 0; i < this->size(); i++)
	{
		delete this->operator[](i);
	}
}

void NotPiano::PianoChord::to_midi(HMIDIOUT handle, int volume)
{
	for (size_t i = 0; i < this->size(); i++)
	{
		this->operator[](i)->to_midi(handle, volume);
	}
}

NotPiano::Piano::Piano()
{
	if(!initialized)
		midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);

	initialized = true;
}

NotPiano::Piano::~Piano()
{
	midiOutClose(handle);
	initialized = false;
}

std::vector<PianoNote*> NotPiano::Piano::compose(const std::string& str)
{
	std::vector<PianoNote*> notes;
	notes.clear();

	for (size_t i = 0; i < str.size(); i++)
	{
		PianoNote* ptr;

		if (str[i] == ' ')
			continue;

		i += translate(str, i, ptr);
		notes.push_back(ptr);
	}
	return notes;
}

void NotPiano::Piano::clearSheet(std::vector<PianoNote*>& sheet)
{
	for (size_t i = 0; i < sheet.size(); i++)
		delete sheet[i];
	sheet.clear();
}

void NotPiano::Piano::play(vector<PianoNote*>& sheet, int quarter_note_delay, int volume)
{
	if (!playing)
	{
		playing = true;
		std::thread tune(&Piano::thread_play, this, sheet, quarter_note_delay, volume);
		tune.detach();
	}
}

void NotPiano::Piano::play(unsigned char note, unsigned char level, bool is_sharp, int delay, int volume)
{
	if(0 < note && note <= 7)
		midiOutShortMsg(handle, 0x90 | (volume << 16) | (PianoNote::C_Scale[is_sharp][level][note-1] << 8));
}

bool NotPiano::Piano::loop(bool value)
{
	return is_loop = value;
}

bool NotPiano::Piano::end()
{
	return !playing;
}

void NotPiano::Piano::stop()
{
	playing = false;
	midiOutShortMsg(handle, 0x90);
}

size_t NotPiano::Piano::translate(std::string str, size_t index, PianoNote*& note)
{
	str.push_back(' ');
	size_t s;
	for (s = index; s < str.size(); s++)
	{
		switch (str[s])
		{
		case '[':
		case '{':
		{
			note = new PianoChord();

			for (s += 1; s < str.size(); s++)
			{
				if (str[s] == ']' || str[s] == '}')
					goto Return;
				if (str[s] == ' ')
					continue;

				PianoNote* pnote;
				s += translate(str, s, pnote);
				if (pnote->duration > note->duration)
					note->duration = pnote->duration;
				((PianoChord*)note)->push_back(pnote);
				if (str[s] == ']' || str[s] == '}')
					goto Return;
			}
		} break;

		case ' ':
		case '|':
			continue;

		default:
		{
			note = new PianoNote();

			note->note = str[s] - '0';
			if (note->note > 7)
			{
				throw std::logic_error("fail to read note or chord");
			}

			for (size_t i = s + 1; i < str.size(); i++, s++)
			{
				switch (str[i])
				{
				case '_': note->duration /= 2; break;
				case '*': note->duration /= 3; break;
				case '&': note->duration /= 7; break;
				case '%': note->duration /= 5; break;
				case '.': note->duration *= 1.5; break;

				case '-': note->duration += 32 * 21; break;

				case '^': note->level++; break;
				case ',': note->level--; break;
				case '#': note->is_sharp = true; break;

				default:
					goto Return;
				}
			}
		} break;
		}
	}

Return:
	return s - index + 1;
}

void NotPiano::Piano::thread_play(vector<PianoNote*> notes, int delay, int volume)
{
	LOOP:

	int tick = 0;
	size_t idx = 0;
	int time_start = clock();
	while (idx < notes.size() && playing)
	{
		notes[idx]->to_midi(handle, volume);
		while (playing && (clock() - time_start) * 1000.0 / CLOCKS_PER_SEC < delay / 32.0 / 21 * (tick + notes[idx]->duration));
		tick += notes[idx++]->duration;
	}

	if (playing && is_loop)
		goto LOOP;

	QUIT:

	guard.lock();
	midiOutShortMsg(handle, 0x80);
	playing = false;
	guard.unlock();
}
