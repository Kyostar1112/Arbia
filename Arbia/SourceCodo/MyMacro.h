#ifndef _MY_MACRO_H_	//繧､繝ｳ繧ｯ繝ｫ繝ｼ繝峨ぎ繝ｼ繝.
#define _MY_MACRO_H_


//============================================================
//	繝槭け繝ｭ.
//============================================================

//繧ｨ繝ｩ繝ｼ繝｡繝�そ繝ｼ繧ｸ.
#define ERR_MSG(str,title)	{MessageBox(NULL,str,title,MB_OK);}

//解放.
#define SAFE_RELEASE(x)		{ if(x) {(x)->Release();(x)=nullptr; } }
#define SAFE_DELETE(p)		{ if(p) { delete (p);   (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p){ if(p) { delete[] (p); (p)=nullptr; } }

#define SAFE_RELEASE(x)		{ if(x) {(x)->Release();(x)=nullptr; } }
#define SAFE_DELETE(p)		{ if(p) { delete (p);   (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p){ if(p) { delete[] (p); (p)=nullptr; } }

//繧ｭ繝ｼ繝懊�繝牙�蜉.
//謚ｼ縺励※縺�ｋ髢.
#define GETKEY_STAY(x) if (GetAsyncKeyState(x) & 0x8000)	
//謚ｼ縺励◆縺ｨ縺阪□縺.
#define GETKEY_DOWN(x) if (GetAsyncKeyState(x) & 0x0001)

#endif//#ifndef _MY_MACRO_H_