#include <common/point.h>
class Path: public Drawable {
	public:
		Path(const Point & loc) {
			location = loc;
		}

		void draw() {
			draw_texture("path", location, 10, 10);
		}

		float getRadius() { return 5; }
};
