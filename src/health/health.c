
static bool h_available;

static void health_handler(HealthEventType event, void *context) {
  // Which type of event occured?
  switch(event) {
    case HealthEventSignificantUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventSignificantUpdate event");
      break;
    case HealthEventMovementUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventMovementUpdate event");
      break;
    case HealthEventSleepUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventSleepUpdate event");
      break;
  }
}
void health_init(){
  h_available=health_service_events_subscribe(health_handler, NULL);
  if(!h_available){
    //no health data
  }
}

int getMetric(HeathMetric metric){
  HealthServiceAccessibilityMask result = 
    health_service_metric_accessible(metric,time_start_of_today() , time(NULL));
  if(result & HealthServiceAccessibilityMaskAvailable) {
    return (int)health_service_sum_today(metric);
  }
  else{
    return 0;
  }
}
