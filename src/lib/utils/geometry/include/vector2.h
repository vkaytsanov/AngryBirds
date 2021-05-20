//
// Created by Viktor on 9.1.2021 г..
//

#ifndef VECTOR2_H
#define VECTOR2_H


template<typename T>
class Vector2 {
public:
	T x;
	T y;

	Vector2() {
		x = 0;
		y = 0;
	}

	Vector2(T x, T y) {
		this->x = x;
		this->y = y;
	}

	Vector2<T> operator+(const Vector2<T>& vec) const {
		return Vector2<T>(this->x + vec.x, this->y + vec.y);
	}

	Vector2<T> operator-(const Vector2<T>& vec) const {
		return Vector2<T>(this->x - vec.x, this->y - vec.y);
	}

	Vector2<T> operator*(const Vector2<T>& vec) const {
		return Vector2<T>(this->x * vec.x, this->y * vec.y);
	}

	Vector2<T> operator*(const T scale) const {
		return Vector2<T>(this->x * scale, this->y * scale);
	}
	
	Vector2<T> operator/(const Vector2<T>& vec) const {
		return Vector2<T>(this->x / vec.x, this->y / vec.y);
	}

	Vector2<T>& operator+=(const Vector2<T>& vec) {
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}
};


typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

#endif //VECTOR2_H
