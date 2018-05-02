#ifndef VECTOR_H
#define VECTOR_H


#ifdef ARDUINO
#include <Arduino.h>
#endif

class Vector {
public:
	Vector (char x_, char y_);
	char x;
	char y;

	inline void stop() {
		this->x = 0;
		this->y = 0;
	}

	inline void invert() {
		this->x = -this->x;
		this->y = -this->y;
	}
};

#endif /* VECTOR_H */
