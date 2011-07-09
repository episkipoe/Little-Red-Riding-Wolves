#include <common/point.h>
class House: public Drawable {
	public:
		House() {
			location.x = -60;
			location.y = 80;
		}

		void draw() {
			draw_texture("house", location, 20);
		}
};

