#include "Lunacy/ForwardDefinitions.h"

#define _USE_MATH_DEFINES
#include <math.h>

float Sexy::ClampAngle(float Angle)
{
	while (Angle > M_PI) Angle -= static_cast<float>(2 * M_PI);
	while (Angle <= -M_PI) Angle += static_cast<float>(2 * M_PI);
	return Angle;
}

float Sexy::Clamp(float Value, float Min, float Max)
{
	return (Value > Max) ? Max : (Value < Min) ? Min : Value;
}