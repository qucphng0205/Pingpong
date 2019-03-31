#include "KeyBoard.h"

KeyBoard *KeyBoard::instance = NULL;

KeyEvent::KeyEvent(EventType type, unsigned char keyCode) : type(type), keyCode(keyCode){	
}

unsigned char KeyEvent::GetKeyCode() {
	return keyCode;
}

bool KeyEvent::IsPress() {
	return type == Press;
}

bool KeyEvent::IsRelease() {
	return type == Release;
}

KeyBoard * KeyBoard::GetInstance() {
	if (instance == NULL)
		instance = new KeyBoard();
	return instance;
}

void KeyBoard::OnKeyPress(unsigned char keyCode) {
	if (!keyState[keyCode]) {
		keyState[keyCode] = true;
		keyBuffer.push(KeyEvent(KeyEvent::Press, keyCode));
	}
}

void KeyBoard::OnKeyRelease(unsigned char keyCode) {
	if (keyState[keyCode]) {
		keyState[keyCode] = false;
		keyBuffer.push(KeyEvent(KeyEvent::Release, keyCode));
	}
}

KeyEvent KeyBoard::peekKey() {
	if (keyBuffer.size() > 0)
		return keyBuffer.front();
	else
		return KeyEvent(KeyEvent::NULLKey, 0);
}

KeyEvent KeyBoard::readKey() {
	if (keyBuffer.size() > 0) {
		KeyEvent e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
	else
		return KeyEvent(KeyEvent::NULLKey, 0);
}
bool KeyBoard::isPress(unsigned char keyCode) {
	return keyState[keyCode];
}
void KeyBoard::flushBuffer() {
	while (!keyBuffer.empty()) {
		keyBuffer.pop();
	}
}
bool KeyBoard::isEmpty() {
	return keyBuffer.empty();
}
