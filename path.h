#include <common/point.h>
class Path: public Drawable {
	public:
		Path(Point loc) {
			location = loc;
			radius = 10;//TODO:tweak to fit sprite
		}

		void draw() {
			draw_texture("path", location, 10, 10);
		}
};
