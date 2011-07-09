#include <common/point.h>
#include <drawable.h>
class Fence: public Drawable {
	public:
		Fence(Point loc) {
			location = loc;
			radius = 10;//TODO:tweak to fit sprite
		}

		void draw() {
			draw_texture("fence", location, 10, 10);
		}
};
