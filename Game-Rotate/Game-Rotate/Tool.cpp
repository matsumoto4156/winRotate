#include "Tool.h"
#include "Make.h"
#include "SceneManager.h"


Tool::Tool(Make* make, int objectnum) :
	mMake(make),
	mObjectNumber(objectnum),
	mTextWidth(0),
	mTextHeight(0),
	mTexture(0),
	mOnTexture(0),
	mFilenames(0)
{
	Initialize();
}
Tool::~Tool() {
	SDL_DestroyTexture(mTexture);
	SDL_DestroyTexture(mOnTexture);
	delete[] mMake;
	delete[] mFilenames;
	mTexture = 0;
	mOnTexture = 0;
	mMake = 0;
	mFilenames = 0;
}
	// ˆÊ’u‚ðŒˆ‚ß‚é
void Tool::SetPosition(float x, float y) {
	if (mTextWidth == 0) {
		SDL_Log("Error Please Set Size!");
		return;
	}
	mPosition = { x, y };
	mLeftTop = mPosition - vector2{ static_cast<float>(mTextWidth / 2), static_cast<float>(mTextHeight / 2) };
	mRightDown = mPosition + vector2{ static_cast<float>(mTextWidth / 2), static_cast<float>(mTextHeight / 2) };
}

// ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚Ä‚¢‚é‚©
bool Tool::IsButton(int x, int y) {
	bool no = x < mLeftTop.x ||
		y < mLeftTop.y ||
		mRightDown.x < x ||
		mRightDown.y < y;

	if (!no) {
		mOnThis = true;
	}
	return !no;
}

// •`ŽÊ
void Tool::Draw(SDL_Renderer* renderer) {
	SDL_Rect back = { static_cast<int>(mLeftTop.x) - 4, static_cast<int>(mLeftTop.y) - 3, mTextWidth+8 , mTextHeight+6 };
	SDL_RenderCopyEx(
		renderer,
		mFrameTexture,
		nullptr,
		&back,
		0,
		nullptr,
		SDL_FLIP_NONE
	);

	back = { static_cast<int>(mLeftTop.x)+10, static_cast<int>(mLeftTop.y)+10, mTextWidth-20, mTextHeight-20 };
	SDL_RenderCopyEx(
		renderer,
		mTexture,
		nullptr,
		&back,
		0,
		nullptr,
		SDL_FLIP_NONE
	);
	if (mOnThis) {
		back = { static_cast<int>(mLeftTop.x), static_cast<int>(mLeftTop.y), mTextWidth, mTextHeight };
		SDL_RenderCopyEx(
			renderer,
			mOnTexture,
			nullptr,
			&back,
			0,
			nullptr,
			SDL_FLIP_NONE
		);
	}
}



// ‰Šú‰»
void Tool::Initialize() {
	mFilenames = new const char* [9];
	mFilenames[0] = "Image/Eraser.png";
	mFilenames[1] = "Image/Flag0.png";
	mFilenames[2] = "Image/Flag1.png";
	mFilenames[3] = "Image/Flag2.png";
	mFilenames[4] = "Image/Flag3.png";
	mFilenames[5] = "Image/FlagG.png";
	mFilenames[6] = "Image/Block.png";
	mFilenames[7] = "Image/Stick.png";
	mFilenames[8] = "Image/Crate.png";

	mOnTexture = mMake->GetScmana()->SetTexture("Image/OnTool1.png");
	mFrameTexture = mMake->GetScmana()->SetTexture("Image/Frame.png");
	mTexture = mMake->GetScmana()->SetTexture(mFilenames[mObjectNumber]);
}
