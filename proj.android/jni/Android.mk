LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

#FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)

#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   $(FILE_LIST:$(LOCAL_PATH)/%=%)
                   
 LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/DrawScene.cpp \
                   ../../Classes/MenuLayer.cpp \
                   ../../Classes/MyTableView.cpp \
                   ../../Classes/VisibleRect.cpp \
                   ../../Classes/TableViewLayer.cpp 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
