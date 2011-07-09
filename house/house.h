#include <common/point.h>
class House: public Drawable {
	public:
		House() {
			location.x = -60;
			location.y = 80;
			viewDistance = 1;//can only see things it touches
		}
		float getRadius() { return 30; }

		void draw() {
			draw_texture("house", location, 60, 60);
		}
};

