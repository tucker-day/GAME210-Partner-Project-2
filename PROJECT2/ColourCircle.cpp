//#include "ColourCircle.h"
//
//#include "EventHandler.h"
//#include "Graphics.h"
//
//ColourCircle::ColourCircle()
//{
//
//}
//
//ColourCircle::~ColourCircle()
//{
//
//}
//
//void ColourCircle::SetColor(int r, int g, int b)
//{
//	colour.r = r;
//	colour.g = g;
//	colour.b = b;
//}
//
//void ColourCircle::Init(float x, float y, float rad)
//{
//	transform.position.x = x;
//	transform.position.y = y;
//
//	radius = rad;
//	dimensions.x = rad;
//	dimensions.y = rad;
//}
//
//void ColourCircle::Draw(bool filled)
//{
//	// create a bounding box based on the dimensions and position.
//	Graphics::SetColor(colour);
//	Graphics::DrawCircle(transform, radius, 100, 1000);
//}
//
//void ColourCircle::Translate(float x, float y)
//{
//	// protects it from moving completely off screen
//	if (transform.position.x + radius+ x < Graphics::WINDOW_WIDTH && transform.position.x- radius + x > 0)
//	{
//		transform.position.x += x;
//	}
//
//	// protects it from moving completely off screen
//	if (transform.position.y + radius +x < Graphics::WINDOW_HEIGHT && transform.position.y - radius + y > 0)
//	{
//		transform.position.y += y;
//	}
//}
//
//void ColourCircle::Update()
//{
//
//}
