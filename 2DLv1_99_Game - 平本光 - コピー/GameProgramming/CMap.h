#ifndef CMAP_H
#define CMAP_H

#include "CRectangle.h"

extern CTexture Texture;
extern CTexture Texture3;
class CMap : public CRectangle {
public:
	void Render() {
		if (mEnabled) {
			if (y <= -300) {
				CRectangle::Render(Texture, 0, 48, 253, 213);
			}
			else {
              CRectangle::Render(Texture3, 0, 135, 131, 0);
			}
			
		}
	}
};

#endif
