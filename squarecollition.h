#pragma once

bool SquareCollition(int zx,int zy,int zx2,int zy2,int ax,int ay,int ax2,int ay2) {
	bool up    =false;
	bool down  =false;
	bool left  =false;
	bool right =false;

	if (zy <= ay2) {
		up = true;
	}
	if (zy2 >= ay) {
		down = true;
	}
	if (zx <= ax2) {
		left = true;
	}
	if (zx2 >= ax) {
		right = true;
	}

	if (up == true &&
		down==true&&
		left==true&&
		right==true
		)return true;

	return false;
}