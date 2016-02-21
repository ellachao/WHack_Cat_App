#include "../health/health.h"
#include "steps_window.h"

static Window *s_steps_window;
static TextLayer *s_numOf_text_layer, *s_steps_text_layer, *s_youveTaken_text_layer, *s_NUM_text_layer;
static GBitmap *s_steps_icon_bitmap, *s_sleep_icon_bitmap, *s_water_icon_bitmap;
static BitmapLayer *s_steps_icon_bitmap_layer, *s_sleep_icon_bitmap_layer, *s_water_icon_bitmap_layer;
static const int icon_size = 30;
static const int side_margin = 10;
static const int bottom_margin = 5;

static void steps_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  static char buffer[8];

  // Create the TextLayers with specific bounds
  s_numOf_text_layer = text_layer_create(
      GRect(side_margin, 5, bounds.size.w/4, bounds.size.h/4));
  text_layer_set_background_color(s_numOf_text_layer, GColorClear);
  text_layer_set_text_color(s_numOf_text_layer, GColorBlack);
  text_layer_set_text(s_numOf_text_layer, "# of");
  text_layer_set_font(s_numOf_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(s_numOf_text_layer, GTextAlignmentCenter);
  
  s_steps_text_layer = text_layer_create(
      GRect(bounds.size.w/4, 0, bounds.size.w/2, bounds.size.h/4));
  text_layer_set_background_color(s_steps_text_layer, GColorClear);
  text_layer_set_text_color(s_steps_text_layer, GColorBlack);
  text_layer_set_text(s_steps_text_layer, "STEPS");
  text_layer_set_font(s_steps_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_steps_text_layer, GTextAlignmentCenter);
  
  s_youveTaken_text_layer = text_layer_create(
      GRect(0, text_layer_get_content_size(s_steps_text_layer).h, bounds.size.w, bounds.size.h/4));
  text_layer_set_background_color(s_youveTaken_text_layer, GColorClear);
  text_layer_set_text_color(s_youveTaken_text_layer, GColorBlack);
  text_layer_set_text(s_youveTaken_text_layer, "you've taken today:");
  text_layer_set_font(s_youveTaken_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(s_youveTaken_text_layer, GTextAlignmentCenter);
  
  s_NUM_text_layer = text_layer_create(
      GRect(0, bounds.size.h-(icon_size+bottom_margin*2)*2, bounds.size.w, bounds.size.h/4));
  text_layer_set_background_color(s_NUM_text_layer, GColorClear);
  text_layer_set_text_color(s_NUM_text_layer, GColorBlack);
  snprintf(buffer,sizeof(buffer),"%d",getMetric(HealthMetricStepCount));
  text_layer_set_text(s_NUM_text_layer,buffer); // to be taken from data!!!
  text_layer_set_font(s_NUM_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text_alignment(s_NUM_text_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_numOf_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_steps_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_youveTaken_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_NUM_text_layer));
  
//   // .png pictures (bitmap): will need to be specified as bitmap resource type in appinfo.json !!!
//   // https://developer.pebble.com/guides/pebble-apps/resources/image-resources/
//   // also need 40px icons!!!
  
  // bitmap layers (icons)
  s_steps_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_STEPS_IMAGE);
  s_steps_icon_bitmap_layer = bitmap_layer_create(GRect(side_margin, bounds.size.h-icon_size-bottom_margin, icon_size, icon_size));
  bitmap_layer_set_bitmap(s_steps_icon_bitmap_layer, s_steps_icon_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_steps_icon_bitmap_layer));
  
  s_sleep_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_SLEEP_IMAGE);
  s_sleep_icon_bitmap_layer = bitmap_layer_create(GRect((bounds.size.w/2)-(icon_size/2), bounds.size.h-icon_size-bottom_margin, icon_size, icon_size));
  bitmap_layer_set_bitmap(s_sleep_icon_bitmap_layer, s_sleep_icon_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_sleep_icon_bitmap_layer));
  
  s_water_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_WATER_IMAGE);
  s_water_icon_bitmap_layer = bitmap_layer_create(GRect(bounds.size.w-icon_size-side_margin, bounds.size.h-icon_size-bottom_margin, icon_size, icon_size));
  bitmap_layer_set_bitmap(s_water_icon_bitmap_layer, s_water_icon_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_water_icon_bitmap_layer));

}

static void steps_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_numOf_text_layer);
}

void step_window_push() {
  // Create main Window element and assign to pointer
  s_steps_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_steps_window, (WindowHandlers) {
    .load = steps_window_load,
    .unload = steps_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_steps_window, true);
}

