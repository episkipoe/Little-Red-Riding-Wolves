#include <common/point.h>
#include <drawable.h>

enum Orient {HORIZONTAL, VERTICAL, VERTICAL_B, GATE, BACKSLASH_A, BACKSLASH_B, FORWARDSLASH_A, FORWARDSLASH_B};

class Fence: public Drawable {
	public:
		Fence(Point loc, Orient o) {
			location = loc;
			orient = o;
		}
		Fence(int x, int y, Orient o) {
			Point pos(x, y);
			location = pos;
			orient = o;
		}

		void draw() {
			if(orient == HORIZONTAL)
				draw_texture("fence_HORIZONTAL", location, 10, 10);
			if(orient == VERTICAL)
				draw_texture("fence_VERTICAL", location, 2, 10);
			if(orient == VERTICAL_B)
				draw_texture("fence_VERTICAL_B", location, 2, 10);
			if(orient == GATE)
				draw_texture("fence_GATE", location, 10, 10);
			if(orient == BACKSLASH_A)
				draw_texture("fence_BACKSLASH_A", location, 4, 10);
			if(orient == BACKSLASH_B)
				draw_texture("fence_BACKSLASH_B", location, 4, 10);
			if(orient == FORWARDSLASH_A)
				draw_texture("fence_FORWARDSLASH_A", location, 4, 10);
			if(orient == FORWARDSLASH_B)
				draw_texture("fence_FORWARDSLASH_B", location, 4, 10);
		}

		float getFearValue() { return 20; }
		float getRadius() { return 1; }

	private:
		Orient orient;
};
