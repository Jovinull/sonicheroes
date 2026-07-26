#include "game/ADVERTISE.hpp"
#include "autosaveD/ADV_MENU.hpp"

ADV_MENU::ADV_MENU() {
	mCount    = 0;
	mSelect = 0;
	mLoop = 0;
}

ADV_MENU::~ADV_MENU() { }

void ADV_MENU::Add(int value) {
	mSelectItems[mCount] = value;
	mCount++;
}

void ADV_MENU::Clr() {
	mCount = mSelect = 0;
}

int ADV_MENU::UpdateUD(int port) {
	if (port == -1) {
		port = 0;
	}

	if (Advertise.GetKey(8, port)) {
		mSelect--;
	} else if (Advertise.GetKey(4, port)) {
		mSelect++;
	}

	Commit();

	if (mSelect == -1) {
		return -1;
	}

	return mSelectItems[mSelect];
}

int ADV_MENU::UpdateUD2() {
	if (Advertise.GetKey(8, 0)) {
		mSelect--;
	} else if (Advertise.GetKey(4, 0)) {
		mSelect++;
	}

	Commit();

	if (Advertise.GetKey(8, 1)) {
		mSelect--;
	} else if (Advertise.GetKey(4, 1)) {
		mSelect++;
	}

	Commit();

	if (mSelect == -1) {
		return -1;
	}

	return mSelectItems[mSelect];
}

int ADV_MENU::UpdateLR(int port) {
	if (port == -1) {
		port = 0;
	}

	if (Advertise.GetKey(1, port)) {
		mSelect--;
	} else if (Advertise.GetKey(2, port)) {
		mSelect++;
	}

	Commit();

	if (mSelect == -1) {
		return -1;
	}

	return mSelectItems[mSelect];
}

int ADV_MENU::UpdateQUAD(int port) {
	if (port == -1) {
		port = 0;
	}

	switch (mSelect) {
		case 0:
			if (Advertise.GetKey(2, port)) {
				mSelect = 2;
			}
			if (Advertise.GetKey(4, port)) {
				mSelect = 1;
			}
			break;
		case 1:
			if (Advertise.GetKey(8, port)) {
				mSelect = 0;
			}
			if (Advertise.GetKey(2, port)) {
				mSelect = 3;
			}
			break;
		case 2:
			if (Advertise.GetKey(1, port)) {
				mSelect = 0;
			}
			if (Advertise.GetKey(4, port)) {
				mSelect = 3;
			}
			break;
		case 3:
			if (Advertise.GetKey(8, port)) {
				mSelect = 2;
			}
			if (Advertise.GetKey(1, port)) {
				mSelect = 1;
			}
			break;
	}

	Commit();

	if (mSelect == -1) {
		return -1;
	}

	return mSelectItems[mSelect];
}

// https://decomp.me/scratch/CBQOE
int ADV_MENU::UpdateQUAD2(int firstRowLength, int secondRowLength, int port) {
	int currentSelect;

	if (port == -1) {
		port = 0;
	}

	{
		BOOL canMoveUp    = 1;
		BOOL canMoveDown  = 1;
		BOOL canMoveLeft  = 1;
		BOOL canMoveRight = 1;
		u32 isFirstRow;

		currentSelect = mSelect;
		isFirstRow   = currentSelect < firstRowLength;

		if (isFirstRow) {
			canMoveUp = 0;
		}
		if (!isFirstRow) {
			canMoveDown = 0;
		}

		if (mSelect == 0 || currentSelect == firstRowLength) {
			canMoveLeft = 0;
		}
		if (currentSelect == firstRowLength - 1
		    || currentSelect == firstRowLength + secondRowLength - 1) {
			canMoveRight = 0;
		}

		if (canMoveUp && Advertise.GetKey(8, port)) {
			mSelect -= firstRowLength;
			while (mSelect >= firstRowLength) {
				mSelect--;
			}
		} else if (canMoveDown && Advertise.GetKey(4, port)) {
			mSelect += firstRowLength;
			while (mSelect < firstRowLength) {
				mSelect++;
			}
		} else if (canMoveLeft && Advertise.GetKey(1, port)) {
			mSelect--;
		} else if (canMoveRight && Advertise.GetKey(2, port)) {
			mSelect++;
		}

		Commit();

		if (mSelect == -1) {
			return -1;
		}

		return mSelectItems[mSelect];
	}
}

void ADV_MENU::Commit() {
	if (mLoop) {
		if (mSelect < 0) {
			mSelect = mCount - 1;
		}
		if (mCount > mSelect) {
			return;
		}
		mSelect = 0;
	} else {
		if (mSelect < 0) {
			mSelect = 0;
		}
		if (mCount > mSelect) {
			return;
		}
		mSelect = mCount - 1;
	}
}

void ADV_MENU::Set(int value) {
	for (int i = 0; i != mCount; i++) {
		if (mSelectItems[i] == value) {
			mSelect = i;
			Commit();
			break;
		}
	}
}

void ADV_MENU::OnLoop() {
	mLoop = 1;
}

void ADV_MENU::SetSelect(int select) {
	if (select <= 0) return;
	if (select >= 3) return;

	mSelect = select;
}
