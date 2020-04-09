#pragma once

enum class KeyState
{
	Pressed,
	Released
};

enum class KeyCode
{
	_1, _2, _3, _4, _5, _6, _7, _8, _9, _0,
	A, B, C, D, E, F, G, H, I, J, K, L, M,
	N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	Tab,
	CapsLock,
	Enter,
	LeftShift,
	RightShift,
	LeftAlt,
	RightAlt,
	LeftCtrl,
	RightCtrl,
	Space,
	UpArrow,
	LeftArrow,
	RightArrow,
	DownArrow
};

class InputManager
{
public:
	virtual ~InputManager() = default;
	virtual KeyState GetKeyState(KeyCode keyCode) = 0;
};