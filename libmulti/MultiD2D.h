#pragma once
#include "stdafx.h"

void InitMultiD2D(); // Initializes the factory, must be called once.

class CMultiD2D {
private:
	ID2D1HwndRenderTarget* m_rt;
	ID2D1Bitmap* m_bitmap;
	CRITICAL_SECTION* m_mutex;

	// user defined bitmap they wish to use
	// separately because D2D may want us to Release and Create an ID2D1Bitmap again
	UINT m_bitmapW;
	UINT m_bitmapH;
	void* m_bitmapP;

	// mutex stuff
	void enter();
	void leave();
	HRESULT createfromfile();
public:

	CMultiD2D();
	~CMultiD2D();

	HRESULT Create(HWND window);
	void Discard(); // Releases all resources EXCEPT for the user defined bitmap.
	HRESULT OnResize(UINT w, UINT h);
	HRESULT OnRender();
	HRESULT SetBitmap(UINT w, UINT h, void* data);
	void SetBitmapFromFile(LPCWSTR filename);
};
