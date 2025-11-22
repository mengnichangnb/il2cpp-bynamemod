#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>

#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"
#include "wy/wy.h"

#include "ByNameModding/Tools.h"

#include "ByNameModding/Il2Cpp.h"

#include "Includes/Dobby/dobby.h"




//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

#include "Includes/Macros.h"


void *instanceBtn;
string cstext1;
char *cstext2;
const char *km;
const char *imei;

using namespace std;
// Hooking examples. Assuming you know how to write hook
void (*AddMoneyExample)(void *instance, int amount);

extern "C"
JNIEXPORT void JNICALL
Java_com_android_support_Main_Get_1AndroidID(JNIEnv *env, jclass clazz, jstring my__id) {
  if (my__id == NULL) {
    return;
}else{
    imei = env->GetStringUTFChars(my__id, 0);
}
}



std::map < std::string, uintptr_t > Fields;
std::map < std::string, uintptr_t > Methods;
uintptr_t g_il2cpp;

// Hooking examples. Assuming you know how to write hook

#define HOOK_BNM(dll, namespace, class, function, count, newfunction)\
DobbyHook((void * )(Il2CppGetMethodOffset(OBFUSCATE(dll), OBFUSCATE(namespace), OBFUSCATE(class), OBFUSCATE(function), count)), (void * ) newfunction, (void ** ) & old_ ##newfunction)

#define GETFIELD_BNM(dll, namespace, class, field)\
    (uintptr_t) Il2CppGetFieldOffset(dll, namespace, class, field)

#define GETADDRESS_BNM(dll, namespace, class, function, count)\
Il2CppGetMethodOffset(OBFUSCATE(dll), OBFUSCATE(namespace), OBFUSCATE(class), OBFUSCATE(function), count)

#define GETADDRESS_VERIFIED(dll, namespace, class, function, count)\
Il2CppGetMethodOffsetWithVerifier(OBFUSCATE(dll), OBFUSCATE(namespace), OBFUSCATE(class), OBFUSCATE(function), count)
//查找同名类的方法

#define HOOK_BNMWithVerifier(dll, namespace, class, function, count, newfunction)\
DobbyHook((void * )(Il2CppGetMethodOffsetWithVerifier(OBFUSCATE(dll), OBFUSCATE(namespace), OBFUSCATE(class), OBFUSCATE(function), count)), (void * ) newfunction, (void ** ) & old_ ##newfunction)

// we will run our hacks in a new thread so our while loop doesn't block process main thread







bool iscost = false;
int costvalue = 99;
int( * old_cost)(void * instance, int side);
int cost(void * instance, int side) {
    
    if (instance != NULL && iscost) {
        
        return costvalue;
    }
    return old_cost(instance, side);
}


void *hack_thread(void *) {
    
    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));

    //Anti-lib rename
    /*
    do {
        sleep(1);
    } while (!isLibraryLoaded("libYOURNAME.so"));*/

   // HOOK_BNM("Assembly-CSharp.dll", "Torappu.Battle", "BattleController", "GetCost", 1, cost);
GETADDRESS_BNM("Assembly-CSharp.dll", "Torappu.Battle", "BattleController", "GetCost",1);


    return NULL;
}



jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;
	
      //features;
     char *features[] = {
          
            OBFUSCATE("1_Toggle_全屏攻击"),
            OBFUSCATE("2_Toggle_秒杀"),
            OBFUSCATE("3_Toggle_无敌"),
            OBFUSCATE("4_Toggle_无限技能"),
            OBFUSCATE("5_Toggle_超级攻速"),
            OBFUSCATE("6_Toggle_全屏放置"),
            OBFUSCATE("7_Toggle_锁费"),
            OBFUSCATE("8_Toggle_去除装置"),
			
			//fuck,
			
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");

    //BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

    switch (featNum) {
 
        

   
	case -10: {	
	    km=env->GetStringUTFChars(str, 0);
        break;
	}
	
	case -11: {			
					
	    char *dljg=wydl(km,imei);
    	
    	if (dljg=="hsjjsbdhejsnsgjwkwgdudnd"){
        	char dqsj[128] = "登录成功\n到期时间: ";
            strcat(dqsj, buffer); 
         
            Toast(env, obj, dqsj, ToastLength::LENGTH_SHORT);      
        	removeView(env,scrollView1,linearLayout3);
          	addView(env,scrollView1,linearLayout1);
         	
     	} else {
        	Toast(env,obj,dljg,ToastLength::LENGTH_LONG); 
	    }
        break;
	}
	
	case -12: {
            
            char * dljg = wyjb(km, imei);
            
            if (dljg == "hsjjsbdhejsnsgjwkwgdudnd") {
                char dqsj[128] = "解绑成功\n解绑剩余次数: ";
                strcat(dqsj, buffer);
                Toast(env, obj, dqsj, ToastLength::LENGTH_SHORT);
            } else {
                Toast(env, obj, dljg, ToastLength::LENGTH_LONG);
            }
        }
        break;
	

	
        
    }
}





__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
            {OBFUSCATE("IconWebViewData"),  OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
            {OBFUSCATE("IsGameLibLoaded"),  OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
            {OBFUSCATE("Init"),  OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
            {OBFUSCATE("SettingsList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
            {OBFUSCATE("SetMloinList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SetMloinList)},
            {OBFUSCATE("GetFeatureList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
		    {OBFUSCATE("getLinearLayout"), OBFUSCATE("(Landroid/widget/ScrollView;Landroid/widget/LinearLayout;Landroid/widget/LinearLayout;Landroid/widget/LinearLayout;)V"),reinterpret_cast<void *>(getLinearLayout)},
    };

    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},                    
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}
