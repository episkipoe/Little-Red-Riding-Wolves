#ifndef RED_H
#define RED_H

#include <drawable.h>
#include <images/textures.h>
#include <wolf/wolf.h>
#include <vector>
#include <map>
class Red : public Drawable {
	public:
		Red () {
			resetLocation();
			speed=40;
			viewDistance=5;//Red can see 5 times her radius
		}

		void draw() {
			draw_texture("red", location, 4, 8);
		}

		float getRadius() { return 4; }

		void resetLocation() {
			location.x = 80;
			location.y = -60;
			location.z = 0;
			lastLoc = location;
			onPath=false;
			beingChased=false;
			avoidanceList.clear();
			pathPosition=0;
		}

		void chase(vector<Wolf>& wolvesVector, Point housePos) {
			if (beingChased) { //beign chased. Run away from wolves, avoid objects, target house
				moveVector.x=0;
				moveVector.y=0;
				//first, factor in all the wolves
				for (size_t i=0; i<wolvesVector.size(); i++){
					Point wolfPos = wolvesVector[i].getLocation();
					moveVector.addVector(location.angle(wolfPos),-5.0/location.distance(wolfPos));
					//printf("angle: %g\n", location.angle(wolfPos));
				}
				//next, factor in all the avoidance points
                avoidObstacles();

				//finally, add the house pull
				moveVector.addVector(location.angle(housePos),pow(100.0/location.distance(housePos),3));
				moveVector.normalize();
				//moveVector.show();

			} else if (pathPoints.size() > 0) { //following the path
				if (location.distance(pathPoints[pathPosition])<15) pathPosition++; //advance the pathPoints list if at the corner
				if (pathPosition<pathPoints.size()) {
					follow(pathPoints[pathPosition]);
				} else {
					beingChased=true; //ran out of path points. Set to beingChased so red will still try to get to house
				}
			} else {
				beingChased=true; //ran out of path points. Set to beingChased so red will still try to get to house
			}

		}

        void avoidObstacles(){
            for (size_t i=0; i<avoidanceList.size(); i++)
                moveVector.addVector(location.angle(avoidanceList[i]),pow(-20.0/location.distance(avoidanceList[i]),3));
        }

		void avoid(Drawable *d) {
            if(isAvoiding.find(d) == isAvoiding.end())
			    avoidanceList.push_back(d->getLocation());
            isAvoiding[d] = true;
		}


		void follow(Point followPoint) {
			moveVector = followPoint + (location * -1);
			moveVector.normalize();
		}

		void beginChase() { beingChased=true; }

		void setOnPath(bool isOnPath) { onPath = isOnPath; }

		void update(float frameTime) {
			lastLoc = location;
			location = location + moveVector * speed * frameTime;
		}

		void clearPath() { pathPoints.clear(); }

		void addPathNode(const Point & node) { pathPoints.push_back(node); }

private:
	Point moveVector;
	float speed;
	bool onPath;
	bool beingChased;
	vector<Point> avoidanceList;
	vector<Point> pathPoints;
	size_t pathPosition;
    map<Drawable*, bool> isAvoiding;
};

#endif
