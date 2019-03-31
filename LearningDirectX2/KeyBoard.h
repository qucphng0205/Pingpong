#pragma once
#include <queue>
class KeyEvent {
public:
	enum EventType {
		Press,
		Release,
		NULLKey
	};
	KeyEvent(EventType type, unsigned char keyCode);
	unsigned char GetKeyCode();
	bool IsPress();
	bool IsRelease();
private:
	unsigned char keyCode;
	EventType type;
};

class KeyBoard {
private:
	static KeyBoard *instance;
	std::queue<KeyEvent> keyBuffer;
	bool keyState[256];
public:
	static KeyBoard *GetInstance();
	void OnKeyPress(unsigned char keyCode);
	void OnKeyRelease(unsigned char keyCode);
	//liec 
	KeyEvent peekKey();
	KeyEvent readKey();
	bool isPress(unsigned char keyCode);
	void flushBuffer();
	bool isEmpty();
};