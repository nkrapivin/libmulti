#include "stdafx.h"
#include "MultiD2D.h"

#define SafeRelease(_Interface) if (*(_Interface) != nullptr) { (*(_Interface))->Release(); (*(_Interface)) = nullptr; }

CRITICAL_SECTION ms_FactoryMutex{ 0 };
ID2D1Factory* ms_Factory{ nullptr };

void EnterFactory(void) { EnterCriticalSection(&ms_FactoryMutex); }
void LeaveFactory(void) { LeaveCriticalSection(&ms_FactoryMutex); }

void InitMultiD2D(void) {
	InitializeCriticalSection(&ms_FactoryMutex);
	EnterFactory();
	D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &ms_Factory);
	LeaveFactory();

	printf(__FUNCTION__ ": hello!\n");
	fflush(stdout);
}

CMultiD2D::CMultiD2D() : m_bitmap(nullptr), m_rt(nullptr), m_bitmapW(0), m_bitmapH(0), m_bitmapP(nullptr), m_mutex(new CRITICAL_SECTION()) {
	InitializeCriticalSection(this->m_mutex);
}

CMultiD2D::~CMultiD2D() {
	this->Discard();

	this->enter();
	this->m_bitmapP = nullptr;
	this->m_bitmapW = 0;
	this->m_bitmapH = 0;
	this->leave();

	DeleteCriticalSection(this->m_mutex);
	delete this->m_mutex;
	this->m_mutex = nullptr;
}

void CMultiD2D::enter(void) { EnterCriticalSection(this->m_mutex); }
void CMultiD2D::leave(void) { LeaveCriticalSection(this->m_mutex); }

void CMultiD2D::Discard(void) {
	this->enter();
	SafeRelease(&this->m_bitmap);
	SafeRelease(&this->m_rt);
	this->leave();
}

HRESULT CMultiD2D::Create(HWND window) {
	HRESULT hR = S_OK;
	FLOAT dpiX = 0.0f, dpiY = 0.0f;

	this->enter();
	
	EnterFactory();
	if (this->m_rt == nullptr) {
		RECT rc;
		GetClientRect(window, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
		hR = ms_Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(window, size), &this->m_rt);
	}
	ms_Factory->GetDesktopDpi(&dpiX, &dpiY);
	LeaveFactory();

	if (SUCCEEDED(hR) && this->m_bitmapP != nullptr && this->m_bitmap == nullptr) {
		D2D1_SIZE_U bmsize = D2D1::SizeU(this->m_bitmapW, this->m_bitmapH);
		D2D1_BITMAP_PROPERTIES props;
		props.dpiX = dpiX;
		props.dpiY = dpiY;
		props.pixelFormat.alphaMode = D2D1_ALPHA_MODE::D2D1_ALPHA_MODE_IGNORE;
		props.pixelFormat.format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
		hR = this->m_rt->CreateBitmap(bmsize, this->m_bitmapP, this->m_bitmapW * 4, props, &this->m_bitmap);
	}

	this->leave();
	return hR;
}

HRESULT CMultiD2D::OnResize(UINT w, UINT h) {
	HRESULT hR = S_OK;

	this->enter();
	if (this->m_rt != nullptr) {
		hR = this->m_rt->Resize(D2D1::SizeU(w, h));
		if (SUCCEEDED(hR)) {
			//printf("OnResize ok. w=%ud,h=%ud\r\n", w, h);
		}
	}
	this->leave();

	return hR;
}

HRESULT CMultiD2D::OnRender(void) {
	HRESULT hR = S_OK;
	this->enter();

	if (this->m_rt != nullptr && this->m_bitmap != nullptr) {
		this->m_rt->BeginDraw();
		this->m_rt->SetTransform(D2D1::Matrix3x2F::Identity());
		this->m_rt->Clear(D2D1::ColorF(D2D1::ColorF::Black));

		// source rectangle, always occupy the whole bitmap, always.
		D2D1_SIZE_F bmsiz = this->m_bitmap->GetSize();
		D2D1_RECT_F source = D2D1::RectF(0.0f, 0.0f, bmsiz.width, bmsiz.height);

		// change this:
		// right now it's just drawing bitmap in the center.
		D2D1_SIZE_F rtsiz = this->m_rt->GetSize();
		D2D1_RECT_F dest = D2D1::RectF(
			rtsiz.width / 2 - source.right / 2,
			rtsiz.height / 2 - source.bottom / 2,
			rtsiz.width / 2 + source.right / 2,
			rtsiz.height / 2 + source.bottom / 2
		);

		this->m_rt->DrawBitmap(this->m_bitmap, dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, source);
		hR = this->m_rt->EndDraw();
	}

	this->leave();

	if (hR == D2DERR_RECREATE_TARGET) {
		hR = S_OK; // that's what MSDN docs tell me to do.
		this->Discard();
	}

	return hR;
}

HRESULT CMultiD2D::SetBitmap(UINT w, UINT h, void* data) {
	this->enter();
	this->m_bitmapW = w;
	this->m_bitmapH = h;
	this->m_bitmapP = data;
	this->leave();
	this->Discard();
	return S_OK;
}
