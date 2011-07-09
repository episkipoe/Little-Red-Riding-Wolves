#include <common/point.h>
#include <drawable.h>
class Fence: public Drawable {
	public:
		Fence(Point loc) {
			location = loc;
		}

		void draw() {
			draw_texture("fence", location, 10, 10);
		}

		float getRadius() { return 5; }
};
