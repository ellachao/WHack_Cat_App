
#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "health/health.h"



static Window *s_main_window;
static TextLayer *s_title_layer;
static GBitmap *s_steps_icon_bitmap, *s_sleep_icon_bitmap, *s_water_icon_bitmap;
static BitmapLayer *s_steps_icon_bitmap_layer, *s_sleep_icon_bitmap_layer, *s_water_icon_bitmap_layer;
static const int icon_size = 30;
static const int side_margin = 10;
static const int bottom_margin = 5;

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  s_title_layer = text_layer_create(
      GRect(0, 0, bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_title_layer, GColorClear);
  text_layer_set_text_color(s_title_layer, GColorBlack);
  text_layer_set_text(s_title_layer, "Catnap");
  text_layer_set_font(s_title_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_title_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_title_layer));
  
  // .png pictures (bitmap): will need to be specified as bitmap resource type in appinfo.json !!!
  // https://developer.pebble.com/guides/pebble-apps/resources/image-resources/
  // also need 40px icons!!!
  
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
  		  
static void select_click_handler(ClickRecognizerRef recognizer, void *context) { 
  health_init();
}


static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_title_layer);
}

  
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  window_set_click_config_provider(s_main_window, click_config_provider);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
