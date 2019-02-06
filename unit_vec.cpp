#include "unit_vec.h"

void gen_unit_vec(float x, float y, float z, Uvec* vec_in)
{
  float magnitude = sqrt(square(x) + square(y) + square(z));
  vec_in->x = x / magnitude;
  vec_in->y = y / magnitude;
  vec_in->z = z / magnitude;
}

void print_unit_vec(Uvec vec_in)
{

	char f1[8], f2[8], f3[8], print_str[36];
	dtostrf(vec_in.x, 5, 2, f1);
	dtostrf(vec_in.y, 5, 2, f2);
	dtostrf(vec_in.z, 5, 2, f3);
	sprintf(print_str, "[ %s %s %s ]", f1, f2, f3);

	Serial.println(print_str);
}