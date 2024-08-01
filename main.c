#include <raylib.h>

#define colorsmax 24
#define shapesmax 4

int main(void) {
	const int width = 800;
	const int height = 450;

	InitWindow(width, height, "Raypaint - Simple Paint Application");

	Color colors[colorsmax] = {LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN, WHITE, BLACK, MAGENTA};

	Rectangle colors_rectangle[colorsmax] = {0};
	Rectangle shapes_rectangle[shapesmax] = {0};
	Rectangle save_rectangle = {8, 390, 65, 50};
	Rectangle ui = {0, 0, 80, 450};

	int mousehover = 0;
	int selectedcolor = 0;
	int selectedshape = 0;
	int selectedshapefr = 0;
	int size = 10;

	Vector2 line[2] = {0};
	Vector2 triangle[3] = {0};

	int linecount = 0;
	int trianglecount = 0;

	bool islinedrawing = false;
	bool istriangledrawing = false;

	RenderTexture2D target = LoadRenderTexture(width, height);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		Vector2 mousepos = GetMousePosition();

		if (IsKeyPressed(KEY_LEFT)) {
			selectedcolor++;
		} else if (IsKeyPressed(KEY_RIGHT)) {
			selectedcolor--;
		}

		size += GetMouseWheelMove() * 5;

		if (size < 2) {
			size = 2;
		} else if (size > 50) {
			size = 50;
		}

		for (int i = 0; i < colorsmax; i++) {
			colors_rectangle[i].height = 20;
			colors_rectangle[i].width = 20;
			colors_rectangle[i].x = 5 + 25 * (i % 3);
			colors_rectangle[i].y = 5 + 25 * (int)(i / 3);
		}

		for (int i = 0; i < shapesmax; i++) {
			shapes_rectangle[i].height = 40;
			shapes_rectangle[i].width = 65;
			shapes_rectangle[i].x = 8 + 1 * (i % 1);
			shapes_rectangle[i].y = 215 + 40 * (int)(i / 1);
		}

		for (int i = 0; i < colorsmax; i++) {
			if (CheckCollisionPointRec(mousepos, colors_rectangle[i])) {
				mousehover = i;
				break;
			}
			mousehover = -1;
		}

		for (int i = 0; i < shapesmax; i++) {
			if (CheckCollisionPointRec(mousepos, shapes_rectangle[i])) {
				selectedshape = i;
				break;
			}
			selectedshape = -1;
		}

		if (mousehover >= 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			selectedcolor = mousehover;
		}

		if (selectedshape >= 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			selectedshapefr = selectedshape;
		}

		if (IsKeyPressed(KEY_S) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousepos, save_rectangle))) {
			Image image = LoadImageFromTexture(target.texture);
			ImageFlipVertical(&image);
			ExportImage(image, "image.png");
			UnloadImage(image);
		}

		if (mousepos.x > 80 && (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || GetGestureDetected() == GESTURE_DRAG)) {
			BeginTextureMode(target);
			switch(selectedshapefr) {
				case 0:
					DrawCircle(mousepos.x, mousepos.y, size, colors[selectedcolor]);
					break;
				case 1:
					DrawPixel(mousepos.x, mousepos.y, colors[selectedcolor]);
					break;
				case 2:
					if (!islinedrawing) {
						islinedrawing = true;
						linecount = 0;
					}
					if (linecount < 2) {
						line[linecount] = mousepos;
						linecount++;
					}
					if (linecount == 2) {
						islinedrawing = false;
						DrawLine(line[0].x, line[0].y, line[1].x, line[1].y, colors[selectedcolor]);
						linecount = 0;
					}
					break;
				case 3:
					if (!istriangledrawing) {
						istriangledrawing = true;
						trianglecount = 0;
					}
					if (trianglecount < 3) {
						triangle[trianglecount] = mousepos;
						trianglecount++;
					}
					if (trianglecount == 3) {
						istriangledrawing = false;
						DrawTriangle(triangle[0], triangle[1], triangle[2], colors[selectedcolor]);
						trianglecount = 0;
					}
					break;
				default:
					break;
			}
			EndTextureMode();
		}
		BeginDrawing();
		ClearBackground(WHITE);

		DrawTextureRec(target.texture, (Rectangle) {0, 0, target.texture.width, - target.texture.height}, (Vector2) {0, 0}, WHITE);

		if (IsKeyPressed(KEY_C)) {
			BeginTextureMode(target);
			ClearBackground(WHITE);
			EndTextureMode();
		}

		DrawRectangleRec(ui, WHITE);

		for (int i = 0; i < colorsmax; i++) {
			DrawRectangleRec(colors_rectangle[i], colors[i]);
			DrawRectangleLinesEx(colors_rectangle[i], 1, BLACK);
		}
		DrawRectangleLinesEx((Rectangle) {colors_rectangle[selectedcolor].x, colors_rectangle[selectedcolor].y, colors_rectangle[selectedcolor].width, colors_rectangle[selectedcolor].height}, 3, BLACK);

		for (int i = 0; i < shapesmax; i++) {
			DrawRectangleRec(shapes_rectangle[i], WHITE);
			DrawRectangleLinesEx(shapes_rectangle[i], 2, BLACK);
		}

		if (islinedrawing) {
			for (int i = 0; i < linecount; i++) {
				DrawCircle(line[i].x, line[i].y, 3, RED);
			}
		} else if (istriangledrawing) {
			for (int i = 0; i < trianglecount; i++) {
				DrawCircle(triangle[i].x, triangle[i].y, 3, RED);
			}
		}

		DrawText("CIRCLE", 20, 230, 10, BLACK);
		DrawText("PIXEL", 20, 270, 10, BLACK);
		DrawText("LINE", 20, 310, 10, BLACK);
		DrawText("TRIANGLE", 15, 350, 10, BLACK);

		DrawRectangleLinesEx(save_rectangle, 2, BLACK);
		DrawText("SAVE", 25, 410, 10, BLACK);

		DrawLine(80, 0, 80, 450, BLACK);

		EndDrawing();
	}
	UnloadRenderTexture(target);
	CloseWindow();
	return 0;
}
