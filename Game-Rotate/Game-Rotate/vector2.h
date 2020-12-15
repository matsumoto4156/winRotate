#pragma once
#include <cmath>
using namespace std;

 struct vector2{
	 float x = 0.0f;
	 float y = 0.0f;
	 vector2 operator + (vector2 vec) {
		 vector2 result;
		 result.x = this->x + vec.x;
		 result.y = this->y + vec.y;
		 return result;
	 }
	 vector2 operator - (vector2 vec) {
		 vector2 result;
		 result.x = this->x - vec.x;
		 result.y = this->y - vec.y;
		 return result;
	 }
	 bool operator < (vector2 vec) {
		 if (this->x >= vec.x) {
			 return false;
		 }
		 else if (this->y >= vec.y) {
			 return false;
		 }
		 return true;
	 }
	 bool operator > (vector2 vec) {
		 if (this->x <= vec.x) {
			 return false;
		 }
		 else if (this->y <= vec.y) {
			 return false;
		 }
		 return true;
	 }
	 float distance(vector2 vec) {
		 return sqrt(pow(this->x - vec.x, 2) + pow(this->y - vec.y, 2));
	 }
};

 template <typename T> struct vec2 {
	 T x = 0;
	 T y = 0;
	 vec2 operator + (vec2 vec) {
		 vec2 result;
		 result.x = this->x + vec.x;
		 result.y = this->y + vec.y;
		 return result;
	 }
	 vec2 operator - (vec2 vec) {
		 vec2 result;
		 result.x = this->x - vec.x;
		 result.y = this->y - vec.y;
		 return result;
	 }
	 bool operator < (vec2 vec) {
		 if (this->x >= vec.x) {
			 return false;
		 }
		 else if (this->y >= vec.y) {
			 return false;
		 }
		 return true;
	 }
	 bool operator > (vec2 vec) {
		 if (this->x <= vec.x) {
			 return false;
		 }
		 else if (this->y <= vec.y) {
			 return false;
		 }
		 return true;
	 }
	 T distance(vec2 vec) {
		 return sqrt(pow(this->x - vec.x, 2) + pow(this->y - vec.y, 2));
	 }
 };