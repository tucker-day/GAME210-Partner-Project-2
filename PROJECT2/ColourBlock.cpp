//#include "ColourBlock.h"
//
//#include "EventHandler.h"
//#include "Graphics.h"
//
//ColourBlock::ColourBlock()
//{
//	
//}
//
//ColourBlock::~ColourBlock()
//{
//
//}
//
//void ColourBlock::SetColor(int r, int g, int b)
//{
//	colour.r = r;
//	colour.g = g;
//	colour.b = b;
//}
//
//void ColourBlock::Init(float x, float y, int width, int height)
//{
//	transform.position.x = x;
//	transform.position.y = y;
//
//	dimensions.x = width;
//	dimensions.y = height;
//}
//
//void ColourBlock::Translate(float x, float y)
//{
//	// protects it from moving completely off screen
//	if (transform.position.x + dimensions.x + x < Graphics::WINDOW_WIDTH && transform.position.x + x > 0)
//	{
//		transform.position.x += x;
//	}
//
//	// protects it from moving completely off screen
//	if (transform.position.y + dimensions.y + y < Graphics::WINDOW_HEIGHT && transform.position.y + y > 0)
//	{
//		transform.position.y += y;
//	}
//}
//
//void ColourBlock::Draw(bool filled)
//{
//	// create a bounding box based on the dimensions and position.
//	Graphics::SetColor(colour);
//	Graphics::DrawRect(transform, dimensions, filled);
//}
//
//void ColourBlock::Update()
//{
//
//}
