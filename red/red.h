#ifndef RED_H
#define RED_H

#include <drawable.h>
#include <wolf/wolf.h>
#include <vector>
#include <map>
class Red : public Drawable {
	public:
		Red () {
			resetLocation();
			speed=40;
			viewDistance=8;//Red can see x * radius 
		}

		void draw() {
			if(alive) {
				draw_texture("red", location, 4, 8);
			} else {
				draw_texture("red", location, 4, 8, 90);
			}
		}

		float getRadius() { return 4; }

		void resetLocation() {
			location.x = 80;
			location.y = -60;
			location.z = 0;
			stop();
			lastLoc = location;
			onPath=false;
			beingChased=false;
			pathPoints.clear();
			avoidanceList.clear();
			pathPosition=0;
			alive=true;
		}

		void get_n_nearest(vector<Wolf>& wolves, vector<Wolf> & nearest, size_t n) {
			vector<Wolf> available = wolves;
			for (size_t i = 0 ; i < n ; i++) {
				if(!available.size()) return ;
				double min_dist=location.distance(available[0].getLocation());
				int min_idx=0;
				for (size_t j=1; j<available.size(); j++) {
					double dx=location.distance(available[j].getLocation());
					if(dx<min_dist) {
						min_dist=dx;
						min_idx=j;
					}
				}
				nearest.push_back(available[min_idx]);
				available.erase(available.begin()+min_idx);
			}
		}

		void chase(vector<Wolf>& wolves, Point housePos) {
			if (beingChased) { //beign chased. Run away from wolves, avoid objects, target house
				moveVector.x=0;
				moveVector.y=0;
				vector<Wolf> nearest_wolves;
				get_n_nearest(wolves, nearest_wolves, 6);
				//first, factor in all the wolves
				for (size_t i=0; i<nearest_wolves.size(); i++){
					Point wolfPos = nearest_wolves[i].getLocation();
					float dx = location.distance(wolfPos);
					if(dx > 60) continue;
					moveVector.addVector(location.angle(wolfPos),-14.0/dx);
					//printf("angle: %g\n", location.angle(wolfPos));
				}
				//next, factor in all the avoidance points
				avoidObstacles();

				//finally, add the house pull
				if(!touching) {
					moveVector.addVector(location.angle(housePos),pow(150.0/location.distance(housePos),2));
				}
				moveVector.normalize();
				//moveVector.show();
			} else if (pathPoints.size() > 0) { //following the path
				for (size_t i=0; i<wolves.size(); i++){
					if(sees(&wolves[i])) {
						beingChased=true;
						chase(wolves, housePos);
						return;
					}
				}
				if (location.distance(pathPoints[pathPosition])<5) pathPosition++; //advance the pathPoints list if at the corner
				if (pathPosition<pathPoints.size()) {
					follow(pathPoints[pathPosition]);
				} else {
					beingChased=true; //ran out of path points. Set to beingChased so red will still try to get to house
					chase(wolves, housePos);
					return;
				}
			} else {
				beingChased=true; //ran out of path points. Set to beingChased so red will still try to get to house
				chase(wolves, housePos);
				return;
			}
		}

		void avoidObstacles(){
			map<Drawable *, float>::iterator it;
			for(it = avoidanceList.begin() ; it != avoidanceList.end() ; it++) {
				Drawable * avoid = it->first;
				if(!sees(avoid)) { continue; }
				Point avoidPoint = avoid->getLocation();
				float dx = location.distance(avoidPoint);
				moveVector.addVector(location.angle(avoidPoint),pow(-it->second/dx,3));
			}
		}

		void avoid(Drawable *d) {
			avoidanceList[d] = d->getFearValue();
		}

		void follow(Point followPoint) {
			moveVector = followPoint + (location * -1);
			moveVector.normalize();
		}

		void beginChase() { beingChased=true; }
		void eat() { alive = false; }
		void stop() { moveVector.clear(); }
		void setTouching(bool t) { touching = t; }

		void setOnPath(bool isOnPath) { onPath = isOnPath; }

		void update(float frameTime) {
			if(!alive) return;
			lastLoc = location;
			float movementSpeed = (onPath ? speed * 1.5 : speed);
			location = location + moveVector * movementSpeed * frameTime;
		}

		void clearPath() { pathPoints.clear(); }

		void addPathNode(const Point & node) { pathPoints.push_back(node); }

private:
	Point moveVector;
	float speed;
	bool touching;
	bool onPath;
	bool beingChased;
	bool alive;
	vector<Point> pathPoints;
	size_t pathPosition;
	map<Drawable*, float> avoidanceList;
};

#endif
