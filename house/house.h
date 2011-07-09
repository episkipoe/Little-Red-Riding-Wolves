#include <common/point.h>
class House: public Drawable {
	public:
		House() {
			location.x = -60;
			location.y = 80;
            radius = 30;//TODO:tweak to fit sprite
            viewDistance = 1;//can only see things it touches
		}

		void draw() {
			draw_texture("house", location, 60);
		}
};

