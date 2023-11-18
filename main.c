#include <raylib.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 1600
#define HEIGHT 1000

#define FN_X_MAX 15
#define FN_Y_MAX 15

const int x_axis_offset = 0.166f * WIDTH;
const int y_axis_offset = 0.166f * HEIGHT;

const int graph_width = WIDTH - (x_axis_offset * 2);		// in pixels
const int graph_height = HEIGHT - (y_axis_offset * 2);

// y = x
double function(double x) {
	return (x - 4) * (x - 4);
}

// note: width and height should be given in scale units ie. 10 units wide, 5 units tall, function is evaluated with a domain [0, 10] and range [0, 5]
RenderTexture2D draw_function(unsigned int width, unsigned int height, bool should_smooth) {

	RenderTexture2D output = LoadRenderTexture(graph_width, graph_height);

	if(width > 0 && height > 0) {
		double x_step = (double) width / (double) graph_width;				// scale-units per pixel
		double y_step = (double) height / (double) graph_height;			// thank god that C is case-sensitive

		printf("INFO: GRAPH: gw: %d, gh: %d, xs: %.04f, ys_inv: %.04f\n", graph_width, graph_height, x_step, 1 / y_step);

		// now we have a graph that is in scale-units on the y-axis and pixel on the x-axis

		BeginTextureMode(output);
		for(int x = 0; x < graph_width; x++) {
			double result_b = function(x * x_step);
			double result_t = function((x + 1) * x_step);

			int y_b = result_b / y_step;
			int y_t = result_t / y_step;

			DrawPixel(x, y_b, RED);
			if(should_smooth) DrawLine(x, y_b, x + 1, y_t, RED);
		}
		EndTextureMode();
	} else {
		// something has gone wrong with the boundaries
		BeginTextureMode(output);

			DrawText(TextFormat("ERROR: bounds made no sense! graph_width: %d, graph_height: %d", width, height), 0, 0, 20, RED);

		EndTextureMode();
	}

	return output;
}

int main(void) {
	InitWindow(WIDTH, HEIGHT, "Test Window");

	unsigned int width = 7;
	unsigned int height = 7;

	int tick_mark_height = 10;

	bool should_smooth = true;

	RenderTexture2D target = draw_function(width, height, should_smooth);

	while(!WindowShouldClose()) {
		//------------------------------------------------------------------------------
		// update

		if(IsKeyPressed(KEY_LEFT) && width > 1) {
			width--;

			target = draw_function(width, height, should_smooth);
		}
		if(IsKeyPressed(KEY_RIGHT) && width < (FN_X_MAX - 1)) {
			width++;

			target = draw_function(width, height, should_smooth);
		}
		if(IsKeyPressed(KEY_UP) && height < (FN_Y_MAX - 1)) {
			height++;

			target = draw_function(width, height, should_smooth);
		}
		if(IsKeyPressed(KEY_DOWN) && height > 1) {
			height--;

			target = draw_function(width, height, should_smooth);
		}

		if(IsKeyPressed(KEY_SPACE)) {
			should_smooth = !should_smooth;

			target = draw_function(width, height, should_smooth);
		}

		if(IsKeyPressed(KEY_ENTER)) {
			const char * fp = TextFormat("./imgs/graph-%d-%d-%d.png", time(NULL), width, height);

			TakeScreenshot(fp);
		}

		//------------------------------------------------------------------------------
		// draw
		BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawTexture(target.texture, x_axis_offset, y_axis_offset, WHITE);

			DrawLine(x_axis_offset, HEIGHT - y_axis_offset, (WIDTH - x_axis_offset), HEIGHT - y_axis_offset, BLACK);
			DrawLine(x_axis_offset, y_axis_offset, x_axis_offset, (HEIGHT - y_axis_offset), BLACK);

			DrawLine(x_axis_offset - 4, HEIGHT - y_axis_offset + 4, x_axis_offset + 4, HEIGHT - y_axis_offset - 4, BLACK);

			for(unsigned int x = 1; x < width; x++) {
				DrawLine(x_axis_offset + (x * (graph_width / width)), HEIGHT - y_axis_offset + (tick_mark_height / 2), x_axis_offset + (x * (graph_width / width)), HEIGHT - y_axis_offset - (tick_mark_height / 2), BLACK);
			}

			for(unsigned int y = 1; y < height; y++) {
				DrawLine(x_axis_offset + (tick_mark_height / 2), y_axis_offset + (y * (graph_height / height)), x_axis_offset - (tick_mark_height / 2), y_axis_offset + (y * (graph_height / height)), BLACK);
			}

			char * x_lbl = "x";
			char * y_lbl = "y";
			char * o_lbl = "0";

			int label_font_size = 20;

			int xl_width = MeasureText(x_lbl, label_font_size);
			int yl_width = MeasureText(y_lbl, label_font_size);
			int ol_width = MeasureText(o_lbl, label_font_size);

			DrawText(x_lbl, x_axis_offset + graph_width + (xl_width / 2), y_axis_offset + graph_height - (label_font_size / 2), label_font_size, BLACK);

			DrawText(y_lbl, x_axis_offset - (yl_width / 2), y_axis_offset - (yl_width / 2) - label_font_size, label_font_size, BLACK);

			DrawText(o_lbl, x_axis_offset - (ol_width * 1.7f), HEIGHT - y_axis_offset, label_font_size, BLACK);

			DrawText(TextFormat("x: [ 0, %2d ]", width), 10, 10, 20, BLACK);
			DrawText(TextFormat("y: [ 0, %2d ]", height), 10, 30, 20, BLACK);
			DrawText(TextFormat("SMOOTHING %s", (should_smooth) ? "ON" : "OFF"), 10, 50, 20, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

