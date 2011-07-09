#include <common/point.h>
class Fense: public Drawable {
	public:
		Fense(Point loc) {
			location = loc;
			radius = 10;//TODO:tweak to fit sprite
		}

		void draw() {
			draw_texture("fence", location, 10);
		}
};
