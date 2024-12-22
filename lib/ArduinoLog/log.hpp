#include <HardwareSerial.h>

#ifndef ARDUINO_LOG_LEVEL
#define ARDUINO_LOG_LEVEL 0
#endif

#define LOG_BEGIN(baud_rate) Serial.begin(baud_rate);

#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_VERBOSE 4

#define ARDUINO_LOGD(param) 
#define ARDUINO_LOGV(param) 
#define ARDUINO_LOGI(param) 
#define ARDUINO_LOGE(param) 


#if ARDUINO_LOG_LEVEL >= LOG_LEVEL_ERROR
#define ARDUINO_LOGE(param) _ARDUINO_LOG_ERROR(param)
#endif

#if ARDUINO_LOG_LEVEL >= LOG_LEVEL_INFO
#define ARDUINO_LOGI(param) _ARDUINO_LOG_INFO(param)
#endif

#if ARDUINO_LOG_LEVEL >= LOG_LEVEL_DEBUG
#define ARDUINO_LOGD(param) _ARDUINO_LOG_DEBUG(param)
#endif

#if ARDUINO_LOG_LEVEL >= LOG_LEVEL_VERBOSE
#define ARDUINO_LOGV(param) _ARDUINO_LOG_VERBOSE(param)
#endif

#define _ARDUINO_LOG_ERROR(logtext)   Serial.print("[ERROR]   "); Serial.println(logtext);
#define _ARDUINO_LOG_VERBOSE(logtext) Serial.print("[VERBOSE] "); Serial.println(logtext);
#define _ARDUINO_LOG_DEBUG(logtext)   Serial.print("[DEBUG]   "); Serial.println(logtext);
#define _ARDUINO_LOG_INFO(logtext)    Serial.print("[INFO]    "); Serial.println(logtext);

